#include <string>
#include <algorithm>

#include "process.hpp"
#include "commons.hpp"

const double process::PROCESS_TTL_MEAN = 1000.0;
const double process::PROCESS_TTL_STDDEV = 270.0;
const double process::PROCESS_IO_MEAN = 10.0;
const double process::PROCESS_IO_STDDEV = 2.0;
const double process::IO_TTL_MEAN = 1500.0;
const double process::IO_TTL_STDDEV = 150.0;

process::process() : tat(0),
		     tos(-1),
		     toc(0),
		     work_done(0),
		     prev_exec_t(0),
		     wait_t(0),
		     stt(state::NEW),
		     prty(priority::NONE),
		     id(set_id()),
		     ttl(set_ttl()),
		     ioops(set_ioops()){}

process::process(priority p) : tat(0),
			       tos(-1),
			       toc(0),
			       work_done(0),
			       prev_exec_t(0),
			       wait_t(0),
			       stt(state::NEW),
			       prty(p),
			       id(set_id()),
			       ttl(set_ttl()),
			       ioops(set_ioops()) {}

int process::get_tat() const { return tat; }
int process::get_tos() const { return tos; }
int process::get_toc() const { return toc; }
int process::get_ttl() const { return ttl; }
int process::get_work_done() const { return work_done; }
int process::get_prev_exec_t() const { return prev_exec_t; }
int process::get_wait_t() const { return wait_t; }
state process::get_state() const { return stt; }
priority process::get_prty() const { return prty; }
std::string process::get_id() const { return id; }
std::vector<int> process::get_ioops() const { return ioops; }

void process::set_tos(int _tos)
{
    if (tos < 0)
	tos = _tos;
}

void process::set_toc(int _toc)
{
    toc = _toc;
}

void process::set_work_done(int _ttl)
{
    // TODO Fix this bs
    if (_ttl > ttl) work_done = ttl;
    else work_done += _ttl;
}

void process::set_prev_exec_time(int _pet)
{
    prev_exec_t = _pet;
}

void process::set_prty(priority _prty)
{
    prty = _prty;
}

void process::add_tat(int _tat)
{
    tat += _tat;
}

void process::add_wait_t(int curr_t)
{
    if (curr_t != prev_exec_t) {
	wait_t += curr_t - prev_exec_t;
    }
}

bool process::is_done()
{
    return (work_done >= ttl) ? true : false;
}

bool process::has_io()
{
    return (commons::gen_even_rand() % 2 == 1) ? true : false;
}

void process::set_state(state _stt)
{
    stt = _stt;
}

std::string process::set_id()
{
    std::string temp_id = commons::gen_hex().substr(1, 4);
    return temp_id;
}

int process::set_ttl()
{
    // Guarantees no negative ttls
    int temp_ttl = 0;
    while (temp_ttl < 1)
    {
	temp_ttl = commons::gen_gaus_rand(PROCESS_TTL_MEAN, PROCESS_TTL_STDDEV);
    }

    return temp_ttl;
}

std::vector<int> process::set_ioops()
{
    // Creates a Gaussian distribution (0-20) IO operations
    // with a Gaussian distribution (02-3000ms) for each IO
    int number_of_ios = commons::gen_gaus_rand(PROCESS_IO_MEAN, PROCESS_IO_STDDEV);
    std::vector<int> temp_ioops(number_of_ios);
    for (size_t i = 0; i < number_of_ios; i++)
    {
	temp_ioops.push_back(commons::gen_gaus_rand(IO_TTL_MEAN, IO_TTL_STDDEV));
    }

    return temp_ioops;
}
