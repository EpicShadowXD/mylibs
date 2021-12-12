#pragma once
#include <iostream>

using ll = unsigned long long;	// Hotfix for potential loss of data warning

// TO-DO: create refference wrapper class
// TO-DO: create size method/ subclass to differentiate between "user used" size and "memory allocated" size
template <typename Type> class matrix
{
protected:
	ll numberOfColumns, numberOfRows;
	Type** data;

public:
	class iterator
	{
	protected:
		ll stride = NULL;
		Type* pointer;

	public:
		iterator() : pointer(nullptr) {}
		iterator(Type* ptr);

		// Dereference operator
		Type& operator * ();

		// Attribute operator
		Type* operator = (const iterator&);

		// Prefix
		Type& operator ++ ();
		Type& operator -- ();

		// Postfix
		iterator operator ++ (Type);
		iterator operator -- (Type);

		// Increment/ decrement by value
		Type& operator += (Type);
		Type& operator -= (Type);

		// Compare - to fix
		inline bool operator == (const iterator&);
		inline bool operator != (const iterator&);
	};

	// Constructors and destructors
	matrix();
	matrix(ll, ll);
	matrix(const matrix&);					// Copy constructor
	~matrix();

	// Attribution
	matrix operator = (const matrix&);

	// Hides data subcategory and can access data directly through instance
	Type*& operator [] (ll value);

	// Arithmetic
	// Note: does operations relative to the implied matrix's dimensions,
	//		meaning that the elements from a bigger matrix outside the scope
	//		of the implied matrix do not get touched. (potential logic error)
	matrix operator += (const matrix&);
	matrix operator -= (const matrix&);
	matrix operator *= (const matrix&);
	matrix operator + (const matrix&);
	matrix operator - (const matrix&);
	matrix operator * (const matrix&);

	// I want to get declaration outside the class but this fucking shit ass
	// fucking programming language won't fucking let me. I am so fucking mad.
	template <typename Type> friend std::ostream& operator << (std::ostream&, const matrix<Type>&);
	template <typename Type> friend std::istream& operator >> (std::istream&, matrix<Type>&);

	// TO-DO!
	// Memory management
	void resize(const ll numberOfColumns, const ll numberOfRows);	// Keeps memory, just destroys elements
	void shrink_to_fit();									// Frees up unused memory
	void erase(const ll colIndex, const ll rowIndex);
	void erase(const ll firstColIndex, const ll firstRowIndex,
		const ll secondColIndex, const ll secondRowIndex);
	void insert(const ll colIndex, const ll rowIndex);	// Requires automatic reallocation of memory; also don'Type forget to implement bounds check
	void at(const ll colIndex, const ll rowIndex);	// Again, don'Type forget to implement bounds check
	void reserve(ll n);
	void swap(matrix& right);
	void append(matrix& right);	// Concatenate two matrixes

	// Methods for iterators | Too lazy to implement exception handling rn
	Type* row_begin(const ll index);
	Type* row_end(const ll index);

	Type* col_begin(const ll index);
	Type* col_end(const ll index);

	// Size
	ll row_size(const ll index);
	ll col_size(const ll index);
};
