#include <iostream>

#include "rbtree.hpp"

void rbtree::insert(int key)
{
    if (root != nullptr)
    	insert(root, root, key);
    else
    	root = new sched_entity(key, nullptr, nullptr, nullptr, 0);
}

sched_entity *rbtree::parent(sched_entity *root)
{
    return *&root->parent;
}

sched_entity *rbtree::sibling(sched_entity *root)
{
    auto *par = parent(root);
    if (par->left == root)
	return par->right;
    else
	return par->left;
}

void rbtree::show_tree(sched_entity *&node)
{
    printf("\n%s", "======");
    printf("\n%s%d", "node is ", node->key);
    printf("\n%s%d", "node is color ", node->rb);

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
    if (!node) {
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
    if (!node)
	return;

    if (root == node) {
	root->rb = 0;
	return;
    }

    sched_entity *nnode = node;
    if (node->rb == 1 && node->parent->rb == 1) {
	auto *grand_p = parent(node->parent);
	sched_entity *aunt;

	if (grand_p->left != node->parent)
	    aunt = grand_p->left;
	else
	    aunt = grand_p->right;

	if (!aunt || aunt->rb == 0)
	    nnode = rotate(node, grand_p);
	else
	    nnode = color_flip(node);
    }

    // if there is no parent to the root
    if (!nnode->parent)
	root = nnode;

    rebalance(nnode->parent);
}

sched_entity *rbtree::rotate(sched_entity *&node, sched_entity *&grand_parent)
{
    if (grand_parent->right->left == node) {
	return right_left_rot(node);
    } else if (grand_parent->right->right == node) {
        auto *lr = left_rot(grand_parent);
	return color_flip_rev(lr);
    } else if (grand_parent->left->right == node) {
	return left_right_rot(node);
    } else {// if (grand_parent->left->left == node)
	auto *rr = right_rot(grand_parent);
	return color_flip_rev(rr);
    }
}

sched_entity *rbtree::right_rot(sched_entity *&root)
{
    auto *tmp = root->left;
    auto *grand_p = parent(root);
    root->left = tmp->right;
    tmp->right = root;
    root->parent = tmp;
    if (root->left)
	root->left->parent = root;
    if (grand_p) {
    	if (root == grand_p->left)
    	    grand_p->left = tmp;
    	else if (root == grand_p->right)
    	    grand_p->right = tmp;
    }
    tmp->parent = grand_p;
    return tmp;
}

sched_entity *rbtree::left_rot(sched_entity *&root)
{
    auto *tmp = root->right;
    auto *grand_p = parent(root);
    root->right = tmp->left;
    tmp->left = root;
    root->parent = tmp;
    if (root->right)
	root->right->parent = root;
    if (grand_p) {
	if (root == grand_p->left)
	    grand_p->left = tmp;
	else if (root == grand_p->right)
	    grand_p->right = tmp;
    }
    tmp->parent = grand_p;
    return tmp;
}

sched_entity *rbtree::right_left_rot(sched_entity *&node)
{
    auto *rr_root = right_rot(node->parent);
    auto *lr_root = left_rot(rr_root->parent);
    return color_flip_rev(lr_root);
}

sched_entity *rbtree::left_right_rot(sched_entity *&node)
{
    auto *lr_root = left_rot(node->parent);
    auto *rr_root = right_rot(lr_root->parent);
    return color_flip_rev(rr_root);
}

sched_entity *rbtree::color_flip(sched_entity *node)
{
    node->parent->parent->rb = 1;
    node->parent->parent->left->rb = 0;
    node->parent->parent->right->rb = 0;
    if (root->rb != 0)
	root->rb = 0;
    return node;
}

sched_entity *rbtree::color_flip_rev(sched_entity *root)
{
    root->rb = 0;
    if (root->left)
	root->left->rb = 1;
    if (root->right)
	root->right->rb = 1;
    return root;
}

void rbtree::replace_node(sched_entity *root, sched_entity *child)
{
    child->parent = root->parent;
    if (root == root->parent->left)
        root->parent->left = child;
    else
        root->parent->right = child;
}

void rbtree::delete_one_child(sched_entity *root)
{
    /*
     * Precondition: n has at most one non-leaf child.
     */
    sched_entity* child = (root->right) ? root->left : root->right;

    replace_node(root, child);
    if (root->rb == 0) {
	if (child->rb == 1)
	    child->rb = 0;
	else
	    del1(child);
    }
    //free(n);
}

void rbtree::del1(sched_entity *root)
{
    if (root->parent)
	del2(root);
}

void rbtree::del2(sched_entity *root)
{
    auto* sib = sibling(root);

    if (sib->rb == 1) {
	root->parent->rb = 1;
	sib->rb = 0;
	if (root == root->parent->left)
	    left_rot(root->parent);
	else
	    right_rot(root->parent);
    }
    del3(root);
}

void rbtree::del3(sched_entity *root)
{
    auto* sib = sibling(root);

    if ((root->parent->rb == 0) &&
	(sib->rb == 0) &&
	(sib->left->rb == 0) &&
	(sib->right->rb == 0)) {
	sib->rb = 1;
	del1(root->parent);
    } else {
	del4(root);
    }
}

void rbtree::del4(sched_entity *root)
{
    auto* sib = sibling(root);

    if ((root->parent->rb == 1) &&
	(sib->rb == 0) &&
	(sib->left->rb == 0) &&
	(sib->right->rb == 0)) {
	sib->rb = 1;
	root->parent->rb = 0;
    } else {
	del5(root);
    }
}

void rbtree::del5(sched_entity *root)
{
    auto* sib = sibling(root);

    if (sib->rb == 0) {
	if ((root == root->parent->left) &&
	    (sib->right->rb == 0) &&
	    (sib->left->rb == 1)) {
	    sib->rb = 1;
	    sib->left->rb = 0;
	    right_rot(sib);
	} else if ((root == root->parent->right) &&
		   (sib->left->rb == 0) &&
		   (sib->right->rb == 1)) {
	    sib->rb = 1;
	    sib->right->rb = 0;
	    left_rot(sib);
	}
    }
    del6(root);
}

void rbtree::del6(sched_entity *root)
{
    auto* sib = sibling(root);

    sib->rb = root->parent->rb;
    root->parent->rb = 0;

    if (root == root->parent->left) {
	sib->right->rb = 0;
	left_rot(root->parent);
    } else {
	sib->left->rb = 0;
	right_rot(root->parent);
    }
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
    rbt.insert(8);
    printf("\n%s%d", "Added successfully ", 8);
    rbt.insert(9);
    printf("\n%s%d", "Added successfully ", 9);
    rbt.insert(10);
    printf("\n%s%d", "Added successfully ", 10);
    rbt.show_tree(rbt.root);
    return 0;
}
