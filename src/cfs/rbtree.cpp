#include "rbtree.hpp"

void rbtree::insert(int key)
{
    if (root != nullptr)
    	insert(root, root, key);
    else
    	root = new sched_entity(key, nullptr, nullptr, nullptr, 0);
}

void rbtree::show_tree(sched_entity *&node)
{
    printf("\n%s%d", "node is ", node->key);
    if (node->left) {
	printf("\n%s%d", "node left is ", node->left->key);
	show_tree(node->left);
    }
    if (node->right) {
	printf("\n%s%d", "node right is ", node->right->key);
	show_tree(node->right);
    }
}

void rbtree::insert(sched_entity *&node, sched_entity *&parent, int key)
{
    if (node == nullptr) {
	node = new sched_entity(key, parent, nullptr, nullptr, 1);
	rebalance(node);
    } else if (key <= node->key) {
	insert(node->left, node, key);
    } else {
	insert(node->right, node, key);
    }
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
}

void rbtree::right_rot(sched_entity *&node, sched_entity *&grand_parent)
{
    auto *oldgp = grand_parent->parent;
    auto *tmp = grand_parent->left;
    grand_parent->left = tmp->right;
    tmp->right = grand_parent;
    oldgp = tmp;

    // color flip
    node->parent->rb = 0;
    node->parent->right->rb = 1;
    node->rb = 1;
}

void rbtree::left_rot(sched_entity *&node, sched_entity *&grand_parent)
{
    auto *oldgp = grand_parent->parent;
    auto *tmp = grand_parent->right;
    grand_parent->right = tmp->left;
    tmp->left = grand_parent;
    oldgp->right = tmp;

    // color flip
    node->parent->rb = 0;
    node->parent->left->rb = 1;
    node->rb = 1;
}

void rbtree::right_left_rot(sched_entity *&node)
{
    right_rot(node, node->parent->parent);
    left_rot(node, node->parent->parent);
}

void rbtree::left_right_rot(sched_entity *&node)
{
    left_rot(node, node->parent->parent);
    right_rot(node, node->parent->parent);
}

void rbtree::color_flip(sched_entity *&node)
{
    node->parent->parent->rb = 1;
    node->parent->parent->left->rb = 0;
    node->parent->parent->right->rb = 0;
    if (root->rb != 0) // Turn to black.
	root->rb = 0;
}

int main()
{
    rbtree rbt;
    rbt.insert(3);
    printf("\n%s%d", "Added successfully ", 3);
    rbt.insert(1);
    printf("\n%s%d", "Added successfully ", 1);
    rbt.insert(6);
    printf("\n%s%d", "Added successfully ", 6);
    rbt.insert(7);
    printf("\n%s%d", "Added successfully ", 7);
    rbt.insert(8);
    printf("\n%s%d", "Added successfully ", 8);
    rbt.show_tree(rbt.root);
    return 0;
}
