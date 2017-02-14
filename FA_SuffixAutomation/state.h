#pragma once
#include <stdlib.h>


extern unsigned STATES_CNT;
extern unsigned long long EDGES_CNT;

extern unsigned* statesLengths;
extern unsigned* statesLinks;
//extern char* statesAlphas;
extern char* statesChildEdge;
extern unsigned** statesChildren;
extern unsigned char* statesChildrenCounts;


void init(unsigned statesCapacity);
unsigned getNewState();
unsigned cloneState(unsigned state);
void setChild(unsigned state, unsigned child, char edge);
//void addChild(unsigned state, unsigned child);
//void replaceChild(unsigned state, unsigned newChild);
unsigned getChild(unsigned state, char edge);
