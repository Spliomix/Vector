// VektorImplementierung.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

//#include "stdafx.h"
#include<unordered_map>
#include<stdexcept>
#include<algorithm>
#include<numeric>
#include<iterator>
#include<iostream>
#include"vector.h"

using namespace std;



	class Person {
		string vorname;
		string zuname;
		int alter;
	public:
		Person() {} //notwendig um leere Arrayeintraege zu initialisieren
		Person(string vorname, string zuname, int alter) : vorname{ vorname }, zuname{ zuname }, alter{ alter } {}
		virtual ~Person() {}
		string getName() const { return zuname + " " + vorname; }
		int getAlter() const { return alter; }
		void setAlter(int alter) {
			if (alter<0) throw runtime_error("alter muss >= 0 sein!");
			this->alter = alter;
		}
		virtual ostream& print(ostream& o) const {
			return o << "[" << zuname << ' ' << vorname << ' ' << alter << ']';
		}
		bool operator<(const Person& p) {
			return(this->alter<p.getAlter());
		}
	};

	class Angestellte : public Person {
		int personal_nummer;
	public:
	size_t count{0};
		Angestellte() : Person() {} //notwendig, um leere Arrayeintraege zu initialisieren
		Angestellte(string vorname, string zuname, int alter, int personal_nummer) : Person{ vorname, zuname, alter }, personal_nummer{ personal_nummer } {}
		ostream& print(ostream& o) const override {
			o << '*' << personal_nummer << '*';
			return Person::print(o);
		}
	};


	ostream& operator<<(ostream&o, const Person& p) {
		return p.print(o);
	}

	ostream& operator<<(ostream&o, const Vector <Person>& vp) {
	int sum =	accumulate(vp.begin(), vp.end(), 0, [](int sum, const Person& elem) {return sum + elem.getAlter(); });
		o<<"ALTER: "<<sum<<endl;
		return o;
	}

///////////////////////////Spezialisierung/////////////////////////
template<>
size_t Vector<Angestellte>::Const_Iterator::count(){
	return count_pp;
}
template<>
Vector<Angestellte>::Const_Iterator& Vector<Angestellte>::Const_Iterator::operator++(){
	if ((v->values + v->size()) == ptr) throw runtime_error("end() erreicht");
	if(!(ptr->getAlter()%2))
		++count_pp;
	++ptr;
	return *this;
}
//S////////////////////////////////////////////////////////////	

	int main() {
		Vector<int> vi{ 1,2,3,4,5 };
		cout << accumulate(vi.begin(), vi.end(), 0, [](int sum, int elem) {return sum + elem; }) << '\n';

		Vector<string> vs{ "a","bb","ccc" };
		vs.erase(find(vs.begin(), vs.end(), "bb"));
		for (auto& s : vs) s += "z";
		for (const auto& s : vs) cout << s << ' ';
		cout << '\n';

		Vector<Angestellte> va{ Angestellte{ "Otto","Mueller",39,5 }, Angestellte{ "Hans","Bauer",36,1 }, Angestellte{ "Lisa","Mueller",25,2 }, Angestellte{ "Maria", "Mayer",40,3 } };
		Vector<Person> vp;
		copy(va.begin(), va.end(), std::back_inserter(vp));
		for (const auto& p : va) cout << p << " ";
		cout << '\n';
		for (const auto& p : vp) cout << p << " ";

		cout << '\n'<<'\n';
		auto pos = vs.begin();
		transform(va.begin(), va.end(), std::inserter(vs, ++pos), [](const Angestellte& a) {return a.getName(); });
		for_each(vs.begin(), vs.end(), [](const string& s) {cout << s << '\n'; });
		cout << '\n';
		cout<<"VP:"<< vp;



		Angestellte a1{"Otto","Mueller",39,5};
		Angestellte a2{"Hans","Bauer",31,1};
		Vector<Person*>vvp{&a1, &a2};
		Vector<Person>vpp{a1, a2};
		cout<<"Person*:" ;
		for (const auto& i:vvp)
			cout<<*i<<" ";
		cout<<endl<<"Person: ";
		for(const auto& i:vpp)
			cout<< i <<" ";
		cout<<endl;
		// Was fehlt in der Klasse Person, damit das folgende Statement kompiliert?
		// Warum fehlt das nicht auch in der Klasse Angestellte?
		cout<<*max_element(va.begin(), va.end());

		// Geben Sie nun analog die juengste Angestellte aus (ohne weitere Aenderungen in Person bzw. Angestellte)
		
		//copy_if
		cout<<"copy_if"<<endl;
		Vector<int> v_copy_if{ 1,2,3,4,5 };
		Vector<int>target{0};
		copy_if(v_copy_if.begin(),v_copy_if.end(), back_inserter(target), 
		[] (int& i)->bool{return i%2;});
		for(const auto& i:target)
			cout<<i<<" ";
		cout<<endl;
		Vector<int>::Const_Iterator it{target.begin()};


		//count Funktion
		cout<<"count"<<endl;
		try{
			cout<<"count"<<(++it).count()<<endl;
		}catch (const std::runtime_error& e) {
       	 std::cout << e.what() << '\n';
    	}
		

		//Spezialisierung
		Vector<Angestellte>::Const_Iterator it2{va.begin()};
		cout<<"count mit Angestellte"<<endl;
		try{	
			cout<<"count: "<<(++it2).count()<<endl;
		}catch (const std::runtime_error& e) {
        	std::cout << e.what() << '\n';
    	}
	return 0;
}




