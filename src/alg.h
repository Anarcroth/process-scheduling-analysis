#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

class alg
{
public:
    alg();

    int get_awt() const;

    void exec();

    void fcfs();
    void sjf();
    void round_rob();

private:
    int average_wait_time;
};

#endif
