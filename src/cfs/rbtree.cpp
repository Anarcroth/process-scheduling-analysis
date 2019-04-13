#include "rbtree.hpp"

void rbtree::insert(int key)
{
    printf("\n%s%d", "first insert adding ", key);
    if (root != nullptr)
    	insert(root, root, key);
    else
    	root = new sched_entity(key, nullptr, nullptr, nullptr, 0);
    printf("\n%s%d", "the root is ", root->key);
    if (root->left)
	printf("\n%s%d", "the root left is ", root->left->key);
    if (root->right)
	printf("\n%s%d", "the root right is ", root->right->key);
    printf("\n%s", "next number please");
}

void rbtree::insert(sched_entity *&node, sched_entity *&parent, int key)
{
    if (node == nullptr) {
	printf("\n creating a new node");
	node = new sched_entity(key, parent, nullptr, nullptr, 1);
	printf("\n%s%d", "the node is ", node->key);
	printf("\n%s%d", "the node parent is ", node->parent->key);
	printf("\n%s%d", "the node color is ", node->rb);
	printf("\n%s%d", "the node parent color is ", node->parent->rb);
	rebalance(node);
    } else if (key <= node->key) {
	printf("\n%s%d", "second insert adding to the left ", key);
	insert(node->left, node, key);
    } else {
	printf("\n%s%d", "second insert adding to the right ", key);
	insert(node->right, node, key);
    }
}

void rbtree::rebalance(sched_entity *&node)
{
    printf("\n%s%d", "rebalancing ", node->key);
    if (root == node) {
	root->rb = 0;
	return;
    }
    printf("\n%s", "root is not equal to node");
    if (node->rb == 1 && node->parent->rb == 1) {
	printf("\n%s", "rebalancing because both are red");
	sched_entity *aunt;
	auto *grand_parent = node->parent->parent;
	if (grand_parent->left != node->parent)
	    aunt = grand_parent->left;
	else
	    aunt = grand_parent->right;

	if (!aunt || aunt->rb == 0) { // if aunt doesn't exist or is black
	    printf("\n rotating the nodes");
	    rotate(node, grand_parent);
	} else { // the aunt is red
	    printf("\n color flipping the nodes");
	    color_flip(node);
	}
	rebalance(node->parent);
    }
    printf("\nend of rebalancing");
}

void rbtree::rotate(sched_entity *&node, sched_entity *&grand_parent)
{
    if (grand_parent->right->left == node) {
	printf("\n doing a right left rotate");
	right_left_rot(node);
    }
    else if (grand_parent->right->right == node) {
	printf("\n doing a left rotate");
	left_rot(node, grand_parent);
    }
    else if (grand_parent->left->right == node) {
	printf("\n doing a left right rotate");
	left_right_rot(node);
    }
    else if (grand_parent->left->left == node) {
	printf("\n doing a right rotate");
	right_rot(node, grand_parent);
    }

    // int left_right_rot = 0;
    // if (node->parent->right == node) { // LR rotate
    // 	node = node->parent;
    // 	left_rot(node);
    // 	left_right_rot = 0;
    // } else { // RL rotate
    // 	node = node->parent;
    // 	right_rot(node);
    // 	left_right_rot = 1;
    // }
    // node->parent->rb = 0;
    // node->parent->parent->rb = 1;
    // if (left_right_rot == 1)
    // 	left_rot(node);
    // else
    // 	right_rot(node);
}

void rbtree::right_rot(sched_entity *&node, sched_entity *&grand_parent)
{
    auto *tmp = grand_parent->left;
    grand_parent->left = tmp->right;
    tmp->right = grand_parent;
    grand_parent = tmp;

    // color flip
    node->parent->rb = 0;
    node->parent->right->rb = 1;
    node->rb = 1;
}

void rbtree::left_rot(sched_entity *&node, sched_entity *&grand_parent)
{
    printf("\n==============================left rot");
    printf("\n%s%d", "1 the node is ", node->key);
    printf("\n%s%d", "1 the node parent is ", node->parent->key);
    printf("\n%s%d", "1 the grand parent is ", grand_parent->key);
    auto *tmp = grand_parent->right;
    grand_parent->right = tmp->left;
    tmp->left = grand_parent;
    grand_parent = tmp;
    printf("\n%s%d", "2 the node is ", node->key);
    printf("\n%s%d", "2 the node parent is ", node->parent->key);
    printf("\n%s%d", "2 the node parent left is ", node->parent->left->key);
    printf("\n%s%d", "2 the node parent right is ", node->parent->right->key);
    printf("\n%s%d", "2 the grand parent is ", grand_parent->key);
    printf("\n%s%d", "2 the grand parent parent is ", grand_parent->parent->key);

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
    printf("\n this is the color flip");
    node->parent->parent->rb = 1;
    node->parent->parent->left->rb = 0;
    node->parent->parent->right->rb = 0;
    printf("\n%s%d", "node is ", node->key);
    printf("\n%s%d", "node parent is ", node->parent->key);
    printf("\n%s%d", "node grand parent is ", node->parent->parent->key);
    if (root->rb != 0)
	root->rb = 0;
    printf("\n%s%d", "the root is ", root->key);
    if (root == node->parent->parent)
	printf("\n%s", "they are the same");
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
    return 0;
}
