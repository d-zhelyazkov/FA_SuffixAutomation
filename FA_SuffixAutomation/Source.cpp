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

	//init
	CURRENT = START = statesArray + getNewState();

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
    unsigned newStateIx = getNewState();
    State* newState = statesArray + newStateIx;
    newState->alpha = c;
	newState->length = CURRENT->length + 1;

	State* state = CURRENT;
	//assigning missing edges to suffix links up to the start
	State* childState = 0;
	for (; state && !(childState = state->getChild(c)); state = state->suffixLink) {
		state->childrenStates.add(newStateIx);
		EDGES_CNT++;
	}

	newState->suffixLink = START;
	if (childState) {
		//if a corresponing edge was found
		newState->suffixLink = childState;

		if (state->length + 1 != childState->length) {
			//creating a clone
			State* clone = new State(childState);
			clone->length = state->length + 1;
			for (; state && state->getChild(c) == childState; state = state->suffixLink) {
				state->replaceChild(clone);
			}

			newState->suffixLink = childState->suffixLink = clone;
		}
	}
	
	CURRENT = newState;
}

unsigned countTerminals() {
	unsigned terminals = 0;
	for (State* state = CURRENT; state; state = state->suffixLink)
		terminals++;

	return terminals;
}
