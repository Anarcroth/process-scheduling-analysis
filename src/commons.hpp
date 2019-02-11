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

    int gen_rand();
    int gen_rand(int lower_bound, int upper_bound);
    std::string gen_hex();

    std::string get_time(int t);

private:
    commons();

    std::mt19937 rng;
};

#endif
