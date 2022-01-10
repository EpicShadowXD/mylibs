#pragma once
#include <iostream>

// Hotfix for potential loss of data warning
using ll = unsigned long long;

// TO-DO: create refference wrapper class
// TO-DO: create size method/ subclass to differentiate between "user used" size and "memory allocated" size
template <typename Type> class matrix
{
public:
	class iterator
	{
	public:
		iterator() : pointer(nullptr) {}
		iterator(Type* ptr);

		Type& operator * ();

		Type* operator = (const iterator&);

		// Prefix
		Type& operator ++ ();
		Type& operator -- ();

		// Postfix
		iterator operator ++ (Type);
		iterator operator -- (Type);

		Type& operator += (const Type);
		Type& operator -= (const Type);

		bool operator == (const iterator&);
		bool operator != (const iterator&);

	protected:
		Type* pointer;
	};

public:
	matrix() :	numberOfColumns(NULL), numberOfRows(NULL), data(nullptr), columnVector(nullptr) {}
	matrix(const ll, const ll);
	matrix(const matrix&);					// Copy constructor
	~matrix();

	// Attribution
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

	// Algebra - TODO
	matrix operator + (const double scalar);
	matrix operator - (const double scalar);
	matrix operator * (const double scalar);

	matrix operator += (const double scalar);
	matrix operator -= (const double scalar);
	matrix operator *= (const double scalar);

	// Iostream output
	template <typename Type> friend std::ostream& operator << (std::ostream&, const matrix<Type>&);
	template <typename Type> friend std::istream& operator >> (std::istream&, matrix<Type>&);

	// TO-DO!
	// Memory management
	void resize(const ll numberOfColumns, const ll numberOfRows);	// Keeps memory, just destroys elements
	void resize(const ll numberOfColumns, const ll numberOfRows, double value);	// Initialize potential new empty spaces with value
	void shrink_to_fit();											// Frees up unused memory defined as all 0s on a row or column
	void erase(const ll colIndex, const ll rowIndex);
	void erase(const ll firstColIndex, const ll firstRowIndex,
		const ll secondColIndex, const ll secondRowIndex);
	void insert(const ll colIndex, const ll rowIndex);				// Requires automatic reallocation of memory; also don'Type forget to implement bounds check
	void at(const ll colIndex, const ll rowIndex);					// Again, don't forget to implement bounds check
	void reserve(ll n);
	void swap(matrix& right);

	// Methods for iterators
	const ll getRowSize();
	const ll getColSize();

	Type* rowBegin(const ll index);
	Type* rowEnd(const ll index);

	Type* colBegin(const ll index);
	Type* colEnd(const ll index);

protected:
	ll numberOfColumns, numberOfRows;
	Type** data;
	Type* columnVector;
};
