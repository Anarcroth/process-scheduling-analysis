#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "commons.h"

commons::commons() : rng(), sstream(), raw_int()
{
    rng.seed(std::random_device()());
}

commons& commons::get()
{
    static commons instance;
    return instance;
}

std::string commons::gen_hex()
{
    sstream << std::hex << raw_int(rng);
    return sstream.str();
}
