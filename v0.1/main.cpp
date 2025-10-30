#include <iostream>
#include <vector>
#include <stdexcept>
#include "studentas.h"
#include "io_utils.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main() {
    try {
        cout << "Pasirinkite veiksma:\n"
             << "1 - Interaktyviai suvesti studentus\n"
             << "2 - Skaityti is failo (kursiokai.txt)\n"
             << "3 - Generuoti atsitiktinius\n"
             << "Jusu pasirinkimas: ";
        int veiksmas = 0; cin >> veiksmas;

        cout << "Rodyti (1) Vidurki, (2) Mediana, (3) Abu: ";
        int show = 3; cin >> show;
        bool rodytiVid = (show == 1 || show == 3);
        bool rodytiMed = (show == 2 || show == 3);

        vector<Studentas> grupe;

        if (veiksmas == 1) {
            while (true) {
                cout << "\n--- Naujas studentas ---\n";
                Studentas s;
                if (!ivestiInteraktyviai(s, GalutinioTipas::Vidurkis)) break;
                grupe.push_back(s);
            }
        } else if (veiksmas == 2) {
            grupe = nuskaitytiIsFailo("kursiokai.txt", GalutinioTipas::Vidurkis);
        } else if (veiksmas == 3) {
            int kiek;
            cout << "Kiek studentu generuoti? "; cin >> kiek;
            grupe = generuotiAtsitiktinius(kiek, 3, 6, GalutinioTipas::Vidurkis);
        } else {
            cout << "Neteisingas pasirinkimas.\n";
            return 0;
        }

        if (grupe.empty()) {
            cout << "Nera duomenu.\n";
            return 0;
        }

        spausdintiLentele(grupe, rodytiVid, rodytiMed);
    }
    catch (const std::exception& e) {
        cout << "Klaida: " << e.what() << endl;
        return 1;
    }
    return 0;
}
