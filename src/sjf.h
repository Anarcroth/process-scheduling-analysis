#ifndef __SJF_H_INCLUDED__
#define __SJF_H_INCLUDED__

#include "alg.h"

class sjf : public alg
{
public:
    sjf(std::vector<std::unique_ptr<process>> prs);

    virtual void work() override;

private:
    void exec();
};

#endif
