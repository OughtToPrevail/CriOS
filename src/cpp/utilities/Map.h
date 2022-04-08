#ifndef OSTEST_MAP_H
#define OSTEST_MAP_H

#include "Vector.h"
#include "Hash.h"

#define DEFAULT_MAP_VECTOR_SIZE (1 << 8)
#define DEFAULT_LOADING_FACTOR 0.75

template<class K, class V>
class MapNode
{
public:
	MapNode(const K& key, const V& value) : _key(key), _value(value), _next(nullptr)
	{

	}

	void setValue(V value)
	{
		this->_value = value;
	}

	void setNext(MapNode<K, V>* next)
	{
		this->_next = next;
	}

	K& getKey()
	{
		return this->_key;
	}

	V& getValue()
	{
		return this->_value;
	}

	MapNode<K, V>* getNext() const
	{
		return this->_next;
	}
private:
	K _key;
	V _value;
	MapNode<K, V>* _next;
};

template<class K, class V>
class Map
{
public:
	Map();
	// ~Map(); // TODO: In the future when destructors are added remove all the nodes

	void put(const K& key, const V& value);
	V* get(const K& key);
	V getWithDefault(K key, K defaultValue);
private:
	unsigned int indexKeyFor(const Vector<MapNode<K, V>*>& vector, K key);
	void putInVector(Vector<MapNode<K, V>*>& vector, MapNode<K, V>* node);
	void updateSize();

	Vector<MapNode<K, V>*> _vector;  // vector but acts as array really, always has capacity of power of 2's
	float _loadingFactor;  // a number between 0 and 1 which defines how full the vector should be before expanding
	unsigned int _threshold;  // when the capacity passes this number, it should resize the vector
};

template<class K, class V>
Map<K, V>::Map() : _vector(DEFAULT_MAP_VECTOR_SIZE), _loadingFactor(DEFAULT_LOADING_FACTOR), _threshold(DEFAULT_LOADING_FACTOR * this->_vector.capacity())
{

}

template<class K, class V>
void Map<K, V>::put(const K& key, const V& value)
{
	MapNode<K, V>* newNode = new MapNode<K, V>(key, value);
	this->putInVector(this->_vector, newNode);
	this->updateSize();
}

template<class K, class V>
V* Map<K, V>::get(const K& key)
{
	unsigned int minIndex = this->indexKeyFor(this->_vector, key);
	MapNode<K, V>* node = this->_vector[minIndex];
	while(node != nullptr)
	{
		if(node->getKey() == key)
		{
			return &node->getValue();
		}
		node = node->getNext();
	}
	return nullptr;
}

template<class K, class V>
V Map<K, V>::getWithDefault(K key, K defaultValue)
{
	V* valuePointer = this->get(key);
	if(valuePointer == nullptr)
	{
		return defaultValue;
	}
	return *valuePointer;
}

template<class K, class V>
unsigned int Map<K, V>::indexKeyFor(const Vector<MapNode<K, V>*>& vector, K key)
{
	return (vector.capacity() - 1) & Hash::hash(key);
}

template<class K, class V>
void Map<K, V>::putInVector(Vector<MapNode<K, V>*>& vector, MapNode<K, V>* node)
{
	unsigned int index = this->indexKeyFor(vector, node->getKey());
	MapNode<K, V>* current = vector[index];
	if(current == nullptr)
	{
		this->_vector.insert(index, node);
	} else
	{
		while(current->getNext() != nullptr)
		{
			current = current->getNext();
		}
		current->setNext(node);
	}
}

template<class K, class V>
void Map<K, V>::updateSize()
{
	if(this->_vector.size() < this->_threshold)
	{
		return;
	}
	this->_threshold = static_cast<int>(this->_vector.capacity() * this->_loadingFactor);
	Vector<MapNode<K, V>*> newVector(this->_vector.capacity() << 1); // move to the next power of 2

	for(unsigned int i = 0; i < this->_vector.capacity(); i++)
	{
		MapNode<K, V>* node = this->_vector[i];
		while(node != nullptr)
		{
			this->putInVector(newVector, node);
			node = node->getNext();
		}
	}

	this->_vector = newVector;
}

#endif //OSTEST_MAP_H
