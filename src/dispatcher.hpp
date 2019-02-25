#include "process.hpp"

namespace dispatcher
{
    void interrupt();
    std::vector<process>::iterator context_switch(std::vector<process>::iterator& pit, int ttl);
    void save_state(std::vector<process>::iterator& pit, int ttl_p);
    std::vector<process>::iterator restore_state(std::vector<process>::iterator& pit);
}
