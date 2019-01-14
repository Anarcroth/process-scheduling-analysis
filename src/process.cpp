#include <string>
#include <algorithm>

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

std::string process::get_pr() const
{
    switch(pr)
    {
    case priority::LOW:
	return "LOW";
    case priority::MEDIUM:
	return "MEDIUM";
    case priority::HIGH:
	return "HIGH";
    default:
	return "EXTREME";
    }
}

std::string process::get_id() const
{
    return id;
}

unsigned int process::get_ttl() const
{
    return ttl;
}

priority process::set_pr()
{
    return static_cast<priority>(commons::get().gen_rand() % 4);
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
