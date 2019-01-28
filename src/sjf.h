#ifndef __SJF_H_INCLUDED__
#define __SJF_H_INCLUDED__

#include "alg.h"

class sjf : public alg
{
public:
    sjf();
    ~sjf();

    virtual int get_awt() override;
    virtual void work(std::vector<process*> &processes) override;

private:
};

#endif
