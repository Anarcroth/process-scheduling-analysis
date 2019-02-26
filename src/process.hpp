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
    EXTREME,
    NONE
};

class process
{
public:
    process();
    process(priority prty);

    state get_state() const;
    priority get_prty() const;
    std::string get_id() const;
    int get_ttl() const;
    int get_next_io() const;
    int get_ttl_passed() const;
    std::vector<int> get_ioops() const;

    void set_ttl(int _ttl);
    void set_ttl_passed(int _ttl);
    void incr_next_io();
    void set_prty(priority _prty);

private:
    void set_state(state _stt);
    std::string set_id();
    int set_ttl();
    std::vector<int> set_ioops();

    int next_io;
    int ttl_passed;
    state stt;
    priority prty;
    std::string id;
    int ttl;
    std::vector<int> ioops;

    static const double PROCESS_TTL_MEAN;
    static const double PROCESS_TTL_STDDEV;
    static const double PROCESS_IO_MEAN;
    static const double PROCESS_IO_STDDEV;
    static const double IO_TTL_MEAN;
    static const double IO_TTL_STDDEV;
};

#endif
