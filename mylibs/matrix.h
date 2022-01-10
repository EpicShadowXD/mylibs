#pragma once
#include <iostream>
#include <functional>
#include <tuple>

// Will never use negative numbers for matrix size
using ll = unsigned long long;

// Use tuple of storage space 1 instead of vector cuz 
// I won't allow myself to use #include <vector> ever
// in this project.
template <typename Type> class refWrapper
{
private:
	std::tuple<Type&> storage;

public:
	// Default constructor cuz std::reference_wrapper doesn't have one
	refWrapper() : storage(nullptr) {}

	// Constructor which takes as a parameter rvalue Type storage
	refWrapper(Type&& value) : storage(value) {}

	// Assign referenced value
	Type operator = (const Type index) { return std::get<0>(storage) = index; }

	// Type cast to Type&
	operator Type& () { return std::get<0>(storage); }

	decltype(&std::get<0>(storage)) operator & () { return &std::get<0>(storage); }
};

// TO-DO: create size method/ subclass to differentiate 
// between "user used" size and "memory allocated" size
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

	// TO-DO!
	// Memory management
	void fill(matrix& other, Type value);
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

private:
	void allocate(matrix&, ll, ll);
	void deallocate(matrix&, ll, ll);
	void copy(matrix&, const matrix, ll, ll);

private:
	ll numberOfColumns, numberOfRows;
	Type** data;
	Type* columnVector;
};
