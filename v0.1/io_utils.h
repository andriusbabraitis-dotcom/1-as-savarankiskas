#pragma once
#include <vector>
#include <string>
#include "studentas.h"

using std::vector;
using std::string;

bool ivestiInteraktyviai(Studentas& s, GalutinioTipas tipas);
vector<Studentas> nuskaitytiIsFailo(const string& kelias, GalutinioTipas tipas);
vector<Studentas> generuotiAtsitiktinius(int kiek, int ndMin, int ndMax, GalutinioTipas tipas);
void spausdintiLentele(const vector<Studentas>& grupe, bool rodytiVid, bool rodytiMed);
