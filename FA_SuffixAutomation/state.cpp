#include "state.h"
#include<string.h>

unsigned STATES_CNT = 0;
unsigned STATES_CAPACITY = 0;
unsigned long long EDGES_CNT = 0;

unsigned* statesLengths = 0;
unsigned* statesLinks = 0;
char* statesAlphas = 0;
unsigned char* statesChildrenCounts = 0;
unsigned** statesChildren = 0;

template <typename T>
T* mallocT(T*&arrPtr, unsigned size) {
    return arrPtr = (T*)malloc(size * sizeof(T));
}

State::State(unsigned ix) {
    this->ix = ix;
    this->suffixLink = &statesLinks[ix];
    this->length = &statesLengths[ix];
    this->alpha = &statesAlphas[ix];
}

State* State::clone() {
    State* clone = getNewState();
    clone->alpha = this->alpha;
    clone->suffixLink = this->suffixLink;

    unsigned char children = statesChildrenCounts[this->ix];
    if (children) {
        statesChildrenCounts[clone->ix] = children;
        statesChildren[clone->ix] = new unsigned[children];
        memcpy(statesChildren[clone->ix], statesChildren[this->ix], children * sizeof(unsigned));
        EDGES_CNT += children;
    }

    return clone;
}

void State::addChild(State * child) {
    unsigned char children = statesChildrenCounts[this->ix];
    unsigned* newArray = new unsigned[children + 1];
    if (children) {
        memcpy(newArray, statesChildren[this->ix], children * sizeof(unsigned));
        delete[] statesChildren[this->ix];
    }

    newArray[children] = child->ix;
    statesChildren[this->ix] = newArray;
    statesChildrenCounts[this->ix]++;
}

State* State::getChild(char c) {

    for (unsigned i = 0; i < statesChildrenCounts[ix]; i++) {
        State* child = getStateByIx(statesChildren[this->ix][i]);
        if (*(child->alpha) == c)
            return child;
        delete child;
    }

    return 0;
}

void State::replaceChild(State* state) {
    for (unsigned i = 0; i < statesChildrenCounts[this->ix]; i++) {
        State* child = getStateByIx(statesChildren[this->ix][i]);
        if (child->alpha == state->alpha) {
            statesChildren[this->ix][i] = state->ix;
            delete child;
            return;
        }
        delete child;
    }
}

void State::init(unsigned statesCapacity) {
    STATES_CAPACITY = statesCapacity;

    mallocT(statesLengths, statesCapacity);
    mallocT(statesLinks, statesCapacity);
    mallocT(statesAlphas, statesCapacity);
    mallocT(statesChildrenCounts, statesCapacity);
    mallocT(statesChildren, statesCapacity);
}

State* State::getNewState() {
    if (STATES_CNT == STATES_CAPACITY)
        return 0;

    State* newState = new State(STATES_CNT++);
    *(newState->alpha) = 0;
    *(newState->suffixLink) = -1;
    *(newState->length) = 0;
    statesChildrenCounts[newState->ix] = 0;
    return newState;
}

State* State::getStateByIx(unsigned ix) {
    if (STATES_CNT <= ix)
        return 0;

    return new State(ix);
}

unsigned long long* getEdgesCount() {
    return &EDGES_CNT;
}

unsigned State::getStatesCount() {
    return STATES_CNT;
}
