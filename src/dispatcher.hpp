#include <mutex>

#include "process.hpp"

namespace dispatcher
{
    extern std::mutex iomutex;

    void interrupt(std::vector<process>::iterator& pit, int tq);
    void context_switch(std::vector<process>::iterator& pit, int tq);
    void save_state(std::vector<process>::iterator& pit, int ttl_p);
    void restore_state(std::vector<process>::iterator& pit);
    void exec_io(std::vector<process>::iterator pit);
}
