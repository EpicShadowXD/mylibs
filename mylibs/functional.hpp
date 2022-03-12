#pragma once
#include "matrix.h"

template <typename Type>
Type** matrix<Type> ::allocateMatrix(const size_t _numberOfColumns, const size_t _numberOfRows)
{
	if (_numberOfColumns || _numberOfRows)
	{
		data = new Type * [rowSize];

		for (size_t i = 0; i < rowSize; i++) data[i] = new Type[colSize];

		return data;
	}

	return (Type**)nullptr;
}

// Deprecated, no longer using it, have better alternative as allocateMatrix and allocateColumnVector
template <typename Type>
void matrix<Type> ::allocate(matrix<Type>& other, const size_t rowSize, const size_t colSize)
{
	if (other.rowSize == 0 && other.colSize == 0) other.data = nullptr;
	else
	{
		other.data = (Type**) new Type * [rowSize];
		for (size_t i = 0; i < rowSize; i++)
			other.data[i] = (Type*) new Type[colSize];
	}
}

template <typename Type>
void matrix<Type> ::deallocateMatrix(matrix<Type>& other, size_t _numberOfColumns, size_t _numberOfRows)
{
	if (_numberOfColumns || other.data)
		for (size_t i = 0; i < rowSize; i++)
			delete[] other.data[i];

	delete[] other.data;
}

// Deprecated
template <typename Type>
void matrix<Type> ::deallocate(matrix<Type>& other, size_t rowSize, size_t colSize)
{
	if (rowSize || other.data)
		for (size_t i = 0; i < rowSize; i++)
			delete[] other.data[i];

	delete[] other.data;
}

// Private method, intended for internal use 
template <typename Type>
void matrix<Type> ::fill(matrix<Type>& other, Type value)
{
	// Fill array with value
	for (size_t i = 0; i < other.rowSize; i++)
		for (size_t j = 0; j < other.colSize; j++)
			other.data[i][j] = value;
}

// Public method, intended for external use
template <typename Type>
void matrix<Type> ::fill(Type value)
{
	for (size_t i = 0; i < rowSize; i++)
		for (size_t j = 0; j < colSize; j++)
			data[i][j] = value;
}

// Currently working on this
template <typename Type>
void matrix<Type> ::resize(const size_t _numberOfColumns, const size_t _numberOfRows)
{
	matrix<Type> temp(*this);

	deallocateMatrix(*this, this->rowSize, this->colSize);

	this->data = allocateMatrix(_numberOfColumns, _numberOfRows);

	rowSize = _numberOfColumns;
	colSize = _numberOfRows;

	fill(*this, 0);

	*this = temp;
}

template <typename Type>
const size_t matrix<Type> ::getRowSize() { return rowSize; }
template <typename Type>
const size_t matrix<Type> ::getColSize() { return colSize; }
