#ifndef __SJF_H_INCLUDED__
#define __SJF_H_INCLUDED__

#include "alg.h"

class sjf : public alg
{
public:
    sjf(std::vector<process*> prs);
    ~sjf();

    virtual void work() override;

private:
    void exec(std::vector<process*> &prs_sorted_by_ttl);
};

#endif
