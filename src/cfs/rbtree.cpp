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
    balance();
}

void rbtree::rebalance(sched_entity *&node)
{
    if (root == node) {
	root->rb = 0;
	return;
    }
    while (t->parent && t->parent->rb == 1) {

	auto *aunt;
	auto *grand_parent = t->parent->parent;

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
