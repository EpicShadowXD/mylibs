#include "matrix.h"
#include <iostream>

// <constructor>
template <typename Type> matrix<Type> ::matrix() { numberOfColumns = numberOfRows = 0; data = NULL; }

template <typename Type> matrix<Type> ::matrix(ll _numberOfColumns, ll _numberOfRows)
{
	// Copy numberOfColumns and numberOfRows into this
	numberOfColumns = _numberOfColumns;
	numberOfRows = _numberOfRows;

	// Memory allocation for array
	data = (Type**) new Type * [numberOfColumns];
	for (size_t i = 0; i < numberOfColumns; i++)
		data[i] = (Type*) new Type[numberOfRows];

	// Fill array with 0
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] = 0;
}

template <typename Type> matrix<Type> ::matrix(const matrix& _array)
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

template <typename Type> std::ostream& operator << (std::ostream& out, const matrix<Type>& other)
{
	for (size_t i = 0; i < other.numberOfColumns; i++)
	{
		for (size_t j = 0; j < other.numberOfRows; j++)
			out << other.data[i][j] << ' ';
		out << std::endl;
	} return out;
}

template <typename Type> std::istream& operator >> (std::istream& in, matrix<Type>& right)
{
	for (size_t i = 0; i < right.numberOfColumns; i++)
		for (size_t j = 0; j < right.numberOfRows; j++)
			in >> right.data[i][j];
	return in;
}
// </operator overload>

// <methods>
template <typename Type> Type* matrix<Type> ::row_begin(const ll index) { return data[index]; }
template <typename Type> Type* matrix<Type> ::row_end(const ll index) { return data[index] + numberOfColumns - 1; }

template <typename Type> Type* matrix<Type> ::col_begin(const ll index) { return &data[0][index]; }
template <typename Type> Type* matrix<Type> ::col_end(const ll index) { return &data[numberOfRows - 1][index]; }

template <typename Type> ll matrix<Type> ::row_size(const ll index) { return numberOfColumns; }
template <typename Type> ll matrix<Type> ::col_size(const ll index) { return numberOfRows; }
// </methods>

// <iterator>
template <typename Type> matrix<Type> ::iterator::iterator(Type* ptr) { pointer = ptr; }

template <typename Type> Type& matrix<Type> ::iterator :: operator * () { return *pointer; }

template <typename Type> Type* matrix<Type> ::iterator :: operator = (const iterator& other) { return pointer = other.pointer; }

template <typename Type> Type& matrix<Type> ::iterator :: operator ++ () { pointer++; return *pointer; }
template <typename Type> Type& matrix<Type> ::iterator :: operator -- () { pointer--; return *pointer; }

template <typename Type> typename matrix<Type> ::iterator matrix<Type> ::iterator :: operator ++ (Type other) { iterator old = *this; operator++(); return old; }
template <typename Type> typename matrix<Type> ::iterator matrix<Type> ::iterator :: operator -- (Type other) { iterator old = *this; operator--(); return old; }

template <typename Type> Type& matrix<Type> ::iterator :: operator += (Type value) { return *pointer += value; }
template <typename Type> Type& matrix<Type> ::iterator :: operator -= (Type value) { return *pointer -= value; }

template <typename Type> bool matrix<Type> ::iterator :: operator == (const iterator& other) { return pointer == other.pointer; }
template <typename Type> bool matrix<Type> ::iterator :: operator != (const iterator& other) { return !(pointer == other.pointer); }
// </iterator>
