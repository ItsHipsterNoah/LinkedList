#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <iostream>

struct Node
{
	int data{ 0 };
	Node* next{nullptr};
};

class LinkedList
{
public:
	LinkedList() {};
	void makeEmpty();
	bool isFull() const;
	int getLength() const;
	int getItem(int item);
	void insertNode(int data);
	void insertNode(int data, int pos);
	void deleteItem(int data);
	void resetList();
	int getNextItem();
	void printList();
	virtual ~LinkedList();
private:
	void reset();
	Node* head{ nullptr };
	int length{ 0 };
	Node* currentPos{ nullptr }; 
};

int main()
{
	int number;
    std::cout << "Enter a number: ";
	std::cin >> number;
	LinkedList list;
	list.insertNode(number);
	list.insertNode(4);
	list.insertNode(3);
	list.insertNode(2);
	list.insertNode(1, 5);
	list.printList();
	for (int i = 5; i != 0; i--) {
		list.deleteItem(i);
	}
	std::cout << std::endl;
	list.printList();
	_CrtDumpMemoryLeaks();
}

void LinkedList::makeEmpty()
{
	Node* temp{ nullptr };
	currentPos = head;
	while (currentPos) {
		temp = currentPos->next;
		delete currentPos;
		currentPos = temp;
	}
	delete temp;
	delete currentPos;
	head = nullptr;
	length = 0;
	reset();
}

bool LinkedList::isFull() const
{
	Node* newNode{ nullptr };
	try {
		Node* newNode = new Node();
		delete newNode;
	}
	catch (std::bad_alloc & e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

int LinkedList::getLength() const
{
	return length;
}

int LinkedList::getItem(int item)
{
	reset();
	while (currentPos) {
		if (currentPos->data == item) {
			return currentPos->data;
		}
		else {
			currentPos = currentPos->next;
		}
	}
	std::cout << "Could not find item" << std::endl;
	return -1;
}

void LinkedList::insertNode(int data)
{
	Node* newNode{ nullptr };
	try {
		Node* newNode = new Node();
		newNode->data = data;
		if (!head) { // if the list is empty, create a new node at the head
			head = newNode;
			currentPos = head;
			length++;
		}
		else {
			while (currentPos->next) {
				currentPos = currentPos->next;
			}
			currentPos->next = newNode;
			length++;
		}
	}
	catch(std::bad_alloc & e) {
		std::cout << e.what() << std::endl;
	}
}

void LinkedList::insertNode(int data, int pos)
{
	reset();
	if (pos == 1) {
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = head;
		head = newNode;
		length++;
	}
	else if (pos > length) {
		while (currentPos->next) {
			currentPos = currentPos->next;
		}
		Node* newNode = new Node();
		newNode->data = data;
		currentPos->next = newNode;
		length++;
	}
	else if(pos > 1) {
		Node* prevPtr = { nullptr };
		for (int i = 0; i < pos-2; i++) {
			currentPos = currentPos->next;
		}
		Node* newNode = new Node();
		newNode->data = data;
		if (currentPos->next) {
			newNode->next = currentPos->next;
			currentPos->next = newNode;
			length++;
		}
	}
	else {
		std::cout << "ERROR! Cannot insert node at an index below 1." << std::endl;
	}
}

void LinkedList::deleteItem(int data)
{
	reset();
	if (head && head->data == data) {
		Node* temp = head->next;
		delete head;
		head = temp;
		length--;
	}
	else {
		while (currentPos->next) {
			if (currentPos->next->data == data) {
				Node* temp = currentPos->next->next;
				delete currentPos->next;
				currentPos->next = temp;
				length--;
			}
			else {
				currentPos = currentPos->next;
			}
		}
	}
}

int LinkedList::getNextItem()
{
	if (currentPos->next) {
		return currentPos->next->data;
	}
}

void LinkedList::printList()
{
	if (!head) {
		std::cout << "ERROR! List is empty!" << std::endl;
	}
	else {
		currentPos = head;
		std::cout << currentPos->data << std::endl;
		while (currentPos->next) {
			currentPos = currentPos->next;
			std::cout << currentPos->data << std::endl;
		}
	}
	reset();
}

LinkedList::~LinkedList()
{
	makeEmpty();
}

void LinkedList::reset()
{
	currentPos = head;
}
