#include "process.hpp"

namespace dispatcher
{
    void interrupt();
    void context_switch(process& pr, int ttl);
    void save_state(process& pr, int ttl_p);
    void restore_state();
}
