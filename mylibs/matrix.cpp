#include "matrix.h"

// <constructor>
template <typename Type> matrix<Type> ::matrix(const ll _numberOfColumns, const ll _numberOfRows)
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

	columnVector = new Type[numberOfRows];
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = 0;
}

template <typename Type> matrix<Type> ::matrix(const matrix& _matrix)
{
	numberOfColumns = _matrix.numberOfColumns;
	numberOfRows = _matrix.numberOfRows;

	// Not making a function for this, sometimes copy-paste is fine
	data = (Type**) new Type * [numberOfColumns];
	for (size_t i = 0; i < numberOfColumns; i++)
		data[i] = (Type*) new Type[numberOfRows];

	// Copy values over
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] = _matrix.data[i][j];

	columnVector = new Type[numberOfRows];
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = _matrix.columnVector[i];
}

template <typename Type> matrix<Type> :: ~matrix()
{
	if (numberOfRows)
	{
		for (size_t i = 0; i < numberOfColumns; i++)
			delete[] data[i];
		delete[] columnVector;
	}
	if (numberOfColumns)
		delete[] data;
}
// </constructor>

// <operator overload>
template <typename Type> matrix<Type> matrix<Type> :: operator = (const matrix& other)
{
	if (numberOfRows)
	{
		for (size_t i = 0; i < numberOfColumns; i++)
			delete[] data[i];
		delete[] columnVector;
	}
	if (numberOfColumns)
		delete[] data;

	// Transfer data
	numberOfColumns = other.numberOfColumns;
	numberOfRows = other.numberOfRows;

	// Reallocate memory
	data = (Type**) new Type * [numberOfColumns];
	for (size_t i = 0; i < numberOfColumns; i++)
		data[i] = (Type*) new Type[numberOfRows];

	// Copy values over
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] = other.data[i][j];

	columnVector = new Type[numberOfRows];
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = other.columnVector[i];

	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator += (const matrix& right)
{
	for (size_t i = 0; i < std::min(numberOfColumns, right.numberOfColumns); i++)
		for (size_t j = 0; j < std::min(numberOfRows, right.numberOfRows); j++)
			data[i][j] += right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator -= (const matrix& right)
{
	for (size_t i = 0; i < std::min(numberOfColumns, right.numberOfColumns); i++)
		for (size_t j = 0; j < std::min(numberOfRows, right.numberOfRows); j++)
			data[i][j] -= right.data[i][j];
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator + (matrix& right) { *this += right; return *this; }

template <typename Type> matrix<Type> matrix<Type> :: operator - (matrix& right) { *this -= right; return *this; }

template <typename Type> Type*& matrix<Type> :: operator [] (const ll index) { return data[index]; }

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
template <typename Type> const ll matrix<Type> ::getRowSize() { return numberOfRows; }
template <typename Type> const ll matrix<Type> ::getColSize() { return numberOfColumns; }

template <typename Type> Type* matrix<Type> ::rowBegin(const ll index) { return data[index]; }
template <typename Type> Type* matrix<Type> ::rowEnd(const ll index) { return data[index] + numberOfColumns; }

template <typename Type> Type* matrix<Type> ::colBegin(const ll index)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		columnVector[i] = (Type&)data[i][index];	// I have no idea why this works
	return columnVector;
}

template <typename Type> Type* matrix<Type> ::colEnd(const ll index)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		columnVector[i] = (Type&)data[i][index];
	return columnVector + numberOfColumns;
}

template <typename Type> void matrix<Type> ::resize(const ll newColSize, const ll newRowSize)
{
	// Pass over numberOfColumns and numberOfRows
	numberOfColumns = newColSize;
	numberOfRows = newRowSize;
	return;
}
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
