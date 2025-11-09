#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std::chrono;
using std::cout;
using std::endl;

template <typename Container>
void testuotiStrategijas(int kiekis) {
    string failas = "studentai_" + std::to_string(kiekis) + ".txt";
    std::ifstream fd(failas);
    if (!fd.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    string header;
    getline(fd, header);

    Container studentai;
    string vardas, pavarde;
    while (fd >> vardas >> pavarde) {
        Studentas s;
        s.vardas = vardas;
        s.pavarde = pavarde;
        for (int i = 0; i < 5; i++) {
            int paz;
            fd >> paz;
            s.nd.push_back(paz);
        }
        fd >> s.egzaminas;
        s.skaiciuotiGalutini();
        studentai.push_back(s);
    }

    // --- 1 strategija: kopijuojant ---
    auto t1 = high_resolution_clock::now();
    Container kietiakai, vargsiukai;
    for (auto& s : studentai) {
        if (s.galutinis >= 5.0) kietiakai.push_back(s);
        else vargsiukai.push_back(s);
    }
    auto t2 = high_resolution_clock::now();
    cout << "[1 strategija] Kopijavimas: "
         << duration_cast<milliseconds>(t2 - t1).count() << " ms\n";

    // --- 2 strategija: trynimas iš bendro konteinerio ---
    Container s_copy = studentai;
    auto t3 = high_resolution_clock::now();
    Container varg2;
    for (auto it = s_copy.begin(); it != s_copy.end();) {
        if (it->galutinis < 5.0) {
            varg2.push_back(*it);
            it = s_copy.erase(it);
        } else ++it;
    }
    auto t4 = high_resolution_clock::now();
    cout << "[2 strategija] Trynimas: "
         << duration_cast<milliseconds>(t4 - t3).count() << " ms\n";

    // --- 3 strategija: STL algoritmai ---
    if constexpr (std::is_same_v<Container, vector<Studentas>>) {
        auto t5 = high_resolution_clock::now();
        auto it = std::stable_partition(studentai.begin(), studentai.end(),
                                        [](const Studentas& s){ return s.galutinis < 5.0; });
        auto t6 = high_resolution_clock::now();
        cout << "[3 strategija] std::partition (vektorius): "
             << duration_cast<milliseconds>(t6 - t5).count() << " ms\n";
    }

    cout << "-----------------------------------\n";
}
