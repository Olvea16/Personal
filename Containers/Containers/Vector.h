#pragma once
template <typename T>
class Vector 
{
	// Classes
protected:
	template <typename Te>
	class element
	{
	public:
		element() {

		}
		element(Te value) {

		}
		Te value;
		Vector::element<Te>* next_element;
	};
public:
	Vector() {

	}
	~Vector();

	size_t size() {
		return vector_size;
	}

	T operator[](size_t index) {
		Vector::element<T>* element = get_element(index);
		return element->value;
	}

	void push(T value) {
		Vector::element<T>* new_element = new Vector::element<T>();
		new_element->value = value;
		if (first_element == NULL) {
			first_element = last_element = new_element;
		}
		else {
			last_element->next_element = new_element;
			last_element = new_element;
		}
		vector_size++;
	}

	class iterator
	{
	public:
		void operator++(T) {
			element = element->next_element;
		}

		T operator*() {
			return this->element->value;
		}

		bool operator!=(Vector<T>::iterator b) {
			return getAdress() != b.getAdress();
		}

		iterator();
		iterator(Vector::element<T>* element) : element(element) {
		}

		~iterator();

	private:
		Vector::element<T>* getAdress() {
			return this->element;
		}

		Vector::element<T>* element;
	};

	void remove(size_t index) {
		if (index < this->vector_size) {
			Vector::element<T>* element;
			Vector::element<T>* previous_element;
			Vector::element<T>* next_element;
			vector_size--;

			if (index == 0) {
				element = this->first_element;
				this->first_element = element->next_element;
				delete element;
				if (index == vector_size - 1) this->last_element = first_element;
			}
			else {
				previous_element = get_element(index - 1);
				element = previous_element->next_element;
				next_element = element->next_element;

				previous_element->next_element = next_element;
				delete element;

				if (index == vector_size - 1) this->last_element = next_element;
			}
		}

	}

	Vector::iterator begin() {
		return Vector::iterator(this->first_element);
	}

	Vector::iterator end() {
		return Vector::iterator(this->last_element->next_element);
	}

private:

	Vector::element<T>* first_element;
	Vector::element<T>* last_element;

	size_t vector_size;

	Vector::element<T>* get_element(size_t index) {
		Vector::element<T>* element = this->first_element;
		for (; index > 0; index--) {
			element = element->next_element;
		}
		return element;
	}

	
};

template<typename T>
inline Vector<T>::~Vector()
{
}

template<typename T>
inline Vector<T>::iterator::iterator()
{
}

template<typename T>
inline Vector<T>::iterator::~iterator()
{
}