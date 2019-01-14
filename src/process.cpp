#include <string>
#include <algorithm>

#include "process.h"
#include "commons.h"
#include "priority.h"

process::process() : pr(get_pr()), id(get_id()), ttl(get_ttl())
{
}

process::process(priority p) : pr(p), id(get_id()), ttl(get_ttl())
{
}

process::process(priority p, unsigned int t) : pr(p), id(get_id()), ttl(t)
{
}

priority process::get_pr()
{
    return static_cast<priority>(commons::get().gen_rand(0, 3));
}

std::string process::get_id()
{
    std::string temp_id = commons::get().gen_hex();
    temp_id = temp_id.substr(1, 4);
    std::transform(temp_id.begin(), temp_id.end(), temp_id.begin(), ::toupper);

    return temp_id;
}

unsigned int process::get_ttl()
{
    return ttl;
}
