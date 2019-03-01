#include "process.hpp"

namespace dispatcher
{
    void interrupt();
    void context_switch(std::vector<process>::iterator& pit, int ttl);
    void save_state(std::vector<process>::iterator& pit, int ttl_p);
    void restore_state(std::vector<process>::iterator& pit);
}
