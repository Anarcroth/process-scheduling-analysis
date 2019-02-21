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
int process::get_ttl() const { return ttl; }
std::vector<int> process::get_ioops() const { return ioops; }

void process::set_state(state _stt)
{
    stt = _stt;
}

priority process::set_prty()
{
    return static_cast<priority>(commons::get().gen_even_rand(0, 3));
}

std::string process::set_id()
{
    std::string temp_id = commons::get().gen_hex();
    temp_id = temp_id.substr(1, 4);
    std::transform(temp_id.begin(), temp_id.end(), temp_id.begin(), ::toupper);

    return temp_id;
}

void process::set_ttl(int _ttl)
{
    if (_ttl < 0) ttl = 0;
    else ttl = _ttl;
}

int process::set_ttl()
{
    return commons::get().gen_normal_rand(0, 4000); //ms
}

std::vector<int> process::set_ioops()
{
    // Creates a Gaussian distribution (0-20) IO operations
    // with a Gaussian distribution (0-3000ms) for each IO
    int number_of_ios = commons::get().gen_normal_rand(0, 20);
    std::vector<int> temp_ioops(number_of_ios);
    temp_ioops.reserve(number_of_ios);
    for (size_t i = 0; i < temp_ioops.size(); i++)
    {
	temp_ioops.push_back(commons::get().gen_normal_rand(10, 3000));
    }
    return temp_ioops;
}
