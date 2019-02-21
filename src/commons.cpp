#include <string>
#include <sstream>
#include <limits>

#include "commons.hpp"

commons::commons() : rng()
{
    rng.seed(std::random_device()());
}

commons& commons::get()
{
    static commons instance;
    return instance;
}

int commons::gen_even_rand()
{
    return gen_even_rand(0, std::numeric_limits<int>::max());
}

int commons::gen_even_rand(int lower_bound, int upper_bound)
{
    std::uniform_int_distribution<std::mt19937::result_type> int_in_range(lower_bound,
									  upper_bound);
    return int_in_range(rng);
}

int commons::gen_normal_rand()
{
    return gen_normal_rand(0, std::numeric_limits<int>::max());
}

int commons::gen_normal_rand(int lower_bound, int upper_bound)
{
    std::normal_distribution<> int_in_range(lower_bound,
					    upper_bound);
    return std::round(int_in_range(rng));
}

std::string commons::gen_hex()
{
    std::stringstream sstream;
    sstream << std::hex << gen_even_rand();
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

std::string commons::prtostr(priority prty)
{
    switch(prty)
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
