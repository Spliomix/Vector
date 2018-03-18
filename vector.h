#pragma once
#include<iostream>
#include<initializer_list>
#include <cstddef>
#include <algorithm>
using namespace std;

class Vector
{

public:
	class Iterator;
	class Const_Iterator;
	using value_type = double;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = double&;
	using const_reference = const double&;
	using pointer = double*;
	using const_pointer = const double*;
	using iterator = Iterator;
	using const_iterator = Const_Iterator;
private:
	size_type max_size = 2;
	size_type sz=0;				//Anzahl der gespeicherten Werte
	pointer values;

public:
	class Iterator { //automatisch friend von Vector
		public:
		using const_reference = Vector::const_reference;
			using value_type= Vector::value_type;
			using difference_type=Vector::difference_type;
			using reference = Vector::reference;
			using pointer = Vector::pointer;
			using size_type = Vector::size_type;
			using iterator_category= std::forward_iterator_tag;
	private:
				pointer ptr;
				size_type first{ 1 };
				Vector *v;
	public:
				Iterator(pointer init_loc,Vector *v ) {
					ptr=init_loc;
					this->v=v;
				}
				Iterator() {

				}
				Iterator& operator++() {
					if ((v->values + v->size()) == ptr) throw runtime_error("end() erreicht");
						++ptr;
					return *this;
				}

				Iterator operator++(int) {
					if ((v->values + v->size()) == ptr+1) throw runtime_error("end() erreicht");
					iterator old(*this);
					 ++*this;

					return old;
				}

				pointer operator->(){
					if ((v->values + v->size()) == ptr) throw runtime_error("end() erreicht");
					return ptr;
				}




				bool operator!=(const Iterator& it2) {
					if ((it2.ptr) == (this->ptr))
						return false;
					return true;
				}
				bool operator==(const Iterator& it2){
					if ((it2.ptr) == (this->ptr))
						return true;
					return false;
				}
				reference operator*() {
					if ((v->values + v->size())==ptr) throw runtime_error("end() erreicht");
					return *ptr;
				}


				operator Const_Iterator() {	
					return Const_Iterator(ptr, v);
				}
				
				

	};

class Const_Iterator { //automatisch friend von Vector
		public:
			using const_reference = Vector::const_reference;
			using value_type= Vector::value_type;
			using difference_type=Vector::difference_type;
			using reference = Vector::reference;
			using pointer = Vector::pointer;
			using size_type = Vector::size_type;
			using iterator_category= std::forward_iterator_tag;
	private:
				pointer ptr;
				const Vector *v;
	public:
		Const_Iterator(pointer init_loc, const Vector *v) {
					ptr=init_loc;
					this->v = v;
				}
		Const_Iterator() {
				}
		Const_Iterator(const Const_Iterator &it2) {
			this->v = it2.v;
			this->ptr = it2.ptr;
		}
		Const_Iterator& operator++() {
			if ((v->values + v->size()) == ptr) throw runtime_error("end() erreicht");
						++ptr;		
					return *this;
				}
				bool operator!=(const Const_Iterator& it2) const {
					if ((it2.ptr) == (this->ptr))
						return false;
					return true;
				}
				bool operator==(const Const_Iterator& it2) const {
					if ((it2.ptr) == (this->ptr))
						return true;
					return false;
				}
				const_reference operator*() const {
					if ((v->values + v->size()) == ptr ) throw runtime_error("end() erreicht");
					return *ptr;
				}


				Const_Iterator operator++(int) {
					if ((v->values + v->size()) == ptr+1) throw runtime_error("end() erreicht");
					Const_Iterator old(*this);
					 ++*this;		
					return old;					
				}

