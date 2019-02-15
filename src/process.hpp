#ifndef __PROCESS_H_INCLUDED__
#define __PROCESS_H_INCLUDED__

#include <vector>
#include <string>

enum class state : unsigned short
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

enum class priority : unsigned short
{
    LOW,
    MEDIUM,
    HIGH,
    EXTREME
};

class process
{
public:
    process();
    process(priority prty);

    state get_state() const;
    priority get_prty() const;
    std::string get_id() const;
    unsigned int get_ttl() const;
    std::vector<unsigned int> get_ioops() const;

private:
    void set_state(state _stt);
    priority set_prty();
    std::string set_id();
    unsigned int set_ttl();
    std::vector<unsigned int> set_ioops();

    state stt;
    priority prty;
    std::string id;
    unsigned int ttl;
    std::vector<unsigned int> ioops;
};

#endif
