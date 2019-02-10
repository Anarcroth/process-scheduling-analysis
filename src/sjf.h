#ifndef __SJF_H_INCLUDED__
#define __SJF_H_INCLUDED__

#include "alg.h"

class sjf : public alg
{
public:
    sjf();

    virtual void work();
    virtual void exec();
};

#endif
