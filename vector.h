#pragma once
#include<iostream>
#include<initializer_list>
using namespace std;
class Vector
{
	size_t max_size = 2;
	double *temp;
	size_t sz=0;				//Anzahl der gespeicherten Werte
	double *values;
	
public:
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
		for (size_t i = 0; i < sz - 1 + 1; i++) {
			temp[i] = values[i];
		};
		delete[] values;
		values = new double[max_size];
		for (size_t i = 0; i < sz - 1 + 1; i++) {
			values[i] = temp[i];
		};	
		delete[] temp;
	}
};
ostream& operator<<(ostream& os, const Vector& table) {
	table.print(os);
	return os;
}

