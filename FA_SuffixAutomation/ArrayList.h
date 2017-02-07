#pragma once
#include<string.h>

template <typename T>
struct ArrayList {
    unsigned size = 0;
    T* array = 0;

    ArrayList() {}
    ArrayList(ArrayList* arrayList) {
        this->size = arrayList->size;
        array = new T[size];
        memcpy(array, arrayList->array, size * sizeof(T));
    }

    void add(T element) {
        T* newArray = new T[size + 1];
        if (array) {
            memcpy(newArray, array, size * sizeof(T));
            delete[] array;
        }

        newArray[size] = element;
        array = newArray;
        size++;
    }
};