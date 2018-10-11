#include "stdafx.h"
#include "BinarySearchTree.h"

bool BinarySearchTree::contains(int value)
{
	pTreeElement element = root;
	while (element && element->value != value) element = nextElement(value, element);

	// If value isnt found, the pointer will be NULL and this will return false. Otherwise it will return true.
	return (element.operator bool());
}

bool BinarySearchTree::isEmpty()
{
	return (root.operator bool());
}

int BinarySearchTree::calculateInternalPathLength()
{
	return calculateInternalPathLength(root, 0);
}

std::vector<int> BinarySearchTree::asVector(eTraversals traversal, size_t level)
{
	if (traversal != levelorder) return asVector(root, traversal);
	std::vector<pTreeElement> vec = getLevel(root, level);
	std::vector<int> result;
	for (pTreeElement ele : vec) result.push_back(ele->value);
	return result;
}

void BinarySearchTree::print()
{
	std::cout << std::endl;
	std::vector<std::vector<std::string>> vec = print(root);
	size_t layers = vec.size();
	int biggestSize = 0;
	for (int i = 0; i < vec.size(); i++) for (int j = 0; j < vec[i].size(); j++) if (vec[i][j].size() > biggestSize) biggestSize = vec[i][j].size();

	for (int l = layers; l > 0; l--) {
		int padding = (pow(2,l) - 1) * biggestSize;

		for (int i = 0; i < vec[layers - l].size(); i++) {
			std::cout << std::setw(ceil(padding / 2.0)) << "" << std::setw(biggestSize) << vec[layers - l][i] << std::setw(floor(padding / 2.0)) << "";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

size_t BinarySearchTree::size()
{
	return _size;
}

void BinarySearchTree::copyFrom(BinarySearchTree target)
{
}

void BinarySearchTree::create(size_t N, size_t threads)
{
	makeEmpty();
	root = create(-1, N, threads);
}

void BinarySearchTree::create(std::vector<int> values, size_t threads)
{
	create(values.size(), threads);
	create(root, &values);
}

void BinarySearchTree::makeEmpty()
{
	makeEmpty(root);
	_size = 0;
}

int BinarySearchTree::calculateInternalPathLength(pTreeElement element, int height)
{
	if (element->isFull() && (element->left->isFull() || element->right->isFull())) {
		int result = 0;
		if (element->left->isFull()) result += calculateInternalPathLength(element->left, height + 1);
		if (element->right->isFull()) result += calculateInternalPathLength(element->right, height + 1);
		return result;
	}
	return height;
}

std::vector<int> BinarySearchTree::asVector(pTreeElement element, eTraversals traversal)
{
	std::vector<int> result;
	if (element) {
		std::vector<int> left = asVector(element->left, traversal);
		std::vector<int> right = asVector(element->right, traversal);

		switch (traversal) {
		case inorder:
			if (element->left) result.insert(result.end(), left.begin(), left.end());
			result.push_back(element->value);
			if (element->right)  result.insert(result.end(), right.begin(), right.end());
			break;

		case preorder:
			result.push_back(element->value);
			if (element->left) result.insert(result.end(), left.begin(), left.end());
			if (element->right)  result.insert(result.end(), right.begin(), right.end());
			break;

		case postorder:
			if (element->left) result.insert(result.end(), left.begin(), left.end());
			if (element->right)  result.insert(result.end(), right.begin(), right.end());
			result.push_back(element->value);
			break;
		}
	}
	return result;
}

std::vector<std::vector<std::string>> BinarySearchTree::print(pTreeElement element)
{
	if (element) {
		std::vector<std::vector<std::string>> result;
		std::vector<std::vector<std::string>> leftString = print(element->left);
		std::vector<std::vector<std::string>> rightString = print(element->right);

		result.push_back(std::vector<std::string>({ std::to_string(element->value) }));
		for (int i = 0; i < leftString.size() || i < rightString.size(); i++) {
			std::vector<std::string> row;
			if (i < leftString.size()) {
				row = leftString[i];
				if (i < rightString.size()) {
					row.insert(row.end(), rightString[i].begin(), rightString[i].end());
				}
			}
			else if (i < rightString.size()) {
				row = rightString[i];
			}
			result.push_back(row);
		}
		return result;
	}
}

std::shared_ptr<TreeElement> BinarySearchTree::create(int base, int N, size_t threads)
{
	if (N > 0) {
		int fullChildren = (RoundDown_2(N) - 2) / 2;
		int leaves = NotGreaterThan(N - fullChildren * 2 - 1, RoundDown_2(N) / 2);
		int leftNodes = fullChildren + leaves;
		int value = fullChildren + leaves + 1;
		pTreeElement result(new TreeElement(value + base));
		N--;

		if (threads > 0 && threads < 3) {
			std::future<pTreeElement> left, right;
			if (leftNodes > 0) {
				if (N - leftNodes > 0 && threads == 2) {
					left = std::async(std::launch::async, [this, base, leftNodes, threads] {return create(base, leftNodes, ceil(threads / 2.0)); });
					right = std::async(std::launch::async, [this, base, value, N, leftNodes, threads] {return create(base + value, N - leftNodes, floor(threads / 2.0)); });

					result->left = left.get();
					result->right = right.get();
				}
				else {
					left = std::async(std::launch::async, [this, base, leftNodes, threads] {return create(base, leftNodes, threads - 1); });
					if (N - leftNodes > 0) result->right = create(base + value, N - leftNodes, threads);
					result->left = left.get();
				}
			}
			else if (N - leftNodes > 0) {
				right = std::async(std::launch::async, [this, base, value, N, leftNodes, threads] {return create(base + value, N - leftNodes, threads - 1); });
				result->right = right.get();
			}
		}
		else {
			if (leftNodes > 0) result->left = create(base, leftNodes, threads / 2);
			if (N - leftNodes > 0) result->right = create(base + value, N - leftNodes, threads / 2);
		}
		return result;
	}
	return nullptr;
}

void BinarySearchTree::create(pTreeElement element, std::vector<int>* values)
{
	if (element) {
		element->value = (*values)[element->value];
		create(element->left, values);
		create(element->right, values);
	}
}

void BinarySearchTree::makeEmpty(pTreeElement element)
{
	if (element) {
		makeEmpty(element->left);
		makeEmpty(element->right);
		element = nullptr;
	}
}

std::shared_ptr<TreeElement> BinarySearchTree::nextElement(int value, pTreeElement element)
{
	// if already pointing to null element. Exception could be thrown here.
	if (!element) return nullptr;

	if (value < element->value) return element->left;
	if (value > element->value) return element->right;
	return element;
}

std::vector<std::shared_ptr<TreeElement>> BinarySearchTree::getLevel(pTreeElement element, size_t level)
{
	std::vector<pTreeElement> result;
	if (element) {
		if (level == 0) result.push_back(element);
		else {
			std::vector<pTreeElement> left = getLevel(element->left, level - 1);
			std::vector<pTreeElement> right = getLevel(element->right, level - 1);

			if (element->left) result.insert(result.end(), left.begin(), left.end());
			if (element->right) result.insert(result.end(), right.begin(), right.end());
		}
	}
	return result;
}
