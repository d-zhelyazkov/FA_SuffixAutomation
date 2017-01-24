#include <stdio.h>
#include "state.h"

using namespace std;

#define MAX_LEN 100000000

State* START = 0;
State* CURRENT = 0;


void addChar(char c);
unsigned countTerminals();

int main() {
	printf("%d\n", sizeof(State));
	//reading input
	char* word = new char[MAX_LEN + 1];
	scanf("%s", word);

    unsigned charSize = scanf("%s", word);
    printf("%d\n", charSize);

    return 0;

	//init
	CURRENT = START = getNewState();

	//populating suffix automaton
	for (unsigned i = 0; word[i]; i++) {
		addChar(word[i]);
		//printf("%u\n", STATES_CNT);
	}

	//printing results
	printf("%u\n%llu\n%u", STATES_CNT, EDGES_CNT, countTerminals());

	return 0;
}

//adding a char to the suffix automation
void addChar(char c) {
	// 1 - 27
	//c -= 'a';
	//c++;

	//creating a state
    unsigned newStateIx = getNewStateIx();
    State* newState = getStateByIx(newStateIx);
    newState->alpha = c;
	newState->length = CURRENT->length + 1;

	State* state = CURRENT;
	//assigning missing edges to suffix links up to the start
	State* childState = 0;
    unsigned childIx = -1;
	for (; state && !(childState = getStateByIx(childIx = state->getChildIx(c))); state = getStateByIx(state->suffixLink)){
		state->childrenStates.add(newStateIx);
		EDGES_CNT++;
	}

	newState->suffixLink = 0;
	if (childState) {
		//if a corresponing edge was found
		newState->suffixLink = childIx;

		if (state->length + 1 != childState->length) {
			//creating a clone
            unsigned cloneIx = childState->clone();
            State* clone = getStateByIx(cloneIx);
			clone->length = state->length + 1;
			for (; state && state->getChildIx(c) == childIx; state = getStateByIx(state->suffixLink)) {
				state->replaceChild(cloneIx);
			}

			newState->suffixLink = childState->suffixLink = cloneIx;
		}
	}
	
	CURRENT = newState;
}

unsigned countTerminals() {
	unsigned terminals = 0;
	for (State* state = CURRENT; state; state = getStateByIx(state->suffixLink))
		terminals++;

	return terminals;
}