				pointer operator->(){
					if ((v->values + v->size()) == ptr) throw runtime_error("end() erreicht");
					return ptr;
				}

				
				friend difference_type operator-(const Const_Iterator& lop,
					const Const_Iterator& rop) {
					return lop.ptr - rop.ptr;
					
				}
				friend bool operator==(const Const_Iterator& lop,
					const Const_Iterator& rop) {
					if (lop.ptr == rop.ptr)return true;
					return false;

				}

				
	};

	
	Iterator begin() { return Iterator(values, this); }
	Iterator end() { return Iterator(values+sz, this ); }
	Const_Iterator begin() const {  return Const_Iterator(values, this); }
	Const_Iterator end() const { return Const_Iterator(values+sz, this ); }

	Vector() {
		values = new value_type[max_size];
	}
	Vector(const Vector &v2) {
		max_size = v2.max_size;
		values = new value_type[max_size];
		sz = v2.size();
		for (size_type i = 0; i < v2.size(); i++) {
			values[i] = v2.values[i];
		};
		
	}
	Vector& operator =(const Vector v2) {
		max_size = v2.max_size;
		values = new value_type[max_size];
		sz = v2.size();
		for (size_type i = 0; i < v2.size(); i++) {
			values[i] = v2.values[i];
		};
		return *this;
	}


	Iterator erase(Const_Iterator it) {
		//auto diff = it.operator->() - begin().operator->();
		auto diff = it - begin();
		if (diff<0 || static_cast<size_type>(diff) >= sz)
			throw runtime_error("Iterator out of bounds");
		size_type current{ static_cast<size_type>(diff) };
		
		for (size_type i{ current }; i<sz - 1; ++i)
			values[i] = values[i + 1];
		--sz;
		return Iterator( values+current , this );
	}

	Iterator insert(Const_Iterator pos, const_reference val) {
		auto diff = pos - begin();
		if (diff<0 || static_cast<size_type>(diff)>sz)
			throw runtime_error("Iterator out of bounds");
		size_type current{ static_cast<size_type>(diff) };
		if (sz >= max_size)
			reserve(max_size * 2); //max_sz*2+10, wenn Ihr Container max_sz==0 erlaubt
		for (size_t i{ sz }; i-->current;)
			values[i + 1] = values[i];
		values[current] = val;
		++sz;
		return iterator(values + current, this );
	}


	~Vector() {
		delete[] values;
	}
	size_type size() const { return sz; }
	bool empty() const { if (!sz)return true; return false; }
	void push_back(value_type val) {
		if (max_size <=sz) {//neuer Platz muss gemacht 	werden
			reserve(max_size*2);
		}
		values[sz] = val; //Wertzuweisung
		sz++;
		//Zugriff erfolgt via values[i]
		

	}

	Vector(const initializer_list<value_type> list) {
		values = new value_type[max_size];
		// Now initialize our array from the list
		for (auto &element : list)
		{		
			push_back(element);
		}
	}
	void pop_back() {
		if (this->sz == 0) throw runtime_error("Vektor ist leer");
		sz--;
		
	}
	reference operator[](size_type val) {
		if (sz <=val || empty()) throw runtime_error("Position nicht vorhanden");
		return values[val];
	}
	reference operator[](size_type val)const {
		if (sz <= val || empty()) throw runtime_error("Position nicht vorhanden");
		return values[val];
	}
	void clear() {
		this->sz = 0;
	}

	ostream& print(ostream & os) const {
		bool start = true;
		for (size_type i = 0; i < this->sz; i++) {
			if (!start) os << ",";
			start = false;
			os << this->values[i];
		};
		return os;
	}

	void shrink_to_fit() {
		max_size = sz;
		if (max_size == 0)max_size = 1;
	}
	void reserve(size_type new_maxsize) {
		pointer temp;
		max_size = new_maxsize;//speicher verdoppeln
		temp = new value_type[max_size];
		for (size_type i = 0; i < sz; i++) {
			temp[i] = values[i];
		};
		delete[] values;
		values = temp;


		
	}



};
ostream& operator<<(ostream& os, const Vector& vector) {
	vector.print(os);
	return os;
}
