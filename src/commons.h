#ifndef __COMMONS_H_INCLUDED__
#define __COMMONS_H_INCLUDED__

#include <string>
#include <random>

class commons
{
public:
    static commons& get();

    commons(commons const&)        = delete;
    void operator=(commons const&) = delete;

    int gen_rand();
    int gen_rand(int l, int h);
    std::string gen_hex();

private:
    commons();

    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> raw_int;
};

#endif
