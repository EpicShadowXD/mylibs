#pragma once
#include <iostream>
#include <stdexcept>

// Will never use negative numbers for matrix size
using ll = unsigned long long;

// TODO: create size method/ subclass to differentiate 
// between "user used" size and "memory allocated" size
template <typename Type> class matrix
{
// Iterator
public:
	class iterator
	{
	protected:
		Type* pointer;

	public:
		iterator() : pointer(nullptr) {}
		iterator(Type* ptr);

		Type& operator * ();
		//Type&& operator * ();

		Type* operator = (const iterator&);
		Type* operator = (Type**);

		// Prefix
		Type& operator + (Type);
		Type& operator - (Type);

		Type& operator ++ ();
		Type& operator -- ();

		// Postfix
		iterator operator ++ (Type);
		iterator operator -- (Type);

		Type& operator += (const Type);
		Type& operator -= (const Type);

		bool operator == (const iterator&);
		bool operator != (const iterator&);
	};

// Matrix
private:
	ll numberOfColumns, numberOfRows;
	Type** data;

public:
	Type** columnVector;

public:

	matrix() :	numberOfColumns(NULL), numberOfRows(NULL), data(nullptr), columnVector(nullptr) {}
	matrix(const ll, const ll);
	matrix(const matrix& other);
	//matrix(const matrix& other) :	numberOfColumns { other.numberOfColumns },
									//numberOfRows { other.numberOfRows }
									//{ allocate(*this, numberOfColumns, numberOfRows);
									//copy(*this, other, numberOfColumns, numberOfRows); } // Copy constructor
	
	~matrix();

	// Copy operator
	matrix operator = (const matrix&);

	// Hides data subcategory and can access data directly through instance
	Type*& operator [] (const ll value);

	// Arithmetic
	// Note: does operations relative to the implied matrix's dimensions, meaning
	//		that the elements from a bigger matrix outside the scope of the implied
	//		matrix do not get touched (potential silent runtime error) (perfectly 
	//		fine for linear albegra though).
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

	template <typename Type> friend std::ostream& operator << (std::ostream&, const matrix<Type>&);
	template <typename Type> friend std::istream& operator >> (std::istream&, matrix<Type>&);

	// TODO
	// Memory management
	void fill(matrix&, const Type);
	void resize(const ll numberOfColumns, const ll numberOfRows);	// Keeps memory, just destroys elements
	void resize(const ll numberOfColumns, const ll numberOfRows, const Type value);	// Initialize potential new empty spaces with value
	void shrink_to_fit();											// Frees up unused memory defined as all 0s on a row or column
	void erase(const ll colIndex, const ll rowIndex);
	void erase(const ll firstColIndex, const ll firstRowIndex,
		const ll secondColIndex, const ll secondRowIndex);
	void insert(const ll colIndex, const ll rowIndex);				// Requires automatic reallocation of memory; also don'Type forget to implement bounds check
	void at(const ll colIndex, const ll rowIndex);					// Again, don't forget to implement bounds check
	void reserve(const ll);
	void swap(matrix& right);

	// Methods for iterators
	const ll getRowSize();
	const ll getColSize();

	const Type* matrixBegin();
	const Type* matrixEnd();

	Type* rowBegin(const ll);
	Type* rowEnd(const ll);

	Type** colBegin(const ll);
	Type** colEnd(const ll);

private:
	// Currently used
	Type** allocateMatrix(ll, ll);
	Type** allocateColumnVector(ll);

	void deallocateMatrix(matrix&, ll, ll);

	// Should be deprecated
	void allocate(matrix&, ll, ll);
	void deallocate(matrix&, ll, ll);
};
