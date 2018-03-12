#pragma once
#include<iostream>
#include<initializer_list>
#include <cstddef>
using namespace std;
using value_type = double;
using size_type = size_t;
using difference_type = ptrdiff_t;
using reference = double&;
using const_reference = const double&;
using pointer = double*;
using const_pointer = const double*;
using iterator = double*;
using const_iterator = const double*;
class Vector
{
	size_t max_size = 2;
	double *temp;
	size_t sz=0;				//Anzahl der gespeicherten Werte
	double *values;
	
public:
	


	class Iterator { //automatisch friend von Vector
			double *ptr;
			double *sptr;
			double *eptr;
			bool first{ false };
		public:
			Iterator(double* init_loc) {
				ptr=init_loc;
				sptr = init_loc;
			}
			Iterator& operator++() {
				if (!first && ptr + 1 == eptr) {
					ptr = sptr-1;
					first = true;
				};	
				++ptr;
				return *this;
			}
			bool operator!=(const Iterator& it2) {
				eptr = it2.ptr;
				if ((it2.ptr) == (this->ptr))
					return false;
				return true;
			}
			double& operator*() {
				return *ptr;
			}
			const double& operator*() const {
				return *ptr;
			}
	};
	Iterator begin() { return Iterator(values); }
	Iterator end() { return Iterator(values+sz ); }
	const Iterator begin() const { return Iterator(values); }
	const Iterator end() const { return Iterator(values+sz ); }
	Vector() {
		values = new double[max_size];
	}
	Vector(const Vector &v2) {
		max_size = v2.max_size;
		values = new double[max_size];
		sz = v2.size();
		for (size_t i = 0; i < v2.size(); i++) {
			values[i] = v2.values[i];
		};
		
	}
	Vector& operator =(const Vector v2) {
		max_size = v2.max_size;
		values = new double[max_size];
		sz = v2.size();
		for (size_t i = 0; i < v2.size(); i++) {
			values[i] = v2.values[i];
		};
		return *this;
	}

	~Vector() {
		delete[] values;
	}
	size_t size() const { return sz; }
	bool empty() const { if (!sz)return true; return false; }
	void push_back(double val) {
		if (max_size <=sz) {//neuer Platz muss gemacht 	werden
			reserve();
		}
		values[sz] = val; //Wertzuweisung
		sz++;
		//Zugriff erfolgt via values[i]
		

	}

	Vector(const initializer_list<double> list) {
		values = new double[max_size];
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
	double& operator[](size_t val) {
		if (sz <=val || empty()) throw runtime_error("Position nicht vorhanden");
		return values[val];
	}
	double& operator[](size_t val)const {
		if (sz <= val || empty()) throw runtime_error("Position nicht vorhanden");
		return values[val];
	}
	void clear() {
		this->sz = 0;
	}

	ostream& print(ostream & os) const {
		bool start = true;
		for (size_t i = 0; i < this->sz; i++) {
			if (!start) os << ",";
			start = false;
			os << this->values[i];
		};
		return os;
	}

	void shrink_to_fit() {
		max_size = sz;
	}
	void reserve() {
		max_size = sz * 2;//speicher verdoppeln
		temp = new double[max_size];
		for (size_t i = 0; i < sz; i++) {
			temp[i] = values[i];
		};
		delete[] values;
		values = temp;
		values = new double[max_size];
		for (size_t i = 0; i < sz ; i++) {
			values[i] = temp[i];
		};	
		delete[] temp;
	}
};
ostream& operator<<(ostream& os, const Vector& table) {
	table.print(os);
	return os;
}

