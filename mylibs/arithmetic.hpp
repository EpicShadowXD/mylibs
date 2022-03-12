#pragma once
#include "matrix.h"

template <typename Type>
matrix<Type> matrix<Type> :: operator += (const matrix& right)
{
	for (size_t i = 0; i < std::min(rowSize, right.rowSize); i++)
		for (size_t j = 0; j < std::min(colSize, right.colSize); j++)
			data[i][j] += right.data[i][j];
	return *this;
}

template <typename Type>
matrix<Type> matrix<Type> :: operator -= (const matrix& right)
{
	for (size_t i = 0; i < std::min(rowSize, right.rowSize); i++)
		for (size_t j = 0; j < std::min(colSize, right.colSize); j++)
			data[i][j] -= right.data[i][j];
	return *this;
}

template <typename Type>
matrix<Type> matrix<Type> :: operator + (matrix& right) { *this += right; return *this; }

template <typename Type>
matrix<Type> matrix<Type> :: operator - (matrix& right) { *this -= right; return *this; }

// Scalars
template <typename Type>
matrix<Type> matrix<Type> :: operator += (const Type scalar)
{
	for (size_t i = 0; i < rowSize; i++)
		for (size_t j = 0; j < colSize; j++)
			data[i][j] += scalar;
	return *this;
}

template <typename Type>
matrix<Type> matrix<Type> :: operator -= (const Type scalar)
{
	for (size_t i = 0; i < rowSize; i++)
		for (size_t j = 0; j < colSize; j++)
			data[i][j] -= scalar;
	return *this;
}

template <typename Type>
matrix<Type> matrix<Type> :: operator *= (const Type scalar)
{
	for (size_t i = 0; i < rowSize; i++)
		for (size_t j = 0; j < colSize; j++)
			data[i][j] *= scalar;
	return *this;
}

template <typename Type>
matrix<Type> matrix<Type> :: operator /= (const Type scalar)
{
	for (size_t i = 0; i < rowSize; i++)
		for (size_t j = 0; j < colSize; j++)
			data[i][j] /= scalar;
	return *this;
}

template <typename Type>
matrix<Type> matrix<Type> :: operator + (const Type scalar) { return *this += scalar; }

template <typename Type>
matrix<Type> matrix<Type> :: operator - (const Type scalar) { return *this -= scalar; }

template <typename Type>
matrix<Type> matrix<Type> :: operator * (const Type scalar) { return *this *= scalar; }

template <typename Type>
matrix<Type> matrix<Type> :: operator / (const Type scalar) { return *this /= scalar; }
