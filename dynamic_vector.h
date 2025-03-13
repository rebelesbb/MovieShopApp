#pragma once

template<typename ElementType>
class VIterator;

template<typename ElementType>
class DynamicVector
{
	friend class VIterator<ElementType>;
public:
	DynamicVector() noexcept;
	DynamicVector(const DynamicVector<ElementType>& other) noexcept;
	void operator=(const DynamicVector<ElementType>& other);

	void push_back(const ElementType& element) noexcept;
	void set(int index, const ElementType& element) noexcept;
	int size() const;
	void clear();
	void erase(int index) noexcept;
	const ElementType& at(int index) const noexcept;
	void sort(bool(*gt)(const ElementType&, const ElementType&));

	VIterator<ElementType> begin();
	VIterator<ElementType> end();

	~DynamicVector<ElementType>();

protected:
	int length;
	int capacity;
	ElementType* elements;

};

template<typename ElementType>
DynamicVector<ElementType>::DynamicVector() noexcept : length{0}, capacity{10}, elements{new ElementType[capacity]} {}

template<typename ElementType>
DynamicVector<ElementType>::DynamicVector(const DynamicVector<ElementType>& other) noexcept : length{other.length}, capacity{other.capacity}, elements{new ElementType[capacity]}
{ 
	for (int index = 0; index < other.length; ++index)
		elements[index] = other.elements[index];
}

template<typename ElementType>
void DynamicVector<ElementType>::operator=(const DynamicVector<ElementType>& other)
{
	delete[] elements;
	length = other.length;
	capacity = other.capacity;
	elements = new ElementType[capacity];
	for (int index = 0; index < length; index++)
		elements[index] = other.elements[index];
}

template<typename ElementType>
DynamicVector<ElementType>::~DynamicVector<ElementType>()
{
	delete[] elements;
}

template<typename ElementType>
VIterator<ElementType> DynamicVector<ElementType>::begin()
{
	return VIterator<ElementType>(*this);
}

template<typename ElementType>
VIterator<ElementType> DynamicVector<ElementType>::end()
{
	return VIterator<ElementType>(*this, length);
}

template<typename ElementType> 
void DynamicVector<ElementType>::push_back(const ElementType& element) noexcept
{
	if (length == capacity)
	{
		capacity = 2 * capacity; 
		ElementType* resizedVector = new ElementType[capacity];

		for (int index = 0; index < length; ++index)
			resizedVector[index] = elements[index];

		delete[] elements;
		elements = resizedVector;
		elements[length++] = element;
	}
	else elements[length++] = element;
}

template<typename ElementType>
void DynamicVector<ElementType>::set(int index, const ElementType& element) noexcept
{
	elements[index] = element;
}

template<typename ElementType>
int DynamicVector<ElementType>::size() const
{
	return length;
}

template<typename ElementType>
inline void DynamicVector<ElementType>::clear()
{
	length = 0;
}

template<typename ElementType>
void DynamicVector<ElementType>::erase(int index) noexcept
{
	for (int i = index; i < length - 1; ++i)
		elements[i] = elements[i + 1];
	length--;
}

template<typename ElementType>	
const ElementType& DynamicVector<ElementType>::at(int index) const noexcept
{
	return elements[index];
}

template<typename ElementType>
void DynamicVector<ElementType>::sort(bool(*gt)(const ElementType&, const ElementType&))
{
	int i, j;
	for (i = 0; i < length - 1; i++)
		for (j = i + 1; j < length; j++)
			if (gt(elements[i], elements[j]))
			{
				auto aux = elements[i];
				elements[i] = elements[j];
				elements[j] = aux;
			}
}


template<typename ElementType>
class VIterator
{
private:
	int position;
	DynamicVector<ElementType> dVector;

public:
	VIterator(const DynamicVector<ElementType>& dV) : dVector{ dV }, position{ 0 } {
	}
	VIterator(const DynamicVector<ElementType>& dV, int pos) : dVector{ dV }, position{ pos } {

	}

	ElementType& operator*() {
		return dVector.elements[position];
	}
	VIterator& operator++()
	{
		position++;
		return *this;
	}
	bool operator==(const VIterator& other) noexcept
	{
		return this->position == other.position;
	}
	bool operator!=(const VIterator& other) noexcept
	{
		return this->position != other.position;
	}
};
