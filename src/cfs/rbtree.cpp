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

void rbtree::balance(sched_entity *&node)
{
    if (root == node) {
	root->rb = 0;
	return;
    }

}
