#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "io_utils.h"

using std::cout;
using std::endl;

int main() {
    vector<int> dydziai = {1000, 10000, 100000};

    for (int n : dydziai) {
        cout << "\n==== Testuojamas dydis: " << n << " ====\n";
        generuotiFaila(n, "studentai_" + std::to_string(n) + ".txt");

        cout << "\n[Vector]\n";
        testuotiStrategijas<std::vector<Studentas>>(n);

        cout << "\n[List]\n";
        testuotiStrategijas<std::list<Studentas>>(n);

        cout << "\n[Deque]\n";
        testuotiStrategijas<std::deque<Studentas>>(n);
    }

    cout << "\nVisi testai baigti!\n";
    return 0;
}
