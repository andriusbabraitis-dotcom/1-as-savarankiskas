#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>

using namespace std::chrono;

template <typename Container>
void testuotiKonteineri(int kiekis) {
    string failas = "studentai_" + std::to_string(kiekis) + ".txt";
    Container studentai;
    std::ifstream fd(failas);
    if (!fd.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    string header;
    getline(fd, header);

    auto start = high_resolution_clock::now();
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
    auto end = high_resolution_clock::now();
    cout << "Nuskaitymas uztruko: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    Container kietiakai, vargsiukai;

    for (auto &st : studentai) {
        if (st.galutinis >= 5.0)
            kietiakai.push_back(st);
        else
            vargsiukai.push_back(st);
    }

    end = high_resolution_clock::now();
    cout << "Skirstymas uztruko: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    std::ofstream fk("kietiakai_" + std::to_string(kiekis) + ".txt");
    std::ofstream fv("vargsiukai_" + std::to_string(kiekis) + ".txt");

    for (auto &s : kietiakai)
        fk << s.vardas << " " << s.pavarde << " " << s.galutinis << "\n";
    for (auto &s : vargsiukai)
        fv << s.vardas << " " << s.pavarde << " " << s.galutinis << "\n";

    fk.close();
    fv.close();
    end = high_resolution_clock::now();

    cout << "Isvedimas uztruko: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";
}
