#pragma once
#include <iostream>
#include <stdexcept>

// TODO: create size method/ subclass to differentiate 
// between "user used" size and "memory allocated" size
template <typename Type> class matrix
{
private:
	size_t rowSize, colSize;
	Type** data;

public:
	using colIterator = Type*;

	matrix() :	rowSize(NULL), colSize(NULL), data(nullptr) {}
	matrix(const size_t, const size_t);
	matrix(const size_t, const size_t, Type);
	matrix(const matrix& other);
	
	~matrix();

	// Copy operator
	matrix operator = (const matrix&);

	// Hides data subcategory and can access data directly through instance
	Type*& operator [] (const size_t value);

	// Arithmetic
	matrix operator += (const matrix&);
	matrix operator -= (const matrix&);

	matrix operator + (matrix&);
	matrix operator - (matrix&);

	matrix operator + (const Type);
	matrix operator - (const Type);
	matrix operator * (const Type);
	matrix operator / (const Type);

	matrix operator += (const Type);
	matrix operator -= (const Type);
	matrix operator *= (const Type);
	matrix operator /= (const Type);

	// TODO
	// Algebra
	double determinant();

	// Iostream operator overload
	template <typename Type> friend std::ostream& operator << (std::ostream&, const matrix<Type>&);
	template <typename Type> friend std::istream& operator >> (std::istream&, matrix<Type>&);

	// TODO
	// Fstream operator overload

	// TODO
	// Memory management
	void resize(const size_t rowSize, const size_t colSize);	// Keeps memory, just destroys elements
	void resize(const size_t rowSize, const size_t colSize, const Type value);	// Initialize potential new empty spaces with value
	void shrink_to_fit();											// Frees up unused memory defined as all 0s on a row or column
	void erase(const size_t colIndex, const size_t rowIndex);
	void erase(const size_t firstColIndex, const size_t firstRowIndex,
		const size_t secondColIndex, const size_t secondRowIndex);
	void insert(const size_t colIndex, const size_t rowIndex);				// Requires automatic reallocation of memory; also don'Type forget to implement bounds check
	void at(const size_t colIndex, const size_t rowIndex);					// Again, don't forget to implement bounds check
	void reserve(const size_t);
	void swap(matrix& right);
	void fill(Type);

	// Methods for iterators
	const size_t getRowSize();
	const size_t getColSize();

	const Type* matrixBegin();
	const Type* matrixEnd();

	Type* rowBegin(const size_t);
	Type* rowEnd(const size_t);

	matrix::colIterator colBegin(const size_t);
	matrix::colIterator colEnd(const size_t);

private:
	// Currently used
	Type** allocateMatrix(const size_t, const size_t);
	Type** allocateColumnVector(const size_t);

	void deallocateMatrix(matrix&, size_t, size_t);

	// Distinction between public fill and private fill for distinct
	// purpose outside class and ease of use for code inside the class.
	void fill(matrix&, const Type);

	// Consider it deprecated, might remove it later.
	void allocate(matrix&, size_t, size_t);
	void deallocate(matrix&, size_t, size_t);
};
