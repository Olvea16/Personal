#pragma once

#include <math.h>
#define max(a,b) ((a > b) ? (a) : (b))

template <typename T>
class AVLTreeElement;

template <typename T>
class AVLTree
{
public:
	AVLTree() {
	}

	~AVLTree() {
	}

	bool remove(T value);
	bool insert(T value);
	bool contains(T value);
	T findMin();
	T findMax();
	size_t size();
	size_t height();
	bool isEmpty();
	void makeEmpty();

private:
	void insert(T value, AVLTreeElement<T>** element);
	bool contains(T value, AVLTreeElement<T>** element);
	T findMin(AVLTreeElement<T>* element);
	T findMax(AVLTreeElement<T>* element);
	size_t height(AVLTreeElement<T>* element);
	AVLTreeElement<T>** findElement(T value, AVLTreeElement<T>** element);
	AVLTreeElement<T>** findElement(T value);

	void balance(AVLTreeElement<T>** element);
	void rotateLeft(AVLTreeElement<T>** element);
	void rotateRight(AVLTreeElement<T>** element);

	AVLTreeElement<T>* firstElement = NULL;
	size_t _size = 0;
};

template<typename T>
class AVLTreeElement {
public:
	~AVLTreeElement() { }

private:
	friend class AVLTree<T>;

	T value;
	AVLTreeElement<T>* left = NULL;
	AVLTreeElement<T>* right = NULL;
	int height, balance;

	AVLTreeElement() {}
	AVLTreeElement(T value, AVLTreeElement<T>* left = NULL, AVLTreeElement<T>* right = NULL) : value(value), left(left), right(right) { }
};

template<typename T>
inline bool AVLTree<T>::remove(T value)
{
	AVLTreeElement<T>** rootElement = findElement(value);
	if (rootElement == NULL) return false;

	AVLTreeElement<T>** leftElement = &((*rootElement)->left);
	AVLTreeElement<T>** rightElement = &((*rootElement)->right);


	AVLTreeElement<T>** nextElement = rightElement;

	return true;
}

template<typename T>
inline bool AVLTree<T>::insert(T value)
{
	if (contains(value)) return false;
	insert(value, &firstElement);
	balance(&firstElement);
	return true;
}

template<typename T>
inline bool AVLTree<T>::contains(T value)
{
	return contains(value, &firstElement);
}

template<typename T>
inline T AVLTree<T>::findMin()
{
	return findMin(firstElement);
}

template<typename T>
inline T AVLTree<T>::findMax()
{
	return findMax(firstElement);
}

template<typename T>
inline size_t AVLTree<T>::size()
{
	return _size;
}

template<typename T>
inline size_t AVLTree<T>::height()
{
	return height(firstElement);
}

template<typename T>
inline bool AVLTree<T>::isEmpty()
{
	return (firstElement == NULL);
}

template<typename T>
inline void AVLTree<T>::makeEmpty()
{
}

template<typename T>
inline void AVLTree<T>::insert(T value, AVLTreeElement<T>** element)
{
	if (*element == NULL) (*element) = new AVLTreeElement<T>{ value };
	else {
		AVLTreeElement<T>** nextElement;
		if (value < (*element)->value) nextElement = &((*element)->left);
		else nextElement = &((*element)->right);
		insert(value, nextElement);
	}
}

template<typename T>
inline bool AVLTree<T>::contains(T value, AVLTreeElement<T>** element) {
	return (findElement(value, element) != NULL);
}

template<typename T>
inline T AVLTree<T>::findMin(AVLTreeElement<T>* element)
{
	AVLTreeElement<T>* nextElement = element->left;
	if (nextElement == NULL) return element->value;
	else return findMin(&nextElement);
}

template<typename T>
inline T AVLTree<T>::findMax(AVLTreeElement<T>* element)
{
	AVLTreeElement<T>* nextElement = element->right;
	if (nextElement == NULL) return element->value;
	else return findMin(nextElement);
}

template<typename T>
inline size_t AVLTree<T>::height(AVLTreeElement<T>* element)
{
	if (element == NULL) return 0;
	return max(height(element->left), height(element->right)) + 1;
}

template<typename T>
inline AVLTreeElement<T>** AVLTree<T>::findElement(T value, AVLTreeElement<T>** element)
{
	if (*element == NULL) return NULL;
	T elVal = (*element)->value;
	if (elVal == value) return element;

	if (value < elVal) return findElement(value, &((*element)->left));
	else return findElement(value, &((*element)->left));
}

template<typename T>
inline AVLTreeElement<T>** AVLTree<T>::findElement(T value)
{
	return findElement(value, &firstElement);
}

template<typename T>
inline void AVLTree<T>::balance(AVLTreeElement<T>** element)
{
	if (*element != NULL) {
		balance(&((*element)->left));
		balance(&((*element)->right));

		if (height((*element)->left) > height((*element)->right) + 1) {
			rotateLeft(element);
		}

		if (1 + height((*element)->left) < height((*element)->right)) {
			rotateRight(element);
		}
	}
}

template<typename T>
inline void AVLTree<T>::rotateLeft(AVLTreeElement<T>** element)
{
	if (*element == NULL || (*element)->left == NULL) return;
	if (height((*element)->left->right) > height((*element)->left->left)) rotateRight(&((*element)->left));

	AVLTreeElement<T>* leftElement = (*element)->left;

	(*element)->left = (*element)->left->right;
	leftElement->right = (*element);
	(*element) = leftElement;
}

template<typename T>
inline void AVLTree<T>::rotateRight(AVLTreeElement<T>** element)
{
	if (*element == NULL || (*element)->right == NULL) return;
	if (height((*element)->right->left) > height((*element)->right->right)) rotateRight(&((*element)->right));

	AVLTreeElement<T>* rightElement = (*element)->right;

	(*element)->right = (*element)->right->left;
	rightElement->left = *element;
	*element = rightElement;
}

