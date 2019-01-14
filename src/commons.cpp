#include <string>
#include <sstream>
#include <limits>

#include "commons.h"

commons::commons() : rng()
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
    return gen_rand(0, std::numeric_limits<int>::max());
}

int commons::gen_rand(int lower_bound, int upper_bound)
{
    std::uniform_int_distribution<std::mt19937::result_type> int_in_range(lower_bound,
									  upper_bound);
    return int_in_range(rng);
}

std::string commons::gen_hex()
{
    std::stringstream sstream;
    sstream << std::hex << gen_rand();
    return sstream.str();
}
