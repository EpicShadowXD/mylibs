#pragma once
#include <iostream>

template <typename T> class matrix
{
public:
	int col, row;
	T** data;

public:
	matrix() { col = row = 0; data = NULL; }	// Wanted to declare outside but doesn't want to work for some odd reason
	matrix(int column, int row);
	matrix(const matrix& _array);					// Copy constructor
	~matrix();

	matrix operator = (const matrix& right);
	matrix operator += (const matrix& right);
	matrix operator -= (const matrix& right);
	matrix operator *= (const matrix& right);
	matrix operator + (const matrix& right);
	matrix operator - (const matrix& right);
	matrix operator * (const matrix& right);
	T*& operator [] (int value);
};

// Beginning of declaration of constructors
template <typename T> matrix<T> :: matrix(int _col, int _row)
{
	// Encapsulation of col and row
	col = _col;
	row = _row;

	// Memory allocation for array
	data = (T**) new T*[col];
	for (size_t i = 0; i < col; i++)
		data[i] = (T*) new T[row];

	// Fill array with 0
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] = 0;
}

template <typename T> matrix<T> ::matrix(const matrix& _array)
{
	col = _array.col;
	row = _array.row;

	// Not making a function for this, sometimes copy-paste is fine
	data = (T**) new T * [col];
	for (size_t i = 0; i < col; i++)
		data[i] = (T*) new T[row];

	// Copy values over
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] = _array.data[i][j];
}

template <typename T> matrix<T> :: ~matrix()
{
	if (row)
		for (size_t i = 0; i < col; i++)
			delete[] data[i];
	if (col)
		delete[] data;
}
// End of declaration of constructors

// Beginning of declaration of operator overloading
template <typename T> matrix<T> matrix<T> :: operator = (const matrix& right)
{
	// Free memory
	if (row)
		for (size_t i = 0; i < col; i++)
			delete[] data[i];
	if (col)
		delete[] data;

	// Transfer data
	col = right.col;
	row = right.row;

	// Reallocate memory
	data = (T**) new T * [col];
	for (size_t i = 0; i < col; i++)
		data[i] = (T*) new T[row];

	// Copy values over
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] = right.data[i][j];
	return *this;
}

template <typename T> matrix<T> matrix<T> :: operator += (const matrix& right)
{
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] += right.data[i][j];
	return *this;
}

template <typename T> matrix<T> matrix<T> :: operator -= (const matrix& right)
{
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] -= right.data[i][j];
	return *this;
}

template <typename T> matrix<T> matrix<T> :: operator *= (const matrix& right)
{
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] *= right.data[i][j];
	return *this;
}

template <typename T> matrix<T> matrix<T> :: operator + (const matrix& right)
{
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] += right.data[i][j];
	return *this;
}

template <typename T> matrix<T> matrix<T> :: operator - (const matrix& right)
{
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] -= right.data[i][j];
	return *this;
}

template <typename T> matrix<T> matrix<T> :: operator * (const matrix& right)
{
	for (size_t i = 0; i < col; i++)
		for (size_t j = 0; j < row; j++)
			data[i][j] *= right.data[i][j];
	return *this;
}

template <typename T> T*& matrix<T> :: operator [] (unsigned index)
{
    return data[index];
}
// End of declaration of operator overloading
