#include <mutex>

#include "process.hpp"
#include "./cfs/rbtree.hpp"

namespace dispatcher
{
    extern std::mutex iomutex;

    void interrupt(std::vector<process>::iterator& pit, int tq);
    void context_switch(std::vector<process>::iterator& pit, int tq);
    void save_state(std::vector<process>::iterator& pit, int ttl_p);
    void restore_state(std::vector<process>::iterator& pit);
    void exec_io(std::vector<process>::iterator pit);

    namespace cfs
    {
	void interpt(process &pit, int tq, rbtree &rbt);
	void con_swch(process &pit, int tq, rbtree &rbt);
	void save_st(process &pit, int ttl_p);
	void restore_st(process &pit, rbtree &rbt);
	void ex_io(std::vector<process>::iterator pit);
    }
}
