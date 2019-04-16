#ifndef __RBTREE_H_INCLUDED__
#define __RBTREE_H_INCLUDED__

//#include "../process.hpp"
#include <stdio.h>
struct sched_entity
{
    int key;

    sched_entity *parent;
    sched_entity *left;
    sched_entity *right;

    int rb; // black 0, red 1

    sched_entity(int k, sched_entity *p, sched_entity *l, sched_entity *r, int _rb) :
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
    //~rbtree();

    void insert(int key);
    //process get_process();
    void show_tree(sched_entity *&node);

    sched_entity *root{};
private:
    void insert(sched_entity *&node, sched_entity *&parent, int key);
    void rebalance(sched_entity *&node);

    void rotate(sched_entity *&node, sched_entity *&grand_parent);
    void right_rot(sched_entity *&root);
    void left_rot(sched_entity *&root);
    void right_left_rot(sched_entity *&node);
    void left_right_rot(sched_entity *&node);

    void color_flip(sched_entity *&node);
    void color_flip_rev(sched_entity *&root);
};

#endif
