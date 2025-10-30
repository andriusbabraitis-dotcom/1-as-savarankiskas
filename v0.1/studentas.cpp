#include "studentas.h"
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

using std::accumulate;
using std::sort;
using std::runtime_error;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::right;

static double vidurkis(const vector<int>& v) {
    if (v.empty()) throw runtime_error("ND sarasas tuscias.");
    int suma = accumulate(v.begin(), v.end(), 0);
    return static_cast<double>(suma) / v.size();
}

static double mediana(vector<int> v) {
    if (v.empty()) throw runtime_error("ND sarasas tuscias.");
    sort(v.begin(), v.end());
    size_t n = v.size();
    return (n % 2) ? v[n/2] : (v[n/2 - 1] + v[n/2]) / 2.0;
}

Studentas::Studentas(const string& v, const string& p, const vector<int>& nd, int egz)
: vardas_(v), pavarde_(p), nd_(nd), egz_(egz) {}

Studentas::~Studentas() {
    vardas_.clear();
    pavarde_.clear();
    nd_.clear();
    egz_ = 0;
    galutinis_ = 0.0;
}

Studentas::Studentas(const Studentas& k)
: vardas_(k.vardas_), pavarde_(k.pavarde_), nd_(k.nd_), egz_(k.egz_), galutinis_(k.galutinis_) {}

Studentas& Studentas::operator=(const Studentas& rhs) {
    if (this != &rhs) {
        vardas_ = rhs.vardas_;
        pavarde_ = rhs.pavarde_;
        nd_ = rhs.nd_;
        egz_ = rhs.egz_;
        galutinis_ = rhs.galutinis_;
    }
    return *this;
}

void Studentas::skaiciuoti(GalutinioTipas tipas) {
    double pagrindas = (tipas == GalutinioTipas::Vidurkis) ? vidurkis(nd_) : mediana(nd_);
    galutinis_ = 0.4 * pagrindas + 0.6 * egz_;
}

istream& operator>>(istream& in, Studentas& s) {
    in >> s.vardas_ >> s.pavarde_;
    return in;
}

ostream& operator<<(ostream& out, const Studentas& s) {
    out << left << setw(12) << s.pavarde_
        << left << setw(12) << s.vardas_
        << right << setw(10) << fixed << setprecision(2) << s.galutinis_;
    return out;
}
