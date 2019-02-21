#ifndef __COMMONS_H_INCLUDED__
#define __COMMONS_H_INCLUDED__

#include <random>
#include <memory>

#include "process.hpp"

class commons
{
public:
    static commons& get();

    commons(commons const&)        = delete;
    void operator=(commons const&) = delete;

    int gen_even_rand();
    int gen_even_rand(int lower_bound, int upper_bound);
    int gen_normal_rand();
    int gen_normal_rand(int lower_bound, int upper_bound);
    std::string gen_hex();
    std::string get_time(int t);
    std::string prtostr(priority prty);

private:
    commons();

    std::mt19937 rng;
};

#endif
