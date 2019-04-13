#include "rbtree.hpp"

void rbtree::insert(process &key)
{
    if (root != nullptr)
	insert(root, root, key);
    else
	root = new sched_entity(key, nullptr, nullptr, nullptr, 0);
}

void rbtree::insert(sched_entity *&node, sched_entity *&parent, process &key)
{
    if (node == nullptr) {
	node = new sched_entity(key, parent, nullptr, nullptr, 1);
    } else if (key.get_ttl() <= node->key.get_ttl()) {
	insert(node->left, node, key);
    } else {
	insert(node->right, node, key);
    }
    rebalance(node);
}

void rbtree::rebalance(sched_entity *&node)
{
    if (root == node) {
	root->rb = 0;
	return;
    }
    if (node->rb == 1 && node->parent->rb == 1) {

	sched_entity *aunt;
	auto *grand_parent = node->parent->parent;

	if (grand_parent->left != node->parent)
	    aunt = grand_parent->left;
	else
	    aunt = grand_parent->right;

	if (!aunt || aunt->rb == 0) { // if aunt doesn't exist or is black
	    rotate(node, grand_parent);
	} else { // the aunt is red
	    color_flip(node);
	}
	rebalance(node->parent);
    }
}

void rbtree::rotate(sched_entity *&node, sched_entity *&grand_parent)
{
    if (grand_parent->right->left == node)
	right_left_rot(node);
    else if (grand_parent->right->right == node)
	left_rot(node, grand_parent);
    else if (grand_parent->left->right == node)
	left_right_rot(node);
    else if (grand_parent->left->left == node)
	right_rot(node, grand_parent);

    // int left_right_rot = 0;
    // if (node->parent->right == node) { // LR rotate
    // 	node = node->parent;
    // 	left_rot(node);
    // 	left_right_rot = 0;
    // } else { // RL rotate
    // 	node = node->parent;
    // 	right_rot(node);
    // 	left_right_rot = 1;
    // }
    // node->parent->rb = 0;
    // node->parent->parent->rb = 1;
    // if (left_right_rot == 1)
    // 	left_rot(node);
    // else
    // 	right_rot(node);
}

void rbtree::right_rot(sched_entity *&node, sched_entity *&grand_parent)
{
    auto *tmp = node->parent;
    node->parent = grand_parent;
    grand_parent = tmp->right;

    // color flip
    node->parent->rb = 0;
    node->rb = 1;
    node->parent->right->rb = 1;
}

void rbtree::left_rot(sched_entity *&node, sched_entity *&grand_parent)
{
    auto *tmp = node->parent;
    node->parent = grand_parent;
    grand_parent = tmp->left;

    // color flip
    node->parent->rb = 0;
    node->rb = 1;
    node->parent->left->rb = 1;
}

void rbtree::color_flip(sched_entity *&node)
{
    node->parent->parent->rb = 1;
    node->parent->parent->left = 0;
    node->parent->parent->right = 0;
    if (root->rb != 0)
	root->rb = 0;
}
