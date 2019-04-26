#ifndef __RBTREE_H_INCLUDED__
#define __RBTREE_H_INCLUDED__

#include <stdio.h>
#include <vector>

#include "../process.hpp"

enum class col : unsigned short
{
    BLACK,
    RED
};

struct sched_entity
{
    process key;

    sched_entity *parent;
    sched_entity *left;
    sched_entity *right;

    col rb;

    sched_entity(process k, sched_entity *p, sched_entity *l, sched_entity *r, col _rb) :
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

    void insert(process key);
    void delete_node(sched_entity *node);

    sched_entity *get_smallest(sched_entity *node);

    bool empty();

    sched_entity *root{};

    std::vector<process> wq;
    std::vector<process> rq;
    std::vector<process> dq;

private:
    void insert(sched_entity *&node, sched_entity *&parent, process key);
    void rebalance(sched_entity *&node);

    sched_entity *rotate(sched_entity *&node, sched_entity *&grand_parent);
    sched_entity *right_rot(sched_entity *&root);
    sched_entity *left_rot(sched_entity *&root);
    sched_entity *right_left_rot(sched_entity *&node);
    sched_entity *left_right_rot(sched_entity *&node);

    sched_entity *color_flip(sched_entity *node);
    sched_entity *color_flip_rev(sched_entity *root);

    sched_entity *parent(sched_entity *root);
    sched_entity *sibling(sched_entity *root);
    bool is_left(sched_entity *node);
    bool has_red_child(sched_entity *node);

    void __delete_node(sched_entity *node);

    sched_entity *replace(sched_entity *node);
    void fix_dubs_black(sched_entity *node);
    sched_entity *fix_root(sched_entity *node);
};

#endif
