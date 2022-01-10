#include "matrix.h"

// <constructor>
template <typename Type> matrix<Type> ::matrix(const ll _numberOfColumns, const ll _numberOfRows)
{
	// Copy numberOfColumns and numberOfRows into this
	numberOfColumns = _numberOfColumns;
	numberOfRows = _numberOfRows;

	allocate(*this, numberOfColumns, numberOfRows);
	fill(*this, 0);

	columnVector = new Type[numberOfRows];
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = 0;
}

template <typename Type> matrix<Type> ::matrix(const matrix& other)
{
	numberOfColumns = other.numberOfColumns;
	numberOfRows = other.numberOfRows;

	allocate(*this, numberOfColumns, numberOfRows);

	// Can't use copy method for this for some odd reason
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] = other.data[i][j];

	columnVector = new Type[numberOfRows];
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = other.columnVector[i];
}

template <typename Type> matrix<Type> :: ~matrix() { deallocate(*this, this->numberOfColumns, this->numberOfRows); }
// </constructor>

// <operator overload>
template <typename Type> matrix<Type> matrix<Type> :: operator = (const matrix& other)
{
	deallocate(*this, this->numberOfColumns, this->numberOfRows);
	allocate(*this, numberOfColumns, numberOfRows);
	copy(*this, other, numberOfColumns, numberOfRows);

	columnVector = new Type[numberOfRows];
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = other.columnVector[i];

	return *this;
}

// Matrices
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

// Scalars
template <typename Type> matrix<Type> matrix<Type> :: operator += (const Type scalar)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] += scalar;
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator -= (const Type scalar)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] -= scalar;
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator *= (const Type scalar)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] *= scalar;
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator /= (const Type scalar)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			data[i][j] /= scalar;
	return *this;
}

template <typename Type> matrix<Type> matrix<Type> :: operator + (const Type scalar) { return *this += scalar; }

template <typename Type> matrix<Type> matrix<Type> :: operator - (const Type scalar) { return *this -= scalar; }

template <typename Type> matrix<Type> matrix<Type> :: operator * (const Type scalar) { return *this *= scalar; }

template <typename Type> matrix<Type> matrix<Type> :: operator / (const Type scalar) { return *this /= scalar; }

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
template <typename Type> void matrix<Type> ::allocate(matrix<Type>& other, ll numberOfColumns, ll numberOfRows)
{
	other.data = (Type**) new Type * [numberOfColumns];
	for (size_t i = 0; i < numberOfColumns; i++)
		other.data[i] = (Type*) new Type[numberOfRows];
}

template <typename Type> void matrix<Type> ::deallocate(matrix<Type>& other, ll numberOfColumns, ll numberOfRows)
{
	if (numberOfRows)
	{
		for (size_t i = 0; i < numberOfColumns; i++)
			delete[] other.data[i];
		delete[] other.columnVector;
	}
	if (numberOfColumns)
		delete[] other.data;
}

// Does not work when right is a reference and can't make
// right a reference, have no idea why
template <typename Type> void matrix<Type> ::copy(matrix<Type>& left, const matrix<Type> right, ll numberOfColumns, ll numberOfRows)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		for (size_t j = 0; j < numberOfRows; j++)
			left.data[i][j] = right.data[i][j];
}

template <typename Type> void matrix<Type> ::fill(matrix<Type>& other, Type value)
{
	// Fill array with value
	for (size_t i = 0; i < other.numberOfColumns; i++)
		for (size_t j = 0; j < other.numberOfRows; j++)
			other.data[i][j] = value;
}


template <typename Type> void matrix<Type> ::resize(const ll newNumberOfColumns, const ll newNumberOfRows)
{
	matrix<Type> myCopy(newNumberOfColumns, newNumberOfRows);

	for (size_t i = 0; i < newNumberOfColumns; i++)
		for (size_t j = 0; j < newNumberOfRows; j++)
			myCopy.data[i][j] = data[i][j];

	deallocate(*this, this->numberOfColumns, this->numberOfRows);
	allocate(*this, newNumberOfColumns, newNumberOfRows);

	*this = myCopy;
	numberOfColumns = newNumberOfColumns;
	numberOfRows = newNumberOfRows;
}

template <typename Type> const ll matrix<Type> ::getRowSize() { return numberOfRows; }		// row length = how many columns there are
template <typename Type> const ll matrix<Type> ::getColSize() { return numberOfColumns; }	// and viceversa

template <typename Type> Type* matrix<Type> ::rowBegin(const ll index) { return data[index]; }
template <typename Type> Type* matrix<Type> ::rowEnd(const ll index) { return data[index] + numberOfColumns; }

template <typename Type> Type* matrix<Type> ::colBegin(const ll index)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		columnVector[i] = (Type&)data[i][index];	// I have no idea why this works | Edit: does nothing
	return columnVector;
}

template <typename Type> Type* matrix<Type> ::colEnd(const ll index)
{
	for (size_t i = 0; i < numberOfColumns; i++)
		columnVector[i] = (Type&)data[i][index];
	return columnVector + numberOfColumns;
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
