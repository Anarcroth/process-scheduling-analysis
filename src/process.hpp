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

/*
 * Description: The process class imitates a real process, but without
 * the work of a process. Instead of creating `PCB` object and filling
 * them with empty processes, which would cause lasagna code, this
 * method makes things clearer and more concrete.
 *
 * The process class keeps track of its different statistics, which
 * are then summarized in the end for the final evaluation.
 * Each process can have a pre-defined priority, or it can be evaluated
 * upon creation, based on a normal distribution.
 */
class process
{
public:
    process();
    process(priority prty);

    int get_tat() const;
    int get_tos() const;
    int get_toc() const;
    int get_ttl() const;
    int get_work_done() const;
    state get_state() const;
    priority get_prty() const;
    std::string get_id() const;
    std::vector<int> get_ioops() const;

    void set_tos(int _tos);
    void set_toc(int _toc);
    void set_work_done(int _ttl);
    void set_prty(priority _prty);

    void add_tat(int _tat);

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

    int tat;                /* turnaround time */
    int tos;                /* time of submission */
    int toc;                /* time of completion */
    int work_done;          /* work done in time units */
    state stt;              /* process state */
    priority prty;          /* process priority */
    std::string id;         /* process id */
    int ttl;                /* time to live */
    std::vector<int> ioops; /* set of IO operations */
};

#endif
