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
    PR0,
    PR1,
    PR2,
    PR3,
    PR4,
    PR5,
    PR6,
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

    void set_ttl_passed(int _ttl);
    void set_prty(priority _prty);

    bool is_done();
    bool has_io();

    static const double PROCESS_TTL_MEAN;
    static const double PROCESS_TTL_STDDEV;
    static const double PROCESS_IO_MEAN;
    static const double PROCESS_IO_STDDEV;
    static const double IO_TTL_MEAN;
    static const double IO_TTL_STDDEV;

private:
    void set_state(state _stt);
    std::string set_id();
    int set_ttl();
    std::vector<int> set_ioops();

    int ttl_passed;
    state stt;
    priority prty;
    std::string id;
    int ttl;
    std::vector<int> ioops;
};

#endif
