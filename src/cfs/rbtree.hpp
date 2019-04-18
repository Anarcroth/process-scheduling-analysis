#ifndef __RBTREE_H_INCLUDED__
#define __RBTREE_H_INCLUDED__

//#include "../process.hpp"
#include <stdio.h>

enum class col : unsigned short
{
    BLACK,
    RED
};

struct sched_entity
{
    int key;

    sched_entity *parent;
    sched_entity *left;
    sched_entity *right;

    col rb;
    bool isOnLeft() { return this == parent->left; }
    // returns pointer to sibling
    sched_entity *sibling() {
	// sibling null if no parent
	if (parent == NULL)
	    return NULL;

	if (this == parent->left)
	    return parent->right;
	return parent->left;
    }

    bool hasRedChild() {
	return (left != NULL and left->rb == col::RED) or
	    (right != NULL and right->rb == col::RED);
    }

    sched_entity(int k, sched_entity *p, sched_entity *l, sched_entity *r, col _rb) :
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

    void insert(int key);
    void show_tree(sched_entity *&node);

    sched_entity *root{};
    sched_entity *print_smallest(sched_entity *node);

    void delete_node(sched_entity *node);

private:
    void insert(sched_entity *&node, sched_entity *&parent, int key);
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

    sched_entity *replace(sched_entity *node);
    void fix_dubs_black(sched_entity *node);
};

#endif
