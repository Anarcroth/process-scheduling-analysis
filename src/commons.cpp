#include <string>
#include <sstream>

#include "commons.h"

commons::commons() : rng(), raw_int()
{
    rng.seed(std::random_device()());
}

commons& commons::get()
{
    static commons instance;
    return instance;
}

int commons::gen_rand()
{
    return raw_int(rng);
}

int commons::gen_rand(int l, int h)
{
    std::uniform_int_distribution<std::mt19937::result_type> int_in_range(l, h);
    return int_in_range(rng);
}

std::string commons::gen_hex()
{
    std::stringstream sstream;
    sstream << std::hex << raw_int(rng);
    return sstream.str();
}
