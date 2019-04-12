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
    while (node->parent && node->parent->rb == 1) {

	sched_entity *aunt;
	auto *grand_parent = node->parent->parent;

	if (grand_parent->left != node->parent)
	    aunt = grand_parent->left;
	else
	    aunt = grand_parent->right;

	if (!aunt || aunt->rb == 0) { // if aunt doesn't exist or is black
	    rotate(node);
	} else { // the aunt is red
	    color_flip(node);
	}
	// rebalance(node);
    }
}

void rbtree::rotate(sched_entity *&node)
{
    //if (node->parent)
}

void rbtree::color_flip(sched_entity *&node)
{

}
