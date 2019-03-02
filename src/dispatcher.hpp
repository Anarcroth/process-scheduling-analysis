#include "process.hpp"

namespace dispatcher
{
    void interrupt(std::vector<process>::iterator& pit, int tq);
    void context_switch(std::vector<process>::iterator& pit, int tq);
    void save_state(std::vector<process>::iterator& pit, int ttl_p);
    void restore_state(std::vector<process>::iterator& pit);
}
