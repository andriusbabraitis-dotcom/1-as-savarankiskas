#include "io_utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>

using std::ofstream;
using std::cout;
using std::endl;
using std::setw;

void generuotiFaila(int kiekis, const string &pavadinimas) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    ofstream fr(pavadinimas);
    fr << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n";

    for (int i = 0; i < kiekis; i++) {
        fr << "Vardas" << i + 1 << " Pavarde" << i + 1;
        for (int j = 0; j < 5; j++) fr << " " << dist(gen);
        fr << " " << dist(gen) << "\n";
    }

    fr.close();
}
