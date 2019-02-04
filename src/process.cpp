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

priority process::get_pr() const { return pr; }

std::string process::get_id() const { return id; }

unsigned int process::get_ttl() const { return ttl; }

priority process::set_pr()
{
    return static_cast<priority>(commons::get().gen_rand(0, 3));
}

std::string process::set_id()
{
    std::string temp_id = commons::get().gen_hex();
    temp_id = temp_id.substr(1, 4);
    std::transform(temp_id.begin(), temp_id.end(), temp_id.begin(), ::toupper);

    return temp_id;
}

unsigned int process::set_ttl()
{
    switch (get_pr())
    {
    case priority::LOW:
	return commons::get().gen_rand(0, 300);
    case priority::MEDIUM:
	return commons::get().gen_rand(300, 900);
    case priority::HIGH:
	return commons::get().gen_rand(900, 1500);
    default: // priority::EXTREME
	return commons::get().gen_rand(1500, 3000);
    }
}
