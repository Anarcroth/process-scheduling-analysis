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

void rbtree::replace_node(sched_entity *root, sched_entity *child)
{
    printf("\n%s%d", "will delete ", root->key);
    child->parent = parent(root);//->parent;
    std::cin.get();
    if (root == root->parent->left)
        root->parent->left = child;
    else
        root->parent->right = child;
}

void rbtree::delete_one_child(sched_entity *root)
{
    printf("\n%s%d", "will delete ", root->key);
    sched_entity* child = (root->right) ? root->left : root->right;
    if (child)
	printf("\n%s%d", "the child is ", child->key);
    replace_node(root, child);
    if (root->rb == col::BLACK) {
	if (child->rb == col::RED)
	    child->rb = col::BLACK;
	else
	    del1(child);
    }
    free(root);
}

void rbtree::del1(sched_entity *root)
{
    if (root->parent)
	del2(root);
}

void rbtree::del2(sched_entity *root)
{
    auto* sib = sibling(root);

    if (sib->rb == col::RED) {
	root->parent->rb = col::RED;
	sib->rb = col::BLACK;
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

    if ((root->parent->rb == col::BLACK) &&
	(sib->rb == col::BLACK) &&
	(sib->left->rb == col::BLACK) &&
	(sib->right->rb == col::BLACK)) {
	sib->rb = col::RED;
	del1(root->parent);
    } else {
	del4(root);
    }
}

void rbtree::del4(sched_entity *root)
{
    auto* sib = sibling(root);

    if ((root->parent->rb == col::RED) &&
	(sib->rb == col::BLACK) &&
	(sib->left->rb == col::BLACK) &&
	(sib->right->rb == col::BLACK)) {
	sib->rb = col::RED;
	root->parent->rb = col::BLACK;
    } else {
	del5(root);
    }
}

void rbtree::del5(sched_entity *root)
{
    auto* sib = sibling(root);

    if (sib->rb == col::BLACK) {
	if ((root == root->parent->left) &&
	    (sib->right->rb == col::BLACK) &&
	    (sib->left->rb == col::RED)) {
	    sib->rb = col::RED;
	    sib->left->rb = col::BLACK;
	    right_rot(sib);
	} else if ((root == root->parent->right) &&
		   (sib->left->rb == col::BLACK) &&
		   (sib->right->rb == col::RED)) {
	    sib->rb = col::RED;
	    sib->right->rb = col::BLACK;
	    left_rot(sib);
	}
    }
    del6(root);
}

void rbtree::del6(sched_entity *root)
{
    auto* sib = sibling(root);

    sib->rb = root->parent->rb;
    root->parent->rb = col::BLACK;

    if (root == root->parent->left) {
	sib->right->rb = col::BLACK;
	left_rot(root->parent);
    } else {
	sib->left->rb = col::BLACK;
	right_rot(root->parent);
    }
}

// find node that replaces a deleted node in BST
sched_entity *rbtree::BSTreplace(sched_entity *x) {
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
	return parent(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
	return NULL;

    // when single child
    if (x->left != NULL)
	return x->left;
    else
	return x->right;
}

  // deletes the given node
void rbtree::deleteNode(sched_entity *v) {
    sched_entity *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == NULL or u->rb == col::BLACK) and (v->rb == col::BLACK));
    sched_entity *parent = v->parent;

    if (u == NULL) {
	// u is NULL therefore v is leaf
	if (v == root) {
	    // v is root, making root null
	    root = NULL;
	} else {
	    if (uvBlack) {
		// u and v both black
		// v is leaf, fix double black at v
		fixDoubleBlack(v);
	    } else {
		// u or v is red
		if (v->sibling() != NULL)
		    // sibling is not null, make it red"
		    v->sibling()->rb = col::RED;
	    }

	    // delete v from the tree
	    if (v == v->parent->left) {
		parent->left = NULL;
	    } else {
		parent->right = NULL;
	    }
	}
	delete v;
	return;
    }

    if (v->left == NULL or v->right == NULL) {
	// v has 1 child
	if (v == root) {
	    // v is root, assign the value of u to v, and delete u
	    v->key = u->key;
	    v->left = v->right = NULL;
	    delete u;
	} else {
	    // Detach v from tree and move u up
	    if (v == v->parent->left) {
		parent->left = u;
	    } else {
		parent->right = u;
	    }
	    delete v;
	    u->parent = parent;
	    if (uvBlack) {
		// u and v both black, fix double black at u
		fixDoubleBlack(u);
	    } else {
		// u or v red, rb u black
		u->rb = col::BLACK;
	    }
	}
	return;
    }

    // v has 2 children, swap values with successor and recurse
    std::swap(u->key, v->key);
    deleteNode(u);
}

void rbtree::fixDoubleBlack(sched_entity *x) {
    if (x == root)
	return;

    sched_entity *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
	// No sibiling, double black pushed up
	fixDoubleBlack(parent);
    } else {
	if (sibling->rb == col::RED) {
	    // Sibling red
	    parent->rb = col::RED;
	    sibling->rb = col::BLACK;
	    if (sibling->isOnLeft()) {
		// left case
		right_rot(parent);
	    } else {
		// right case
		left_rot(parent);
	    }
	    fixDoubleBlack(x);
	} else {
	    // Sibling black
	    if (sibling->hasRedChild()) {
		// at least 1 red children
		if (sibling->left != NULL and sibling->left->rb == col::RED) {
		    if (sibling->isOnLeft()) {
			// left left
			sibling->left->rb = sibling->rb;
			sibling->rb = parent->rb;
			right_rot(parent);
		    } else {
			// right left
			sibling->left->rb = parent->rb;
			right_rot(sibling);
			left_rot(parent);
		    }
		} else {
		    if (sibling->isOnLeft()) {
			// left right
			sibling->right->rb = parent->rb;
			left_rot(sibling);
			right_rot(parent);
		    } else {
			// right right
			sibling->right->rb = sibling->rb;
			sibling->rb = parent->rb;
			left_rot(parent);
		    }
		}
		parent->rb = col::BLACK;
	    } else {
		// 2 black children
		sibling->rb = col::RED;
		if (parent->rb == col::BLACK)
		    fixDoubleBlack(parent);
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
    rbt.deleteNode(smallest);
    auto *s = rbt.print_smallest(rbt.root);
    printf("\n%s%d", "--------------------node smallest ", s->key);
    rbt.deleteNode(s);
    auto *a = rbt.print_smallest(rbt.root);
    rbt.deleteNode(a);
    rbt.show_tree(rbt.root);
    return 0;
}
