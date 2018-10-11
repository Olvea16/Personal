#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <future>

#define NotGreaterThan(x,y) (x > y) ? (y):(x)
#define RoundUp_2(x) pow(2,ceil(log2(x)))
#define RoundDown_2(x) pow(2,floor(log2(x)))

class TreeElement;

class BinarySearchTree
{
public:
	typedef std::shared_ptr<TreeElement> pTreeElement;

	enum eTraversals { inorder, preorder, postorder, levelorder };

	BinarySearchTree() { };
	BinarySearchTree(size_t N, size_t threads = 0) {
		create(N, threads); 
		_size = N;
	}
	BinarySearchTree(std::vector<int> values, bool sorted = false, size_t threads = 0) { 
		//if (!sorted) elements = sort(elements); 
		create(values, threads);
		_size = values.size();
	}
	~BinarySearchTree() { };

	// Quieries
	bool contains(int value);
	bool isEmpty();
	int calculateInternalPathLength();
	std::vector<int> asVector(eTraversals traversal, size_t level = 0);
	void print();
	size_t size();

	// Manipulations
	void copyFrom(BinarySearchTree target);
	void create(size_t N, size_t threads);
	void create(std::vector<int> values, size_t threads);
	void makeEmpty();

private:
	pTreeElement root = nullptr;
	size_t _size = 0;

	// Quieries
	int calculateInternalPathLength(pTreeElement element, int height);
	std::vector<int> asVector(pTreeElement element, eTraversals traversal);
	std::vector<std::vector<std::string>> print(pTreeElement element);

	// Manipulations
	pTreeElement create(int base, int N, size_t threads);
	void create(pTreeElement element, std::vector<int>* values);
	void makeEmpty(pTreeElement element);

	// Traversals
	pTreeElement nextElement(int value, pTreeElement element);

	std::vector<pTreeElement> getLevel(pTreeElement element, size_t level);

};

class TreeElement
{
public:
	typedef std::shared_ptr<TreeElement> pTreeElement;

	TreeElement(int value, pTreeElement left = nullptr, pTreeElement right = nullptr) : value(value), left(left), right(right) { }
	~TreeElement() { }

	// This class is only supposed to be accessed from the BinarySearchTree class.
private:
	friend class BinarySearchTree;

	// Attributes
	int value;
	pTreeElement left;
	pTreeElement right;

	// Methods
	bool hasChildren() { return (left || right); }
	bool isFull() { return (left && right); }
};