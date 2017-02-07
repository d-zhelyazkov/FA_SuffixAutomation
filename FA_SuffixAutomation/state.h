#pragma once

#include <stdlib.h>

class State {

    State(unsigned ix);

public:

    static void init(unsigned statesCapacity);
    static State* getNewState();
    static unsigned getStatesCount();
    static State* getStateByIx(unsigned ix);


    unsigned ix = -1;
	unsigned* length = 0;
	unsigned* suffixLink = 0;
    char* alpha = 0;


    State* clone();
    void addChild(State* child);
    State* getChild(char c);
    void replaceChild(State* state);

};

unsigned long long* getEdgesCount();
