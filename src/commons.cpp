#include <string>
#include <sstream>
#include <limits>

#include "commons.hpp"

namespace commons
{
    std::mt19937 rng {std::random_device()()};
    std::uniform_int_distribution<int> even_rand(0, std::numeric_limits<int>::max());

    int gen_even_rand()
    {
	return even_rand(rng);
    }

    int gen_gaus_rand(double mean, double stddev)
    {
	std::normal_distribution<> gen_gaussian_rand {mean, stddev};
	return std::round(gen_gaussian_rand(rng));
    }

    std::string gen_hex()
    {
	std::stringstream sstream;
	sstream << std::hex << gen_even_rand();
	return sstream.str();
    }

    std::string get_time(int t)
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

    std::string prtostr(priority prty)
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
}
