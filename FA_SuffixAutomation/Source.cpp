#include <stdio.h>
#include <string.h>
#include "state.h"

using namespace std;

#define MAX_LEN 100000000

unsigned CURRENT = 0;
unsigned START = 0;

void addChar(char c);
unsigned countTerminals();

int main() {
	//reading input
	char* word = new char[MAX_LEN + 1];
    scanf("%s", word);
    unsigned wordSize = strlen(word);
    //printf("word size: %d\n", wordSize);

	//init
    init(2 * wordSize + 1);
    START = CURRENT = getNewState();

	//populating suffix automaton
	for (unsigned i = 0; word[i]; i++) {
		addChar(word[i]);
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
    unsigned newState = getNewState();
    statesAlphas[newState] = c;
	statesLengths[newState] = statesLengths[CURRENT] + 1;

	unsigned state = CURRENT;
	//assigning missing edges to suffix links up to the start
	unsigned childState = 0;
	for (; state && !(childState = getChild(state, c)); state = statesLinks[state]){
        addChild(state, newState);
	}

    statesLinks[newState] = START;
	if (childState) {
		//if a corresponing edge was found
        statesLinks[newState] = childState;

		if (statesLengths[state] + 1 != statesLengths[childState]) {
			//creating a clone
            unsigned clone = cloneState(childState);
            statesLengths[clone] = statesLengths[state] + 1;
			for (; state && getChild(state, c) == childState; state = statesLinks[state]) {
				replaceChild(state, clone);
			}

            statesLinks[newState] = statesLinks[childState] = clone;
		}
    }

	CURRENT = newState;
}

unsigned countTerminals() {
	unsigned terminals = 0;
    for (unsigned state = CURRENT; state; state = statesLinks[state]) {
        terminals++;
    }
	return terminals;
}
