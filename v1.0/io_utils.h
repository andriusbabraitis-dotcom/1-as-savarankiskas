#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <vector>
#include <list>
#include <deque>
#include <string>
#include "studentas.h"

using std::string;
using std::vector;
using std::list;
using std::deque;

void generuotiFaila(int kiekis, const string& pavadinimas);
template <typename Container>
void testuotiStrategijas(int kiekis);

#include "io_utils.tpp"
#endif
