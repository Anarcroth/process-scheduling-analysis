#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <random>

#include "process.h"
#include "priority.h"

process::process() : pr(set_pr()), id(set_id()), ttl(set_ttl())
{
}

process::process(priority p) : pr(p), id(set_id()), ttl(set_ttl())
{
}

process::process(priority p, unsigned int t) : pr(p), id(set_id()), ttl(t)
{
}

std::string process::get_id() const
{
    return id;
}

priority process::set_pr()
{
    return priority::MEDIUM;
}

std::string process::set_id()
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> raw_id;
    std::string temp_id = "";
    std::stringstream sstream;
    sstream << std::hex << raw_id(rng);

    return sstream.str().substr(0, 4);
}

unsigned int process::set_ttl()
{
    return 3000;
}
