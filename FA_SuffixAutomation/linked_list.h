#pragma once

template <typename T>
struct Node {
	Node* next = 0;
	T data;

	Node(T data) : data(data) {}
};

template <typename T>
struct LinkedList {
	Node<T>* start = 0;

	LinkedList() {}
	LinkedList(LinkedList<T>* linkedList) {
		for (Node<T>* node = linkedList->start; node; node = node->next) {
			this->add(node->data);
		}
	}

	void add(T elem) {
		Node<T>* node = new Node<T>(elem);
		if (start) {
			Node<T>* curr = start;
			for (; curr->next; curr = curr->next);
			curr->next = node;
		}
		else {
			start = node;
		}
	}

	unsigned getSize() {
		unsigned count = 0;
		for (Node<T>* curr = start; curr; curr = curr->next, count++);
		return count;
	}
};
