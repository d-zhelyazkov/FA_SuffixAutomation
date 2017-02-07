#include <stdio.h>
#include <string.h>
#include "state.h"

using namespace std;

#define MAX_LEN 100000000

#define delete(x) {delete x; x = 0;}

State* CURRENT = 0;


void addChar(char c);
unsigned countTerminals();

int main() {
	//printf("Size of state: %d\n", sizeof(State));
    //printf("Size of arrayList: %d\n", sizeof(ArrayList<State>));
	//reading input
	char* word = new char[MAX_LEN + 1];
    scanf("%s", word);
    unsigned wordSize = strlen(word);
    printf("word size: %d\n", wordSize);

	//init
    State::init(2 * wordSize + 1);
	CURRENT = State::getNewState();

	//populating suffix automaton
	for (unsigned i = 0; word[i]; i++) {
		addChar(word[i]);
		//printf("%u\n", STATES_CNT);
	}

	//printing results
	printf("%u\n%llu\n%u", State::getStatesCount(), *getEdgesCount(), countTerminals());

	return 0;
}

//adding a char to the suffix automation
void addChar(char c) {
	// 1 - 27
	//c -= 'a';
	//c++;

	//creating a state
    State* newState = State::getNewState();
    *(newState->alpha) = c;
	*(newState->length) = *(CURRENT->length) + 1;

	State* state = CURRENT;
	//assigning missing edges to suffix links up to the start
	State* childState = 0;
	/*for (; state && !(childState = getStateByIx(childIx = state->getChildIx(c))); state = getStateByIx(state->suffixLink)){
		state->childrenStates.add(newStateIx);
        (*getEdgesCount())++;
	}*/
    while (state && !(childState = state->getChild(c))) {
        state->addChild(newState);
        (*getEdgesCount())++;

        State* nextState = State::getStateByIx(*(state->suffixLink));
        delete(state);
        state = nextState;
    }

	*(newState->suffixLink) = 0;
	if (childState) {
		//if a corresponing edge was found
        *(newState->suffixLink) = childState->ix;

		if (*(state->length) + 1 != *(childState->length)) {
			//creating a clone
            State* clone = childState->clone();
			*(clone->length) = *(state->length) + 1;
			/*for (; state && state->getChildIx(c) == childIx; state = getStateByIx(state->suffixLink)) {
				state->replaceChild(cloneIx);
			}*/
            while (state) {
                State* childState2 = state->getChild(c);
                if (!childState2 || childState2->ix != childState->ix) {
                    delete(childState2);
                    break;
                }

                state->replaceChild(clone);

                State* nextState = State::getStateByIx(*(state->suffixLink));
                delete(state);
                state = nextState;
            }

			*(newState->suffixLink) = *(childState->suffixLink) = clone->ix;
            delete(clone);
		}
    }

    delete(childState);
    delete(state);
	CURRENT = newState;
}

unsigned countTerminals() {
	unsigned terminals = 0;
    State* state = CURRENT;
    while (state) {
        terminals++;

        State* nextState = State::getStateByIx(*(state->suffixLink));
        delete(state);
        state = nextState;
    }
	return terminals;
}
