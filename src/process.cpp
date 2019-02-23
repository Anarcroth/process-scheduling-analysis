#include <string>
#include <algorithm>

#include "process.hpp"
#include "commons.hpp"

const double process::PROCESS_TTL_MEAN = 1000.0;
const double process::PROCESS_TTL_STDDEV = 15.0;
const double process::PROCESS_IO_MEAN = 10.0;
const double process::PROCESS_IO_STDDEV = 2.0;
const double process::IO_TTL_MEAN = 1500.0;
const double process::IO_TTL_STDDEV = 15.0;

process::process() : stt(state::NEW),
		     prty(priority::NONE),
		     id(set_id()),
		     ttl(set_ttl()),
		     ioops(set_ioops()) {}

process::process(priority p) : stt(state::NEW),
			       prty(p),
			       id(set_id()),
			       ttl(set_ttl()),
			       ioops(set_ioops()) {}

state process::get_state() const { return stt; }
priority process::get_prty() const { return prty; }
std::string process::get_id() const { return id; }
int process::get_ttl() const { return ttl; }
int process::get_next_io() const { return next_io; }
int process::get_ttl_passed() const { return ttl_passed; }
std::vector<int> process::get_ioops() const { return ioops; }

void process::set_state(state _stt)
{
    stt = _stt;
}

void process::set_prty(priority _prty)
{
    prty = _prty;
}

std::string process::set_id()
{
    std::string temp_id = commons::gen_hex().substr(1, 4);
    //std::transform(temp_id.begin(), temp_id.end(), temp_id.begin(), ::toupper);
    return temp_id;
}

void process::set_ttl(int _ttl)
{
    if (_ttl < 0) ttl = 0;
    else ttl = _ttl;
}

void process::set_ttl_passed(int _ttl)
{
    if (_ttl > ttl) ttl_passed = ttl;
    else ttl_passed = _ttl;
}

void process::set_nexi_io()
{
    next_io *= 2;
}

int process::set_ttl()
{
    // Guarantees no negative ttls
    int temp_ttl = 0;
    while (temp_ttl < 1)
	temp_ttl = commons::gen_gaus_rand(PROCESS_TTL_MEAN, PROCESS_TTL_STDDEV);

    return temp_ttl;
}

std::vector<int> process::set_ioops()
{
    // Creates a Gaussian distribution (0-20) IO operations
    // with a Gaussian distribution (02-3000ms) for each IO

    int number_of_ios = ttl;
    // Guarantees number of ios between 0 and the ttl
    while (number_of_ios >= ttl && number_of_ios < 0)
	number_of_ios = commons::gen_gaus_rand(PROCESS_IO_MEAN, PROCESS_IO_STDDEV);

    std::vector<int> temp_ioops(number_of_ios);
    for (size_t i = 0; i < number_of_ios; i++)
	temp_ioops.push_back(commons::gen_gaus_rand(IO_TTL_MEAN, IO_TTL_STDDEV));

    next_io = ttl / number_of_ios;

    return temp_ioops;
}
