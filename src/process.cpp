#include <string>

#include "process.h"
#include "commons.h"
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
    std::string temp_id = commons::get().gen_hex();
    temp_id = temp_id.substr(0, 4);
    std::transform(temp_id.begin(), temp_id.end(), temp_id.begin(), ::toupper);

    return temp_id;
}

unsigned int process::set_ttl()
{
    return 3000;
}
