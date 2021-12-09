#pragma once
#include <iostream>

using ll = unsigned long long;	// Hotfix for potential loss of data warning

/*
class refWrapper	// Either create refference_wrapper or use std::refference_wrapper
{

};
*/

template <typename Type> class iterator
{
protected:
	ll stride = NULL;
	Type* pointer;

public:
	iterator() : pointer(nullptr) {}
	iterator(Type* ptr) { pointer = ptr; }

	// Dereference operator
	Type& operator * () { return *pointer; }

	// Prefix
	Type& operator -- () { pointer--; return *pointer; }
	Type& operator ++ () { pointer++; return *pointer; }

	// Postfix
	iterator operator -- (Type value) { iterator old = *this; operator--(); return old; }
	iterator operator ++ (Type value) { iterator old = *this; operator++(); return old; }

	// Increment/ decrement by value
	Type& operator += (Type value) { return *pointer += value; }
	Type& operator -= (Type value) { return *pointer -= value; }

	// Compare - to fix
	inline bool operator == (const iterator& right) { return pointer == right.pointer; }
	inline bool operator != (const iterator& right) { return pointer == right.pointer; }

	iterator operator = (const iterator& right) { return pointer = right.pointer; }

	friend std::ostream& operator << (std::ostream& out, const iterator& right) { out << right.pointer; return out; }
};

// TO-DO: create size method/ subclass to differentiate between "user used" size and "memory allocated" size
template <typename Type> class matrix : public iterator<Type>
{
protected:
	ll numberOfColumns, numberOfRows;
	Type** data;

public:
	// Constructors and destructors
	matrix() { numberOfColumns = numberOfRows = 0; data = NULL; }		// Wanted to declare outside but doesn'Type want to work for some odd reason
	matrix(ll _numberOfColumns, ll _numberOfRows);
	matrix(const matrix& _array);					// Copy constructor
	~matrix();

	// Attribution
	matrix operator = (const matrix& right);

	// Hides data subcategory and can access data directly through instance
	Type*& operator [] (ll value);

	// Arithmetic
	// Note: does operations relative to the implied matrix's dimensions,
	//		meaning that the elements from a bigger matrix outside the scope
	//		of the implied matrix do not get touched. (potential logic error)
	matrix operator += (const matrix& right);
	matrix operator -= (const matrix& right);
	matrix operator *= (const matrix& right);
	matrix operator + (const matrix& right);
	matrix operator - (const matrix& right);
	matrix operator * (const matrix& right);

	// I want to get declaration outside the class but this fucking shit ass
	// fucking programming language won'Type fucking let me. I am so fucking mad.
	friend std::ostream& operator << (std::ostream& out, const matrix& right)
	{
		for (size_t i = 0; i < right.numberOfColumns; i++)
		{
			for (size_t j = 0; j < right.numberOfRows; j++)
				out << right.data[i][j] << ' ';
			out << std::endl;
		} return out;
	}

	friend std::istream& operator >> (std::istream& in, const matrix& right)
	{
		for (size_t i = 0; i < right.numberOfColumns; i++)
			for (size_t j = 0; j < right.numberOfRows; j++)
				in >> right.data[i][j];
		return in;
	}

	// TO-DO!
	// Memory management
	void resize(const ll numberOfColumns, const ll numberOfRows);	// Keeps memory, just destroys elements
	void shrink_to_fit();									// Frees up unused memory
	void erase(const ll colIndex, const ll rowIndex);
	void erase(const ll firstColIndex, const ll firstRowIndex,
		const ll secondColIndex, const ll secondRowIndex);
	void insert(const ll colIndex, const ll rowIndex);	// Requires automatic reallocation of memory; also don'Type forget to implement bounds check
	void at(const ll colIndex, const ll rowIndex);	// Again, don'Type forget to implement bounds check
	void reserve(ll n);
	void swap(matrix& right);
	void append(matrix& right);	// Concatenate two matrixes

	// Iterators | Too lazy to implement exception handling rn so Ill just return nullptr
	Type* row_begin(const ll index) { return data[index]; }
	Type* row_end(const ll index) { return data[index] + numberOfColumns - 1; }

	Type* col_begin(const ll index) { return &data[0][index]; }
	Type* col_end(const ll index) { return &data[numberOfRows - 1][index]; }

	// Size
	ll row_size(const ll index) { return numberOfColumns; }
	ll col_size(const ll index) { return numberOfRows; }
};

// <constructor>
template <typename Type> matrix<Type> :: matrix(ll _numberOfColumns, ll _numberOfRows)
{
	// Copy numberOfColumns and numberOfRows into this
	numberOfColumns = _numberOfColumns;
	numberOfRows = _numberOfRows;

	// Memory allocation for array
	data = (Type**) new Type* [numberOfColumns];
	for (size_t i = 0; i < numberOfColumns; i++)
		data[i] = (Type*) new Type[numberOfRows];

	// Fill array with 0
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] = 0;
}

template <typename Type> matrix<Type> :: matrix(const matrix& _array)
{
	numberOfColumns = _array.numberOfColumns;
	numberOfRows = _array.numberOfRows;

	// Not making a function for this, sometimes copy-paste is fine
	data = (Type**) new Type * [numberOfColumns];
	for (size_t i = 0; i < numberOfColumns; i++)
		data[i] = (Type*) new Type[numberOfRows];

	// Copy values over
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] = _array.data[i][j];
}

template <typename Type> matrix<Type> :: ~matrix()
{
	if (numberOfRows)
		for (size_t i = 0; i < numberOfColumns; i++)
			delete[] data[i];
	if (numberOfColumns)
		delete[] data;
}
// </constructor>

// <operator overload>
template <typename Type> matrix<Type> matrix<Type> :: operator = (const matrix& right)
{
	// Free memory through destructor
	if (numberOfRows)
		for (size_t i = 0; i < numberOfColumns; i++)
			delete[] data[i];
	if (numberOfColumns)
		delete[] data;

	// Transfer data
	numberOfColumns = right.numberOfColumns;
	numberOfRows = right.numberOfRows;

	// Reallocate memory
	data = (Type**) new Type * [numberOfColumns];
	for (size_t i = 0; i < numberOfColumns; i++)
		data[i] = (Type*) new Type[numberOfRows];

	// Copy values over
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] = right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator += (const matrix& right)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] += right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator -= (const matrix& right)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] -= right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator *= (const matrix& right)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] *= right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator + (const matrix& right)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] += right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator - (const matrix& right)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] -= right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator * (const matrix& right)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] *= right.data[i][j];
	return *this;
}

template <typename Type> Type*& matrix<Type> :: operator [] (ll const index) { return data[index]; }
// </operator overload>