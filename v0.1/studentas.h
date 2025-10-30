#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::istream;
using std::ostream;

enum class GalutinioTipas { Vidurkis, Mediana };

class Studentas {
	string vardas_;
	string pavarde_;
	vector<int> nd_;
	int egz_ = 0;
	double galutinis_ = 0.0;

public:
	Studentas() = default;
	Studentas(const string& v, const string& p, const vector<int>& nd, int egz);

	~Studentas();
	Studentas(const Studentas& kitas);
	Studentas& operator=(const Studentas& rhs);

	void skaiciuoti(GalutinioTipas tipas);
	const string& vardas() const {
		return vardas_;
	}
	const string& pavarde() const {
		return pavarde_;
	}
	double galutinis() const {
		return galutinis_;
	}

	friend istream& operator>>(istream& in, Studentas& s);
	friend ostream& operator<<(ostream& out, const Studentas& s);
};
