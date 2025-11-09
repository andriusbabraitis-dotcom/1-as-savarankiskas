#include "io_utils.h"
#include <fstream>
#include <random>
#include <iostream>

using std::ofstream;
using std::cout;
using std::endl;

void generuotiFaila(int kiekis, const string& pavadinimas) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    ofstream f(pavadinimas);
    f << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n";
    for (int i = 0; i < kiekis; i++) {
        f << "Vardas" << i + 1 << " Pavarde" << i + 1;
        for (int j = 0; j < 5; j++) f << " " << dist(gen);
        f << " " << dist(gen) << "\n";
    }
}
