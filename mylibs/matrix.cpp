#include "matrix.h"

// <constructor>
template <typename Type> matrix<Type> ::matrix(const ll _numberOfColumns, const ll _numberOfRows)
{
	// Will deactivate ll macro later on so handled throw exception
	//if (_numberOfColumns < 0 || _numberOfRows < 0)
		//throw std::invalid_argument("Matrices can't have negative size.");

	// Copy numberOfColumns and numberOfRows into this
	numberOfColumns = _numberOfColumns;
	numberOfRows = _numberOfRows;

	if (_numberOfColumns == 0 && numberOfRows == 0)
	{
		this->data = nullptr;
		this->columnVector = nullptr;

		return;
	}

	allocate(*this, numberOfColumns, numberOfRows);
	fill(*this, 0);
}

template <typename Type> matrix<Type> ::matrix(const matrix& other)
{
	numberOfColumns = other.numberOfColumns;
	numberOfRows = other.numberOfRows;

	data = allocateMatrix(other.numberOfColumns, other.numberOfRows);
	columnVector = allocateColumnVector(other.numberOfRows);

	if (other.data)
		for (size_t i = 0; i < other.numberOfColumns; i++)
			for (size_t j = 0; j < other.numberOfRows; j++)
				data[i][j] = other.data[i][j];

	if (other.columnVector)
		for (size_t i = 0; i < other.numberOfRows; i++)
			columnVector[i] = other.columnVector[i];
}

template <typename Type> matrix<Type> :: ~matrix()
{
	deallocateMatrix(*this, this->numberOfColumns, this->numberOfRows);
	delete[] this->columnVector;
}
// </constructor>

// <operator overload>
template <typename Type> matrix<Type> matrix<Type> :: operator = (const matrix& other)
{
	deallocateMatrix(*this, numberOfColumns, numberOfRows);
	delete[] this->columnVector;

	this->data = allocateMatrix(numberOfColumns, numberOfRows);
	this->columnVector = allocateColumnVector(numberOfRows);

	// Could make this smarter so it goes thru the whole array only once instead of
	// parsing it once for row col and another time for minRow and minCol but this
	// is way easier to read.
	fill(*this, 0);

	if (other.data)
		for (size_t i = 0; i < std::min(numberOfColumns, other.numberOfColumns); i++)
			for (size_t j = 0; j < std::min(numberOfRows, other.numberOfRows); j++)
				data[i][j] = other.data[i][j];

	if (other.columnVector)
		for (size_t i = 0; i < std::min(numberOfRows, other.numberOfRows); i++)
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
		out << '\n';
	} return out;
}

template <typename Type> std::istream& operator >> (std::istream& in, matrix<Type>& other)
{
	for (size_t i = 0; i < other.numberOfColumns; i++)
		for (size_t j = 0; j < other.numberOfRows; j++)
			in >> other.data[i][j];
	return in;
}
// </operator overload>

// <methods>
template <typename Type> Type** matrix<Type> ::allocateMatrix(ll _numberOfColumns, ll _numberOfRows)
{
	//int** p = nullptr;

	if (_numberOfColumns || _numberOfRows)
	{
		data = new Type * [numberOfColumns];

		for (size_t i = 0; i < numberOfColumns; i++) data[i] = new Type[numberOfRows];

		return data;
	}

	return (Type**)nullptr;
}

template <typename Type> Type** matrix<Type> ::allocateColumnVector(ll _numberOfRows)
{
	//int** p = nullptr;

	if (_numberOfRows)
	{
		columnVector = new Type * [_numberOfRows];

		return columnVector;
	}

	return (Type**)nullptr;
}


// Deprecated, no longer using it, have better alternative as allocateMatrix and allocateColumnVector
template <typename Type> void matrix<Type> ::allocate(matrix<Type>& other, ll numberOfColumns, ll numberOfRows)
{
	if (other.numberOfColumns == 0 && other.numberOfRows == 0)
	{
		other.data = nullptr;
		other.columnVector = nullptr;
	}
	else
	{
		other.data = (Type**) new Type * [numberOfColumns];
		for (size_t i = 0; i < numberOfColumns; i++)
			other.data[i] = (Type*) new Type[numberOfRows];

		other.columnVector = new Type * [numberOfRows];
	}
}

