#ifndef OSTEST_VECTOR_H
#define OSTEST_VECTOR_H

#include "Math.h"

#define DEFAULT_VECTOR_SIZE 256
#define MIN_SIZE 2

template<class T>
class Vector
{
public:
	Vector();
	explicit Vector(int n);
	Vector(const Vector<T>& other);
	~Vector() = default;
	void deleteVector();

	unsigned int size() const;
	unsigned int capacity() const;
	unsigned int resizeFactor() const;
	bool empty() const;

	void pushBack(T val);
	void pushAll(const Vector<T>& vector);
	void insert(unsigned int index, T val);
	void assign(T val);
	T pop_back();
	void erase(int index);//only erases the element at the given index

	void reserve(unsigned int n);
	void resize(unsigned int n);
	void resize(unsigned int n, T val);

	T* begin() const;
	T* end() const;

	void clear();

	Vector<T>& operator=(const Vector<T>& other);
	T& operator[](unsigned int pos) const;
private:
	T* _elements;
	unsigned int _size;
	unsigned int _capacity;
	unsigned int _resizeFactor;
};

template<class T>
void Vector<T>::erase(int index)
{
	if(index < (int)this->_size)
	{
		this->_size--;
		this->_capacity = Math::ceil((double) this->_size / this->_resizeFactor) * this->_resizeFactor;
		T* newArray = new T[this->_capacity];

		for (int i = 0, j = 0; i < (int)this->_size; i++, j++)
		{
			if(index == j)
			{
				i--;//sub 1 from j so i will miss the value;
			}
			else
			{
				newArray[i] = this->_elements[j];
			}
		}
		delete this->_elements;
		this->_elements = newArray;
	}
	else
	{
		//error!
	}
}


template<class T>
T Vector<T>::pop_back()
{
	T tempVal = this->_elements[this->size() - 1];
	if (_size > 0)
	{
		this->resize(_size - 1);
		return tempVal;
	}
	else
	{
		//"error: pop from empty vector
		return 100000000;
	}
}
template<class T>
Vector<T>::Vector() : Vector(DEFAULT_VECTOR_SIZE)
{

}

template<class T>
Vector<T>::Vector(int n) : _size(0), _capacity(0) ,_resizeFactor(0)
{
	if(n < MIN_SIZE)
	{
		n = MIN_SIZE;
	}

	this->_elements = new T[n];
	this->_size = 0;
	this->_capacity = n;
	this->_resizeFactor = n;
}

template<class T>
Vector<T>::Vector(const Vector<T>& other)
{
	*this = other;
}

template<class T>
void Vector<T>::deleteVector()
{
	if (this->_elements)
	{
		delete[] this->_elements;
	}

	this->_elements = nullptr;
	this->_size = 0;
	this->_capacity = 0;
}


/*
template<class T>
Vector<T>::~Vector()
{
	if (this->_elements)
	{
		delete[] this->_elements;
	}

	this->_elements = nullptr;
	this->_size = 0;
	this->_capacity = 0;
}
*/
/*
Returns the size of the vector (total elements in the vector)

output:
	the size of the vector
*/
template<class T>
unsigned int Vector<T>::size() const
{
	return this->_size;
}

/*
Returns the capacity - how many elements it can hold without expanding

output:
	the capacity
*/
template<class T>
unsigned int Vector<T>::capacity() const
{
	return this->_capacity;
}

/*
Returns the resize factor - by how much the array would expand when it resizes

output:
	the resize factor
*/
template<class T>
unsigned int Vector<T>::resizeFactor() const
{
	return this->_resizeFactor;
}

template<class T>
bool Vector<T>::empty() const
{
	return this->size() == 0;
}

/*
Pushes a value to the end of the vector

input:
	val - value to add to the end of the vector
*/
template<class T>
void Vector<T>::pushBack(T val)
{
	this->reserve(this->_size + 1);
	this->_elements[this->_size] = val;
	this->_size += 1;
}

template<class T>
void Vector<T>::pushAll(const Vector<T>& vector)
{
	for(const T& t : vector)
	{
		this->pushBack(t);
	}
}

template<class T>
void Vector<T>::insert(unsigned int index, T val)
{
	if(index < this->_size)
	{
		this->_size++;
		this->_capacity = Math::ceil((double) this->_size / this->_resizeFactor) * this->_resizeFactor;
		T* newArray = new T[this->_capacity];
		for (unsigned int i = 0, j = 0; i < this->_size; i++, j++)
		{
			if(index == i)
			{
				newArray[i] = val;
				j--;//subtructing 1 from j so i wont miss a value;
			}
			else
			{
				newArray[i] = this->_elements[j];
			}
		}
		delete this->_elements;
		this->_elements = newArray;
	}
	else
	{
		//error!
	}

}

/*
Reserves specified N positions in the array.

input:
	n - minimum size the array must be able to hold
*/
template<class T>
void Vector<T>::reserve(unsigned int n)
{
	if (this->_capacity < n)
	{
		this->_capacity = Math::ceil((double)n / this->_resizeFactor) * this->_resizeFactor;
		T* newArray = new T[this->_capacity];
		for (unsigned int i = 0; i < this->_size; i++)
		{
			newArray[i] = this->_elements[i];
		}
		delete this->_elements;
		this->_elements = newArray;
	}
}

/*
Resizes the vector to the specified N size.

input:
	n - new size of the vector
*/
template<class T>
void Vector<T>::resize(unsigned int n)
{
	if (n <= this->_capacity)
	{
		// if n > size then add the elements (the size will be changed at the end of the method so if n < size then elements will be removed)
		for (unsigned int i = this->_size; i < n; i++)
		{
			this->pushBack(0);
		}
	}
	else
	{
		this->reserve(n);
	}
	// resize the array to the given size
	this->_size = n;
}

/*
Assigns the specified value to each element

input:
	val - value to assign
*/
template<class T>
void Vector<T>::assign(T val)
{
	for(int i = 0; i < this->_size; i++)
	{
		this->_elements[i] = val;
	}
}

/*
Resizes the vector and puts the specified val in the new elements (elements that were exposed from the enlargement, if the array wasn't enlarged then the val won't be used)

input:
	n - new size of the vector
	val - value to assign to new elements
*/
template<class T>
void Vector<T>::resize(unsigned int n, T val)
{
	unsigned int i = this->_size;
	this->resize(n);
	for(; i < n; i++)
	{
		this->_elements[i] = val;
	}
}

template<class T>
T* Vector<T>::begin() const
{
	return this->_elements;
}

template<class T>
T* Vector<T>::end() const
{
	return this->_elements + this->_size;
}

template<class T>
void Vector<T>::clear()
{
	this->_size = 0;
}

/*
Takes all the other vector's value to this vector.
*/
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if(this == &other)
	{
		return *this;
	}
	this->_size = other.size();
	this->_capacity = other.capacity();
	this->_resizeFactor = other.resizeFactor();
	this->_elements = new T[other.capacity()];
	for(unsigned int i = 0; i < other.capacity(); i++)
	{
		this->_elements[i] = other._elements[i];
	}
	return *this;
}

/*
Returns the element in the specified pos.
If the position is out of bounds then it will return the first element.

input:
	pos - position of the element
output:
	the element in the position or the first element if the pos is out of bounds
*/
template<class T>
T& Vector<T>::operator[](unsigned int pos) const
{
	if(pos < 0 || pos >= this->_size)
	{
		pos = 0;
	}
	return this->_elements[pos];
}

#endif //OSTEST_VECTOR_H
