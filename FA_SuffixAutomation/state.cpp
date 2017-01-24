#include "state.h"

unsigned State::clone() {
    unsigned cloneIx = getNewStateIx();
    State* clone = getStateByIx(cloneIx);
    clone->alpha = alpha;
    clone->suffixLink = suffixLink;

    clone->childrenStates = ArrayList<unsigned>(&childrenStates);
    EDGES_CNT += childrenStates.size;

    return cloneIx;
}

unsigned State::getChildIx(char c) {

    //for (Node<State*>* curr = childrenStates->start; curr; curr = curr->next) {
    for (unsigned i = 0; i < childrenStates.size; i++) {
        unsigned childIx = childrenStates.array[i];
        State* child = getStateByIx(childIx);
        if (child->alpha == c)
            return childIx;
    }

    return -1;
}

void State::replaceChild(unsigned stateIx) {
    State* state = getStateByIx(stateIx);
    //for (Node<State*>* curr = childrenStates->start; curr; curr = curr->next) {
    for (unsigned i = 0; i < childrenStates.size; i++) {
        State* child = getStateByIx(childrenStates.array[i]);
        if (child->alpha == state->alpha) {
            childrenStates.array[i] = stateIx;
            return;
        }
    }
}
