#ifndef __COMMONS_H_INCLUDED__
#define __COMMONS_H_INCLUDED__

#include <random>

#include "process.hpp"

namespace commons
{
    int gen_even_rand();
    int gen_gaus_rand(double mean, double stddev);
    std::string gen_hex();
    std::string get_time(int t);
    std::string prtostr(priority prty);

    extern std::mt19937 rng;
    extern std::uniform_int_distribution<int> even_rand;
}

#endif
