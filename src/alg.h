#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

class alg
{
public:
    alg();

    int get_awt() const;

    virtual void work();
    virtual void exec();

private:
    int average_wait_time;
};

#endif
