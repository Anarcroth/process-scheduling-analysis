#include <iostream>
#include <algorithm>

#include "rbtree.hpp"

void rbtree::insert(int key)
{
    if (root != nullptr)
    	insert(root, root, key);
    else
    	root = new sched_entity(key, nullptr, nullptr, nullptr, col::BLACK);
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
    printf("\n%s%hu", "node is color ", node->rb);

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
	node = new sched_entity(key, parent, nullptr, nullptr, col::RED);
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
	root->rb = col::BLACK;
	return;
    }

    sched_entity *nnode = node;
    if (node->rb == col::RED && node->parent->rb == col::RED) {
	auto *grand_p = parent(node->parent);
	sched_entity *aunt;

	if (grand_p->left != node->parent)
	    aunt = grand_p->left;
	else
	    aunt = grand_p->right;

	if (!aunt || aunt->rb == col::BLACK)
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
    node->parent->parent->rb = col::RED;
    node->parent->parent->left->rb = col::BLACK;
    node->parent->parent->right->rb = col::BLACK;
    if (root->rb != col::BLACK)
	root->rb = col::BLACK;
    return node;
}

sched_entity *rbtree::color_flip_rev(sched_entity *root)
{
    root->rb = col::BLACK;
    if (root->left)
	root->left->rb = col::RED;
    if (root->right)
	root->right->rb = col::RED;
    return root;
}

sched_entity *rbtree::replace(sched_entity *node)
{
    if (node->left && node->right)
	return parent(node->right);
    if (!node->left && !node->right)
	return nullptr;
    if (node->left)
	return node->left;
    else
	return node->right;
}

void rbtree::delete_node(sched_entity *node)
{
    sched_entity *rnode = replace(node);

    bool dubblack = ((!rnode || rnode->rb == col::BLACK)
		    && (node->rb == col::BLACK));

    sched_entity *par = node->parent;

    if (!rnode) {
	if (node == root) {
	    root = nullptr;
	} else {
	    if (dubblack) {
		fix_dubs_black(node);
	    } else {
		if (node->sibling())
		    node->sibling()->rb = col::RED;
	    }

	    if (node == node->parent->left)
		par->left = nullptr;
	    else
		par->right = nullptr;
	}
	delete node;
	return;
    }

    if (node->left == nullptr || node->right == nullptr) {
	if (node == root) {
	    node->key = rnode->key;
	    node->left = node->right = nullptr;
	    delete rnode;
	} else {
	    if (node == node->parent->left) {
		par->left = rnode;
	    } else {
		par->right = rnode;
	    }
	    delete node;
	    rnode->parent = par;
	    if (dubblack)
		fix_dubs_black(rnode);
	    else
		rnode->rb = col::BLACK;
	}
	return;
    }

    std::swap(rnode->key, node->key);
    delete_node(rnode);
}

void rbtree::fix_dubs_black(sched_entity *node)
{
    if (node == root)
	return;

    sched_entity *sibling = node->sibling();
    sched_entity *parent = node->parent;
    if (!sibling) {
	fix_dubs_black(parent);
    } else {
	if (sibling->rb == col::RED) {
	    parent->rb = col::RED;
	    sibling->rb = col::BLACK;

	    if (sibling->isOnLeft())
		right_rot(parent);
	    else
		left_rot(parent);

	    fix_dubs_black(node);

	} else {
	    if (sibling->hasRedChild()) {
		if (sibling->left && sibling->left->rb == col::RED) {
		    if (sibling->isOnLeft()) {
			sibling->left->rb = sibling->rb;
			sibling->rb = parent->rb;
			right_rot(parent);
		    } else {
			sibling->left->rb = parent->rb;
			right_rot(sibling);
			left_rot(parent);
		    }
		} else {
		    if (sibling->isOnLeft()) {
			sibling->right->rb = parent->rb;
			left_rot(sibling);
			right_rot(parent);
		    } else {
			sibling->right->rb = sibling->rb;
			sibling->rb = parent->rb;
			left_rot(parent);
		    }
		}
		parent->rb = col::BLACK;
	    } else {
		sibling->rb = col::RED;
		if (parent->rb == col::BLACK)
		    fix_dubs_black(parent);
		else
		    parent->rb = col::BLACK;
	    }
	}
    }
}

sched_entity *rbtree::print_smallest(sched_entity *node)
{
    while (node->left)
	node = node->left;
    return node;
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
    //rbt.show_tree(rbt.root);
    auto *smallest = rbt.print_smallest(rbt.root);
    // printf("\n%s%d", "--------------------node smallest ", smallest->parent->key);
    rbt.delete_node(smallest);
    auto *s = rbt.print_smallest(rbt.root);
    printf("\n%s%d", "--------------------node smallest ", s->key);
    rbt.delete_node(s);
    auto *a = rbt.print_smallest(rbt.root);
    rbt.delete_node(a);
    rbt.show_tree(rbt.root);
    return 0;
}
