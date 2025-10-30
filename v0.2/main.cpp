#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <iomanip>
#include "io_utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::deque;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

struct Timings {
    long long create_ms=0, read_ms=0, split_ms=0, write_ms=0;
};

template<class Container>
Timings test_konteineriui(const string& in_file,
                          const string& out1,
                          const string& out2) {
    Timings t{};
    auto t0 = steady_clock::now();

    Container c; 
    nuskaityti_i_konteineri(in_file, c);

    auto t1 = steady_clock::now();
    t.read_ms = duration_cast<milliseconds>(t1 - t0).count();

    auto t2 = steady_clock::now();
    skirti_is_konteinerio(c, out1, out2);
    auto t3 = steady_clock::now();
    t.split_ms = duration_cast<milliseconds>(t3 - t2).count();
    t.write_ms = 0; 
    return t;
}

static void spausdinti_t(const string& label, const Timings& t) {
    cout << std::left << std::setw(10) << label
         << " | create: " << std::setw(8) << t.create_ms << "ms"
         << " read: "   << std::setw(8) << t.read_ms   << "ms"
         << " split: "  << std::setw(8) << t.split_ms  << "ms"
         << " write: "  << std::setw(8) << t.write_ms  << "ms"
         << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const long long sizes[] = {1'000, 10'000, 100'000, 1'000'000, 10'000'000};

    cout << "=== v0.2 testavimas ===\n";

    for (long long n : sizes) {
        string in  = "studentai_" + std::to_string(n) + ".txt";
        string out1= "vargsiukai_" + std::to_string(n) + ".txt";
        string out2= "kietiakiai_" + std::to_string(n) + ".txt";

        Timings t_all{};

        auto a0 = steady_clock::now();
        generuoti_faila(in, n, 5);
        auto a1 = steady_clock::now();
        t_all.create_ms = duration_cast<milliseconds>(a1 - a0).count();

        auto s0 = steady_clock::now();
        stream_skirti_i_du(in, out1, out2);
        auto s1 = steady_clock::now();
        t_all.read_ms  = duration_cast<milliseconds>(s1 - s0).count();
        t_all.split_ms = 0;
        t_all.write_ms = 0;

        cout << "\nDydis: " << n << " įrašų\n";
        spausdinti_t("STREAM", t_all);

        Timings tv = test_konteineriui<vector<Studentas>>(in, "v_vargs_"+std::to_string(n)+".txt",
                                                             "v_kiet_"+std::to_string(n)+".txt");
        spausdinti_t("vector", tv);

        Timings tl = test_konteineriui<list<Studentas>>(in, "l_vargs_"+std::to_string(n)+".txt",
                                                           "l_kiet_"+std::to_string(n)+".txt");
        spausdinti_t("list", tl);

        Timings td = test_konteineriui<deque<Studentas>>(in, "d_vargs_"+std::to_string(n)+".txt",
                                                            "d_kiet_"+std::to_string(n)+".txt");
        spausdinti_t("deque", td);
      
    }

    cout << "\nBAIGTA.\n";
    return 0;
}
