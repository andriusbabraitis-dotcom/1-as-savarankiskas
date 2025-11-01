#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas{};
    double galutinis{};

    void skaiciuotiGalutini() {
        if (!nd.empty()) {
            double vidurkis = std::accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
            galutinis = 0.4 * vidurkis + 0.6 * egzaminas;
        } else galutinis = egzaminas * 0.6;
    }
};

#endif
