#include <string>
#include <algorithm>

#include "process.hpp"
#include "commons.hpp"

process::process() : stt(state::NEW),
		     prty(set_prty()),
		     id(set_id()),
		     ttl(set_ttl()),
		     ioops(set_ioops()) {}

process::process(priority p) : stt(state::NEW), prty(p), id(set_id()), ttl(set_ttl()) {}

state process::get_state() const { return stt; }
priority process::get_prty() const { return prty; }
std::string process::get_id() const { return id; }
unsigned int process::get_ttl() const { return ttl; }
std::vector<unsigned int> process::get_ioops() const { return ioops; }

void process::set_state(state _stt)
{
    stt = _stt;
}

priority process::set_prty()
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
    switch (prty)
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

std::vector<unsigned int> process::set_ioops()
{
    std::vector<unsigned int> temp_ioops(commons::get().gen_rand());
    for (size_t i = 0; i < temp_ioops.size(); i++)
    {
	temp_ioops.push_back(commons::get().gen_rand());
    }
    return temp_ioops;
}
