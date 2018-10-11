#pragma once
#include <string>

int findNextPrime(int n);
template <typename Tk, typename Tv>
class HashtableElement;


template <typename Tk, typename Tv>
class Hashtable
{
public:
	enum eProbingType { Linear, Quadratic };

	Hashtable(size_t size, eProbingType probingType = Quadratic) {
		_size = findNextPrime(size);
		array = new Tv[_size];
	}
	~Hashtable() {}

	size_t size();

	void ins(Tk key, Tv value);
	void del(Tk key);
	Tv get(Tk key);

	void resize(size_t size = 0);

private:
	size_t _size;
	Tv* array;
	eProbingType probing;

	size_t hashFunc(Tk key);
};

template <typename Tv>
class Hashtable<std::string, Tv> {
public:
	Hashtable(size_t size) {
		_size = findNextPrime(size);
		array = new HashtableElement<std::string, Tv>[_size];
	}
	~Hashtable() {}

	size_t size();

	void ins(std::string key, Tv value);
	void del(std::string key);
	Tv get(std::string key);

	void resize(size_t size = 0);

private:
	size_t _size;
	HashtableElement<std::string, Tv>* array;
	eProbingType probing;

	size_t hashFunc(std::string key);
	size_t probingFunc(size_t currentIndex);
};

template <typename Tk, typename Tv>
class HashtableElement {
	HashtableElement() {}
	HashtableElement(Tk key, Tv value, bool flag = true) : key(key), value(value), valid(flag) {}
	~HashtableElement() {}
private:
	friend class Hashtable<Tk, Tv>;
	Tv value;
	Tk key;
	bool valid = false;
};

template<typename Tk, typename Tv>
size_t Hashtable<Tk, Tv>::size()
{
	return size_t();
}

template<typename Tv>
inline void Hashtable<std::string, Tv>::ins(std::string key, Tv value)
{
	size_t index = hashFunc(key);
	HashtableElement<std::string, Tv>* element = &(array[index]);
	if (!element->valid) array[index] = HashtableElement<std::string, Tv>(key, value);
	else {
		size_t probingindex = 0;
		while (element->valid) {
			probingindex = probingFunc(probingindex);
		}
	}
}

template<typename Tv>
inline void Hashtable<std::string, Tv>::del(std::string key)
{
}

template<typename Tv>
inline Tv Hashtable<std::string, Tv>::get(std::string key)
{
	size_t index = hashFunc(key);
	HashtableElement<std::string, Tv>* element = array[index];
	if (element->key == key) return element->value;
	size_t probingOffset = 0;
	probingOffset = probingFunc(probingOffset);
}

template<typename Tk, typename Tv>
inline void Hashtable<Tk, Tv>::ins(Tk key, Tv value)
{
	size_t index = hashFunc(key);
	array[index] = HashtableElement<Tk, Tv>(key, value);
}

template<typename Tk, typename Tv>
inline void Hashtable<Tk, Tv>::del(Tk key)
{

}

template<typename Tk, typename Tv>
inline Tv Hashtable<Tk, Tv>::get(Tk key)
{
	return Tv();
}

template<typename Tk, typename Tv>
inline void Hashtable<Tk, Tv>::resize(size_t size)
{

}

template<typename Tv>
inline size_t Hashtable<std::string, Tv>::hashFunc(std::string key)
{
	size_t result = 0;
	for (char c : key) result = 37 * result + c;
	result %= _size;
	return result;
}

template<typename Tv>
inline size_t Hashtable<std::string, Tv>::probingFunc(size_t currentIndex)
{
	switch (probing) {
	case Quadratic: return pow(sqrt(currentIndex) + 1, 2);
		break;

	case Linear: return currentIndex + 1;
		break;
	}
}

template<typename Tk, typename Tv>
inline size_t Hashtable<Tk, Tv>::hashFunc(Tk key)
{
	return size_t();
}

