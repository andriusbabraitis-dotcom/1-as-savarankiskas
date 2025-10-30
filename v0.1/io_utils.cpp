#include "io_utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <random>
#include <iomanip>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::runtime_error;
using std::vector;
using std::string;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::right;
using std::sort;

static bool yraSkaicius(const string& s) {
    if (s.empty()) return false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1u : 0u;
    for (; i < s.size(); ++i)
        if (!isdigit(static_cast<unsigned char>(s[i]))) return false;
    return true;
}

bool ivestiInteraktyviai(Studentas& s, GalutinioTipas tipas) {
    string vard, pav;
    cout << "Vardas Pavarde (arba 'q' nutraukti): ";
    if (!(cin >> vard)) return false;
    if (vard == "q" || vard == "Q") return false;
    cin >> pav;

    vector<int> nd;
    cout << "Iveskite ND (baigti – ne skaiciumi): ";
    int x;
    while (cin >> x) {
        if (x < 0 || x > 10) {
            cout << "ND turi buti tarp 0 ir 10.\n";
            continue;
        }
        nd.push_back(x);
    }
    cin.clear();
    string dummy; cin >> dummy;

    int egz;
    cout << "Egzamino rezultatas: ";
    cin >> egz;

    s = Studentas(vard, pav, nd, egz);
    s.skaiciuoti(tipas);
    return true;
}

vector<Studentas> nuskaitytiIsFailo(const string& kelias, GalutinioTipas tipas) {
    ifstream f(kelias);
    if (!f) throw runtime_error("Nepavyko atidaryti failo: " + kelias);

    vector<Studentas> grupe;
    string eil;
    getline(f, eil);

    while (getline(f, eil)) {
        if (eil.empty()) continue;
        istringstream is(eil);
        string pav, vard;
        is >> pav >> vard;
        vector<int> nd;
        int x;
        while (is >> x) nd.push_back(x);
        if (nd.empty()) continue;
        int egz = nd.back();
        nd.pop_back();

        Studentas s(vard, pav, nd, egz);
        s.skaiciuoti(tipas);
        grupe.push_back(s);
    }
    return grupe;
}

vector<Studentas> generuotiAtsitiktinius(int kiek, int ndMin, int ndMax, GalutinioTipas tipas) {
    std::random_device rd; std::mt19937 g(rd());
    std::uniform_int_distribution<int> bal(0, 10);
    std::uniform_int_distribution<int> kiekNd(ndMin, ndMax);

    vector<Studentas> v;
    for (int i = 0; i < kiek; i++) {
        int ndKiek = kiekNd(g);
        vector<int> nd;
        for (int j = 0; j < ndKiek; j++) nd.push_back(bal(g));
        int egz = bal(g);
        Studentas s("Vardas" + std::to_string(i+1), "Pavarde" + std::to_string(i+1), nd, egz);
        s.skaiciuoti(tipas);
        v.push_back(s);
    }
    return v;
}

void spausdintiLentele(const vector<Studentas>& grupe, bool rodytiVid, bool rodytiMed) {
    vector<Studentas> v = grupe;
    sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b) {
        if (a.pavarde() != b.pavarde()) return a.pavarde() < b.pavarde();
        return a.vardas() < b.vardas();
    });

    cout << left << setw(12) << "Pavarde"
         << left << setw(12) << "Vardas";
    if (rodytiVid) cout << left << setw(20) << "Galutinis (Vid.)";
    if (rodytiMed) cout << left << setw(20) << "Galutinis (Med.)";
    cout << endl << string(12+12+(rodytiVid?20:0)+(rodytiMed?20:0), '-') << endl;

    for (const auto& s : v) {
        cout << left << setw(12) << s.pavarde()
             << left << setw(12) << s.vardas();
        if (rodytiVid) {
            Studentas t = s; t.skaiciuoti(GalutinioTipas::Vidurkis);
            cout << right << setw(18) << fixed << setprecision(2) << t.galutinis() << "  ";
        }
        if (rodytiMed) {
            Studentas t = s; t.skaiciuoti(GalutinioTipas::Mediana);
            cout << right << setw(18) << fixed << setprecision(2) << t.galutinis() << "  ";
        }
        cout << endl;
    }
}
