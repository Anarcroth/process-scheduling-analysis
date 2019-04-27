#include <utility>
#include <algorithm>
#include <string>

#include "rbtree.hpp"

void rbtree::insert(process key)
{
    if (root != nullptr)
    	insert(root, root, key);
    else {
    	root = new sched_entity(key, nullptr, nullptr, nullptr, col::BLACK);
    }
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

bool rbtree::is_left(sched_entity *node)
{
    return node == node->parent->left;
}

bool rbtree::has_red_child(sched_entity *node)
{
    return (node->left && node->left->rb == col::RED) ||
	(node->right && node->right->rb == col::RED);
}

void rbtree::insert(sched_entity *&node, sched_entity *&parent, process key)
{
    if (!node) {
	node = new sched_entity(key, parent, nullptr, nullptr, col::RED);
	rebalance(node);
	rq.push_back(key);
    } else if (key.get_vruntime() <= node->key.get_vruntime()) {
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
    if (grand_parent->right) {
	if (grand_parent->right->left == node) {
	    return right_left_rot(node);
	} else { //if (grand_parent->right->right == node) {
	    auto *lr = left_rot(grand_parent);
	    return color_flip_rev(lr);
	}
    } else {
	if (grand_parent->left->right == node) {
	    return left_right_rot(node);
	} else { // if (grand_parent->left->left == node)
	    auto *rr = right_rot(grand_parent);
	    return color_flip_rev(rr);
	}
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
    for (auto pit = rq.begin(); pit != rq.end(); ++pit) {
	if (node->key.get_id() == pit->get_id()) {
	    rq.erase(pit);
	    break;
	}
    }
    __delete_node(node);
    root = fix_root(root);
}

void rbtree::__delete_node(sched_entity *node)
{
    sched_entity *rnode = replace(node);

    bool dubblack = ((!rnode || rnode->rb == col::BLACK)
		    && (node->rb == col::BLACK));

    sched_entity *par = parent(node);

    if (!rnode) {
	if (node == root) {
	    root = nullptr;
	} else {
	    if (dubblack) {
		fix_dubs_black(node);
	    } else {
		if (sibling(node))
		    sibling(node)->rb = col::RED;
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

    sched_entity *sib = sibling(node);
    sched_entity *par = parent(node);
    if (!sib) {
	fix_dubs_black(par);
    } else {
	if (sib->rb == col::RED) {
	    par->rb = col::RED;
	    sib->rb = col::BLACK;

	    if (is_left(sib))
		right_rot(par);
	    else
		left_rot(par);

	    fix_dubs_black(node);

	} else {
	    if (has_red_child(sib)) {
		if (sib->left && sib->left->rb == col::RED) {
		    if (is_left(sib)) {
			sib->left->rb = sib->rb;
			sib->rb = par->rb;
			right_rot(par);
		    } else {
			sib->left->rb = par->rb;
			right_rot(sib);
			left_rot(par);
		    }
		} else {
		    if (is_left(sib)) {
			sib->right->rb = par->rb;
			left_rot(sib);
			right_rot(par);
		    } else {
			sib->right->rb = sib->rb;
			sib->rb = par->rb;
			left_rot(par);
		    }
		}
		par->rb = col::BLACK;
	    } else {
		sib->rb = col::RED;
		if (par->rb == col::BLACK)
		    fix_dubs_black(par);
		else
		    par->rb = col::BLACK;
	    }
	}
    }
}

sched_entity *rbtree::get_smallest(sched_entity *node)
{
    while (node->left)
	node = node->left;
    return node;
}

sched_entity *rbtree::fix_root(sched_entity *node)
{
    if (!node)
	return nullptr;
    while (node->parent)
	node = node->parent;
    return node;
}

bool rbtree::empty()
{
    return (root) ? false : true;
}

void rbtree::fix_internal_repr()
{
    std::sort(rq.begin(),
	      rq.end(),
	      [] (const process a, const process b) {
		  return a.get_vruntime() < b.get_vruntime();
	      });
}
