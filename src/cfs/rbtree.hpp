#ifndef __RBTREE_H_INCLUDED__
#define __RBTREE_H_INCLUDED__

#include "../process.hpp"

struct sched_entity
{
    process key;

    sched_entity *parent;
    sched_entity *left;
    sched_entity *right;

    int rb;

    sched_entity(process k, sched_entity *p, sched_entity *l, sched_entity *r, int _rb) :
	key(k),
	parent(p),
	left(l),
	right(r),
	rb(_rb) {}
};

class rbtree
{
public:
    rbtree() = default;
    ~rbtree();

    void insert(sched_entity *&root, process &key);
    process get_process();
private:
    void right_rotation();
    void left_rotation();

    sched_entity *root{};
};

#endif
