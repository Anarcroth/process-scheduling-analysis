#include <string>
#include <sstream>
#include <limits>

#include "commons.h"
#include "process.h"
#include "priority.h"

commons::commons() : rng()
{
    rng.seed(std::random_device()());
}

commons& commons::get()
{
    static commons instance;
    return instance;
}

int commons::gen_rand()
{
    return gen_rand(0, std::numeric_limits<int>::max());
}

int commons::gen_rand(int lower_bound, int upper_bound)
{
    std::uniform_int_distribution<std::mt19937::result_type> int_in_range(lower_bound,
									  upper_bound);
    return int_in_range(rng);
}

std::string commons::gen_hex()
{
    std::stringstream sstream;
    sstream << std::hex << gen_rand();
    return sstream.str();
}

std::string commons::get_time(int t)
{
    t = t - 3600000 * (t / 3600000);
    long min = t / 60000;
    t = t - 60000 * min;
    long sec = t / 1000;
    t = t - 1000 * sec;
    std::ostringstream os;
    os << "Average waiting time -> minutes: "
       << min << ", seconds: "
       << sec << ", milliseconds: " << t;
    return os.str();
}

void commons::make_pr(int ch, std::vector<process> &pool)
{
    switch (ch)
    {
    case 'r':
	pool.push_back(process());
	break;
    case 'l':;
	pool.push_back(process(priority::LOW));
	break;
    case 'm':
	pool.push_back(process(priority::MEDIUM));
	break;
    case 'h':
	pool.push_back(process(priority::HIGH));
	break;
    case 'x':
	pool.push_back(process(priority::EXTREME));
	break;
    }
}
