#ifndef __PRIORITY_H_INCLUDED__
#define __PRIORITY_H_INCLUDED__

#include <string>

enum class priority
{
    LOW = 0,
    MEDIUM,
    HIGH,
    EXTREME
};

std::string prtostr(priority pr);

#endif
