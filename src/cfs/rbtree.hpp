#ifndef __RBTREE_H_INCLUDED__
#define __RBTREE_H_INCLUDED__

#include "../process.hpp"

struct sched_entity
{
    process key;

    sched_entity *parent;
    sched_entity *left;
    sched_entity *right;

    int rb; // black 0, red 1

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

    void insert(process &key);
    process get_process();

private:
    void insert(sched_entity *&node, process &key);
    void right_rot(sched_entity *&node);
    void left_rot(sched_entity *&node);
    void rotate(sched_entity *&node);
    void color_flip(sched_entity *&node);
    void rebalance(sched_entity *&node);

    sched_entity *root{};
};

#endif
