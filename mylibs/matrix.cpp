#pragma once

// Here are the dependencies
#include "matrix.h"
#include "arithmetic.hpp"
//#include "iterator.hpp"
#include "functional.hpp"
#include "algebra.hpp"

// Here is the root:
// constructors/ destructors
// opereator overload for parsing data
// iostream support for debugging

// <constructor + destructor>
template <typename Type>
matrix<Type> ::matrix(const size_t _numberOfColumns, const size_t _numberOfRows)
{
	// Will deactivate size_t macro later on so handled throw exception
	//if (_numberOfColumns < 0 || _numberOfRows < 0)
		//throw std::invalid_argument("Matrices can't have negative size.");

	// Copy rowSize and colSize into this
	rowSize = _numberOfColumns;
	colSize = _numberOfRows;

	if (_numberOfColumns == 0 && colSize == 0)
	{
		this->data = nullptr;
		return;
	}

	allocate(*this, rowSize, colSize);
	fill(*this, 0);
}

template <typename Type>
matrix<Type> ::matrix(const size_t _numberOfColumns, const size_t _numberOfRows, const Type value)
{
	rowSize = _numberOfColumns;
	colSize = _numberOfRows;

	if (_numberOfColumns == 0 && colSize == 0)
	{
		this->data = nullptr;
		this->columnVector = nullptr;

		return;
	}

	allocate(*this, rowSize, colSize);
	fill(*this, value);
}

template <typename Type>
matrix<Type> ::matrix(const matrix& other)
{
	rowSize = other.rowSize;
	colSize = other.colSize;

	data = allocateMatrix(other.rowSize, other.colSize);

	if (other.data)
		for (size_t i = 0; i < other.rowSize; i++)
			for (size_t j = 0; j < other.colSize; j++)
				data[i][j] = other.data[i][j];
}

template <typename Type>
matrix<Type> :: ~matrix()
{
	deallocateMatrix(*this, this->rowSize, this->colSize);
}
// </constructor + destructor>

// <copy operator>
template <typename Type>
matrix<Type> matrix<Type> :: operator = (const matrix& other)
{
	deallocateMatrix(*this, rowSize, colSize);

	this->data = allocateMatrix(rowSize, colSize);

	// Could make this smarter so it goes thru the whole array only once instead of
	// parsing it once for row col and another time for minRow and minCol but this
	// is way easier to read.
	fill(*this, 0);

	if (other.data)
		for (size_t i = 0; i < std::min(rowSize, other.rowSize); i++)
			for (size_t j = 0; j < std::min(colSize, other.colSize); j++)
				data[i][j] = other.data[i][j];

	return *this;
}
// </copy operator>

// Dereference brackets
template <typename Type> 
Type*& matrix<Type> :: operator [] (const size_t index) { return data[index]; }

// Iostream support for easy debugging
template <typename Type>
std::ostream& operator << (std::ostream& out, const matrix<Type>& other)
{
	for (size_t i = 0; i < other.rowSize; i++)
	{
		for (size_t j = 0; j < other.colSize; j++)
			out << other.data[i][j] << ' ';
		out << '\n';
	} return out;
}

template <typename Type>
std::istream& operator >> (std::istream& in, matrix<Type>& other)
{
	for (size_t i = 0; i < other.rowSize; i++)
		for (size_t j = 0; j < other.colSize; j++)
			in >> other.data[i][j];
	return in;
}