template <typename Type> void matrix<Type> ::deallocateMatrix(matrix<Type>& other, ll _numberOfColumns, ll _numberOfRows)
{
	if (_numberOfColumns || other.data)
		for (size_t i = 0; i < numberOfColumns; i++)
			delete[] other.data[i];

	delete[] other.data;
}

// Deprecated
template <typename Type> void matrix<Type> ::deallocate(matrix<Type>& other, ll numberOfColumns, ll numberOfRows)
{
	if (numberOfColumns || other.data)
		for (size_t i = 0; i < numberOfColumns; i++)
			delete[] other.data[i];

	delete[] other.data;
	delete[] other.columnVector;
}

template <typename Type> void matrix<Type> ::fill(matrix<Type>& other, Type value)
{
	// Fill array with value
	for (size_t i = 0; i < other.numberOfColumns; i++)
		for (size_t j = 0; j < other.numberOfRows; j++)
			other.data[i][j] = value;

	other.columnVector = nullptr;
}

// Currently working on this
template <typename Type> void matrix<Type> ::resize(const ll _numberOfColumns, const ll _numberOfRows)
{
	matrix<Type> temp(*this);

	deallocate(*this, numberOfColumns, numberOfRows);

	this->data = allocateMatrix(_numberOfColumns, _numberOfRows);
	this->columnVector = allocateColumnVector(_numberOfRows);

	numberOfColumns = _numberOfColumns;
	numberOfRows = _numberOfRows;

	*this = temp;
}

template <typename Type> const ll matrix<Type> ::getRowSize() { return numberOfColumns; }		// row length = how many columns there are
template <typename Type> const ll matrix<Type> ::getColSize() { return numberOfRows; }			// and viceversa

template <typename Type> const Type* matrix<Type> ::matrixBegin() { return data[0]; }
template <typename Type> const Type* matrix<Type> ::matrixEnd() { return data[numberOfRows] + numberOfColumns; }

template <typename Type> Type* matrix<Type> ::rowBegin(const ll index) { return data[index]; }
template <typename Type> Type* matrix<Type> ::rowEnd(const ll index) { return data[index] + numberOfColumns; }

// Trying to work out how to iterate thru a 2d array (of pointers, Type**) with a 1d pointer (Type*)
template <typename Type> Type** matrix<Type> ::colBegin(const ll index)
{
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = &data[i][index];
	return columnVector;
}

template <typename Type> Type** matrix<Type> ::colEnd(const ll index)
{
	for (size_t i = 0; i < numberOfRows; i++)
		columnVector[i] = &data[i][index];
	return (columnVector + numberOfRows);
}
// </methods>

// <iterator>
template <typename Type> matrix<Type> ::iterator::iterator(Type* ptr) { pointer = ptr; }

template <typename Type> Type& matrix<Type> ::iterator :: operator * () { return *pointer; }

template <typename Type> Type* matrix<Type> ::iterator :: operator = (const iterator& other) { return pointer = other.pointer; }
template <typename Type> Type* matrix<Type> ::iterator :: operator = (Type** other) { return pointer = other[0]; }

template <typename Type> Type& matrix<Type> ::iterator :: operator ++ () { pointer++; return *pointer; }
template <typename Type> Type& matrix<Type> ::iterator :: operator -- () { pointer--; return *pointer; }

template <typename Type> typename matrix<Type> ::iterator matrix<Type> ::iterator :: operator ++ (Type other) { iterator old = *this; operator++(); return old; }
template <typename Type> typename matrix<Type> ::iterator matrix<Type> ::iterator :: operator -- (Type other) { iterator old = *this; operator--(); return old; }

template <typename Type> Type& matrix<Type> ::iterator :: operator += (Type value) { return *pointer += value; }
template <typename Type> Type& matrix<Type> ::iterator :: operator -= (Type value) { return *pointer -= value; }

template <typename Type> Type& matrix<Type> ::iterator :: operator + (Type value) { return this += value; }
template <typename Type> Type& matrix<Type> ::iterator :: operator - (Type value) { return this -= value; }

template <typename Type> bool matrix<Type> ::iterator :: operator == (const iterator& other) { return pointer == other.pointer; }
template <typename Type> bool matrix<Type> ::iterator :: operator != (const iterator& other) { return !(pointer == other.pointer); }
// </iterator>
