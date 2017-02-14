#include "state.h"
#include<string.h>
#include <stdio.h>

#define CHILDREN_SIZE 26
enum ChildrenCount { ZERO, ONE, MANY };

//externs
unsigned STATES_CNT = 0;
unsigned long long EDGES_CNT = 0;

unsigned* statesLengths = 0;
unsigned* statesLinks = 0;
//char* statesAlphas = 0;
char* statesChildEdge = 0;
unsigned** statesChildren = 0;
unsigned char* statesChildrenCounts = 0;


template <typename T>
void templateCalloc(T*&arrPtr, unsigned size) {
    arrPtr = (T*)calloc(size, sizeof(T));
}

void init(unsigned statesCapacity) {
    templateCalloc(statesLengths, statesCapacity);
    templateCalloc(statesLinks, statesCapacity);
    //templateCalloc(statesAlphas, statesCapacity);
    templateCalloc(statesChildEdge, statesCapacity);
    templateCalloc(statesChildrenCounts, statesCapacity);
    templateCalloc(statesChildren, statesCapacity);
}

unsigned getNewState() {
    STATES_CNT++;

    return STATES_CNT;
}

ChildrenCount getStateChildrenCount(unsigned state) {
    return (!statesChildren[state]) ? ZERO :
        (statesChildEdge[state]) ? ONE : MANY;
}

unsigned cloneState(unsigned state) {
    unsigned clone = getNewState();
    //statesAlphas[clone] = statesAlphas[state];
    statesChildEdge[clone] = statesChildEdge[state];
    statesLinks[clone] = statesLinks[state];

    //copy children array
    unsigned char childrenCount = statesChildrenCounts[clone] = statesChildrenCounts[state];
    /*if (childrenCount) {
        statesChildren[clone] = new unsigned[childrenCount];
        memcpy(statesChildren[clone], statesChildren[state], childrenCount * sizeof(unsigned));
        EDGES_CNT += childrenCount;
    }*/
    switch (getStateChildrenCount(state)) {
    case ZERO:
        break;
    case ONE:
        statesChildren[clone] = new unsigned(*(statesChildren[state]));
        EDGES_CNT++;
        break;
    case MANY:
        statesChildren[clone] = new unsigned[CHILDREN_SIZE];
        memcpy(statesChildren[clone], statesChildren[state], CHILDREN_SIZE * sizeof(unsigned));
        for (unsigned i = 0; i < CHILDREN_SIZE; i++) {
            if (statesChildren[clone][i])
                EDGES_CNT++;
        }
        break;
    }
        
    return clone;
}

void setChild(unsigned state, unsigned child, char edge) {
    switch (getStateChildrenCount(state)) {
    case ZERO:
        statesChildEdge[state] = edge;
        statesChildren[state] = new unsigned(child);
        EDGES_CNT++;
        break;
    case ONE: {
        unsigned existingChild = *(statesChildren[state]);
        if (statesChildEdge[state] == edge) {
            *(statesChildren[state]) = child;
        }
        else {
            delete statesChildren[state];
            templateCalloc(statesChildren[state], CHILDREN_SIZE);
            statesChildren[state][statesChildEdge[state] - 'a'] = existingChild;
            statesChildren[state][edge - 'a'] = child;
            statesChildEdge[state] = 0;
            EDGES_CNT++;
        }
        break;
    }
    case MANY: {
            char normalizedAlpha = edge - 'a';
            if (!statesChildren[state][normalizedAlpha])
                EDGES_CNT++;
            statesChildren[state][normalizedAlpha] = child;
        }
        break;
    }

}

//void addChild(unsigned state, unsigned child) {
//    unsigned childrenCount = statesChildrenCounts[state];
//    unsigned* newArray = new unsigned[childrenCount + 1];
//    if (childrenCount) {
//        memcpy(newArray, statesChildren[state], childrenCount * sizeof(unsigned));
//        delete[] statesChildren[state];
//    }
//
//    newArray[childrenCount] = child;
//    statesChildren[state] = newArray;
//    statesChildrenCounts[state] ++;
//    EDGES_CNT++;
//}
//
//void replaceChild(unsigned state, unsigned newChild) {
//    for (unsigned char i = 0; i < statesChildrenCounts[state]; i++) {
//        unsigned child = statesChildren[state][i];
//        if (statesAlphas[child] != statesAlphas[newChild])
//            continue;
//        
//        statesChildren[state][i] = newChild;
//        break;
//    }
//}

unsigned getChild(unsigned state, char edge) {

    /*for (unsigned char i = 0; i < statesChildrenCounts[state]; i++) {
        unsigned child = statesChildren[state][i];
        if (statesAlphas[child] == edge)
            return child;
    }

    return 0;*/

    switch (getStateChildrenCount(state)) {
    case ZERO:
        return 0;
    case ONE: {
            unsigned child = *(statesChildren[state]);
            return (statesChildEdge[state] == edge) ? child : 0;
        }
    case MANY:
        return statesChildren[state][edge - 'a'];
    }
}