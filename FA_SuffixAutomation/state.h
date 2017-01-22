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

    State* clone();
    State* getChild(char c);
    void replaceChild(unsigned stateIx);
};


State* statesArray = 0;

State* init(unsigned statesCapacity) {
    return statesArray = (State*)malloc(sizeof(State) * statesCapacity);
}

unsigned getNewState() {
    return STATES_CNT++;
}