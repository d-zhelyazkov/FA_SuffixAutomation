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
    if(wordSize && wordSize <= 100)
        printf("Word:\t\t%s\n",word);
    printf("Word size:\t%u\n", wordSize);

    //init
    init(2 * wordSize + 1);
    START = CURRENT = getNewState();

    //populating suffix automaton
    for (unsigned i = 0; word[i]; i++) {
        addChar(word[i]);
    }

    //printing results
    printf("States:\t\t%u\nEdges:\t\t%llu\nTerminals:\t%u\n", STATES_CNT, EDGES_CNT, countTerminals());

    return 0;
}

//adding a char to the suffix automation
void addChar(char c) {

    //creating a state
    unsigned newState = getNewState();
    //statesAlphas[newState] = c;
    statesLengths[newState] = statesLengths[CURRENT] + 1;
    statesLinks[newState] = START;

    //assigning missing edges to suffix links up to the start
    for (unsigned state = CURRENT; state; state = statesLinks[state]){
        unsigned childState = getChild(state, c);
        if (!childState) {
            //addChild(state, newState);
            setChild(state, newState, c);
        }
        else {
            //a corresponing edge was found

            if (statesLengths[state] + 1 == statesLengths[childState]) {
                statesLinks[newState] = childState;
            } else {
                //creating a clone
                unsigned clone = cloneState(childState);
                statesLengths[clone] = statesLengths[state] + 1;
                for (; state && getChild(state, c) == childState; state = statesLinks[state]) {
                    //replaceChild(state, clone);
                    setChild(state, clone, c);
                }

                statesLinks[newState] = statesLinks[childState] = clone;
            }

            break;
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
