#ifndef __COMMONS_H_INCLUDED__
#define __COMMONS_H_INCLUDED__

#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <random>

class commons
{
public:
    static commons& get();

    commons(commons const&)        = delete;
    void operator=(commons const&) = delete;

    std::string gen_hex();
private:
    commons();

    std::mt19937 rng;
    std::stringstream sstream;
    std::uniform_int_distribution<std::mt19937::result_type> raw_int;
};

#endif
