#ifndef POKE_DS_H
#define POKE_DS_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#define NUM_TYPE 18
#define NUM_STAT 6
#define NUM_POKE 807

//you must not change those 4 functions
void initializer();
std::vector<int> poke_generator();
void terminator();
bool is_number(const std::string& s);
extern std::ifstream next_poke_f;

#endif // POKE_DS_H