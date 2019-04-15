#include <iostream>

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
    if (node->parent)
	printf("\n%s%d", "node parent is ", node->parent->key);
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

	if (!aunt || aunt->rb == 0)
	    rotate(node, grand_parent);
	else
	    color_flip(node);

	rebalance(node->parent);
    }
}

void rbtree::rotate(sched_entity *&node, sched_entity *&grand_parent)
{
    if (grand_parent->right->left == node) {
	right_left_rot(node);
    } else if (grand_parent->right->right == node) {
        left_rot(grand_parent);
    } else if (grand_parent->left->right == node) {
	left_right_rot(node);
    } else if (grand_parent->left->left == node) {
	right_rot(grand_parent);
    }
}

void rbtree::right_rot(sched_entity *&root)
{
    //printf("\n===== right rotation");

    auto *oldgp = root->parent;
    auto *tmp = root->left;

    // printf("\n%s%d", "0 oldgp ", oldgp->key);
    // printf("\n%s%d", "0 root ", root->key);
    // printf("\n%s%d", "0 tmp ", tmp->key);

    /////
    if (tmp->right)
	root->left = tmp->right; // should be null
    else
	root->left = nullptr;
    tmp->right = root;
    // if (tmp->right)
    // 	printf("\n%s%d", "1 tmp->right ", tmp->right->key);
    root = tmp;
    oldgp->right = tmp;
    //printf("\n%s%d", "1 oldgp right ", oldgp->right->key);
    /////
    // if (root)
    // 	printf("\n%s%d", "2 root ", root->key);
    // if (root->right)
    // 	printf("\n%s%d", "2 root->right ", root->right->key);
    // if (root->left)
    // 	printf("\n%s%d", "2 root->left ", root->left->key);
    // if (tmp->right)
    // 	printf("\n%s%d", "2 tmp->right ", tmp->right->key);
    // if (tmp)
    // 	printf("\n%s%d", "2 tmp ", tmp->key);
    // if (oldgp->right)
    // 	printf("\n%s%d", "2 oldgp right right ", oldgp->right->right->key);
    // if (oldgp)
    // 	printf("\n%s%d", "2 oldgp ", oldgp->key);
    // if (tmp == oldgp->right && root == tmp)
    // 	printf("\n%s", "yes they are the same");

    // printf("\n===== oh yeah right rotation");
}

void rbtree::left_rot(sched_entity *&grand_parent)
{
    auto *oldgp = grand_parent->parent;
    auto *tmp = grand_parent->right;
    if (tmp->left)
	grand_parent->right = tmp->left;
    tmp->left = grand_parent;
    oldgp->left = tmp;

    printf("\n===== left rotation");
    printf("\n===== left rotation");
}

void rbtree::right_left_rot(sched_entity *&node)
{
    right_rot(node->parent);

    printf("\n===== after right rotation");
    if (node)
     	printf("\n%s%d", "node ", node->key);
    if (node->parent)
     	printf("\n%s%d", "node parent ", node->parent->key);
    // if (node->parent->right)
    // 	printf("\n%s%d", "node->parent->right ", node->parent->right->key);
    // if (node->parent->left)
    // 	printf("\n%s%d", "node->parent->left ", node->parent->left->key);
    printf("\n===== after right rotation");
    std::cin.get();
    left_rot(node->parent->parent);
    color_flip_rev(node->parent->parent);
}

void rbtree::left_right_rot(sched_entity *&node)
{
    left_rot(node->parent);
    right_rot(node->parent->parent);
    color_flip_rev(node->parent->parent);
}

void rbtree::color_flip(sched_entity *&node)
{
    node->parent->parent->rb = 1;
    node->parent->parent->left->rb = 0;
    node->parent->parent->right->rb = 0;
    if (root->rb != 0)
	root->rb = 0;
}

void rbtree::color_flip_rev(sched_entity *&root)
{
    root->rb = 0;
    if (root->left)
	root->left->rb = 1;
    if (root->right)
	root->right->rb = 1;
}

int main()
{
    rbtree rbt;
    rbt.insert(3);
    printf("\n%s%d", "Added successfully ", 3);
    rbt.insert(1);
    printf("\n%s%d", "Added successfully ", 1);
    rbt.insert(5);
    printf("\n%s%d", "Added successfully ", 5);
    rbt.insert(7);
    printf("\n%s%d", "Added successfully ", 7);
    rbt.insert(6);
    printf("\n%s%d", "Added successfully ", 6);
    //rbt.show_tree(rbt.root);
    //rbt.insert(8);
    //printf("\n%s%d", "Added successfully ", 8);
    //rbt.insert(9);
    //printf("\n%s%d", "Added successfully ", 9);
    //rbt.insert(10);
    //printf("\n%s%d", "Added successfully ", 10);
    //rbt.show_tree(rbt.root);
    return 0;
}
