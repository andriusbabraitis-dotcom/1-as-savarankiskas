#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <numeric>

using std::string;
using std::vector;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas{};
    double galutinis{};

    void skaiciuotiGalutini() {
        if (!nd.empty()) {
            double vid = std::accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
            galutinis = 0.4 * vid + 0.6 * egzaminas;
        } else galutinis = egzaminas * 0.6;
    }
};

#endif
