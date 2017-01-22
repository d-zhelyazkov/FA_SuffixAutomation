#include "state.h"

State* State::clone() {
    unsigned cloneIx = getNewState();
    State* clone = statesArray + cloneIx;
    clone->alpha = alpha;
    clone->suffixLink = suffixLink;

    clone->childrenStates = ArrayList<unsigned>(&childrenStates);
    EDGES_CNT += childrenStates.size;

    return clone;
}

State * State::getChild(char c) {

    //for (Node<State*>* curr = childrenStates->start; curr; curr = curr->next) {
    for (unsigned i = 0; i < childrenStates.size; i++) {
        State* child = statesArray + childrenStates.array[i];
        if (child->alpha == c)
            return child;
    }

    return 0;
}

void State::replaceChild(unsigned stateIx) {
    State* state = statesArray + stateIx;
    //for (Node<State*>* curr = childrenStates->start; curr; curr = curr->next) {
    for (unsigned i = 0; i < childrenStates.size; i++) {
        State* child = statesArray + childrenStates.array[i];
        if (child->alpha == state->alpha) {
            childrenStates.array[i] = stateIx;
            return;
        }
    }
}
