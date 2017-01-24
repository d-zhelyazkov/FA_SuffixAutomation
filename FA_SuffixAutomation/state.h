#pragma once

//#include"linked_list.h"
#include "ArrayList.h"
#include <stdlib.h>

unsigned STATES_CNT = 0;
unsigned STATES_CAPACITY = 0;
unsigned long long EDGES_CNT = 0;

struct State {
	char alpha = 0;
	unsigned length = 0;
	unsigned suffixLink = -1;
	//LinkedList<State*>* childrenStates = 0;
    ArrayList<unsigned> childrenStates;

    unsigned clone();
    unsigned getChildIx(char c);
    void replaceChild(unsigned stateIx);
};


State* statesArray = 0;

State* init(unsigned statesCapacity) {
    STATES_CAPACITY = statesCapacity;
    return statesArray = (State*)malloc(sizeof(State) * statesCapacity);
}

unsigned getNewStateIx() {
    if (STATES_CNT == STATES_CAPACITY)
        return -1;
    return STATES_CNT++;
}

State* getNewState() {
    if (STATES_CNT == STATES_CAPACITY)
        return 0;
    return statesArray + STATES_CNT++;
}

State* getStateByIx(unsigned ix) {
    if (STATES_CNT <= ix)
        return 0;
    return statesArray + ix;
}

