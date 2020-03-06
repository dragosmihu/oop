#include <fstream>
#include<iostream>
#include<cmath>

using namespace std;
ifstream fin("TextFile1.txt");

class Numar_Complex {
	double re, im;
public:
	Numar_Complex() { this->im = 0; this->re = 0; }
	Numar_Complex(Numar_Complex const &n){
			this->re = n.re;
			this->im = n.im;
		}
	~Numar_Complex() = default;
	double Modul();
	Numar_Complex operator + (Numar_Complex const& obj) {
		Numar_Complex res;
		res.re = this->re + obj.re;
		res.im = this->im + obj.im;
		return res;
	}
	Numar_Complex operator *(Numar_Complex const& obj) {
		Numar_Complex res;
		res.re = this->re * obj.re - this->im * obj.im;
		res.im = this->re * obj.im + this->im * obj.re;
		return res;
	}
	friend ostream& operator <<(ostream& out, Numar_Complex const& obj) {
		out << obj.re << " + i * " << obj.im;
		return out;
	}
	friend istream& operator >>(istream& in, Numar_Complex &obj) {
		in >> obj.re >> obj.im;
		return in;
	}
	void operator =(const Numar_Complex& x) {
		this->re = x.re;
		this->im = x.im;
	}
};

class Vector_Complex : public Numar_Complex {
	int len;
	Numar_Complex* v;
public:
	Vector_Complex();
	Vector_Complex(Numar_Complex const &x, int n);
	Vector_Complex(Vector_Complex &w);
	~Vector_Complex() {
		delete[]v;
	}
	double* Get_VectorOfModules();
	int Get_Len() {
		return len;
	}
	void Sort();
	Numar_Complex Sum_Vector();
	Numar_Complex Prod_Scalar(Vector_Complex const&a);
	friend ostream& operator <<(ostream& out, Vector_Complex const& w) {
		out << w.len << "\n";
		for (int i = 0; i < w.len; i++)
			out << w.v[i] << ", ";
		return out;
	}
	friend istream& operator >>(istream& in, Vector_Complex & w) {
		in >> w.len;
		delete[] w.v;
		w.v = new Numar_Complex[w.len];
		for (int i = 0; i < w.len; i++)
			in >> w.v[i];
		return in;
	}
};

int main()
{
    Vector_Complex Vec, Vec2;
	fin >> Vec;
	cout << Vec << "\n"<< Vec.Sum_Vector() << "\n";
	double* p = Vec.Get_VectorOfModules();
	int n = Vec.Get_Len();
	for (int i = 0; i < n; i++, p++)
		cout << *p << ", ";
	p -= n;
	delete[] p;
	Vec.Sort();
	cout << Vec<< "\n";
	fin >> Vec2;
	cout << Vec.Prod_Scalar(Vec2);
	return 0;
}


double Numar_Complex::Modul() {
	return sqrt(this->re * this->re + this->im * this->im);
}

Vector_Complex::Vector_Complex() {
	len = 0;
	v = new Numar_Complex[0];
}

Vector_Complex::Vector_Complex(Numar_Complex const &x, int n) {
	len = n;
	v = new Numar_Complex[n];
	for (int i = 0; i < n; i++)
		v[i] = x;
}

Vector_Complex::Vector_Complex(Vector_Complex &w) {
	len = w.len;
	v = new Numar_Complex[len];
	for (int i = 0; i < len; i++)
		v[i] = w.v[i];
}

double* Vector_Complex::Get_VectorOfModules() {
	double* w = new double[len];
	for (int i = 0; i < len; i++)
		w[i] = v[i].Modul();
	return w;
}

void Vector_Complex::Sort() {
	int i, j;
	Numar_Complex aux;
	for (i = 0; i<len-1 ;i++)
		for (j = i + 1; j < len; j++) 
			if (v[i].Modul() > v[j].Modul()) {
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
}

Numar_Complex Vector_Complex::Sum_Vector() {
	Numar_Complex s;
	for (int i = 0; i < len; i++)
		s = s + v[i];
	return s;
}

Numar_Complex Vector_Complex::Prod_Scalar(Vector_Complex const& a) {
	Numar_Complex prod;
	for (int i = 0; i < a.len; i++)
		prod = prod + a.v[i] * v[i];
	return prod;
}
