#include "priority.hpp"

std::string prtostr(priority pr)
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
