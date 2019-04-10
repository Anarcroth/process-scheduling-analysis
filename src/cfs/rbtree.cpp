#include "rbtree.hpp"

void rbtree::insert(sched_entity *&root, process &key)
{
    if (root == nullptr) {
	root = new sched_entity(key, nullptr, nullptr, nullptr, 1);
    } else {
	if (key.get_ttl() < root->key.get_ttl())
	    insert(root->left, key);
    }


}
