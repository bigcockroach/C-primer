#include "RB_Tree.h"

void RB_Tree::left_rotate(RB_Node* x) {
	RB_Node* y = x->right;
	x->right = y->left;
	if (y->left != nullptr)
		y->left->p = x;
	y->p = x->p;
	if (x->p == nullptr)
		root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void RB_Tree::right_rotate(RB_Node* y) {
	RB_Node* x = y->left;
	y->left = x->right;
	if (x->right != nullptr)
		x->right->p = y;
	x->p = y->p;
	if (y->p == nullptr)
		root = x;
	else if (y = y->p->left)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

void RB_Tree::RB_INSERT(RB_Node* z) {
	RB_Node* x = root;
	RB_Node* y = nullptr;
	while (x != nullptr) {
		y = x;
		if (z->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	z->p = y;
	if (y == nullptr)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->right = nullptr;
	z->left = nullptr;
	z->color = 'R';
	RB_INSERT_FIXUP(z);
}

void RB_Tree::RB_INSERT_FIXUP(RB_Node* z) {
	while (z->p->color == 'R') {
		if (z->p == z->p->p->left) {
			RB_Node* y = z->p->p->right;
			if (y->color == 'R') {
				y->color = 'B';
				z->p->color = 'R';
				z = z->p->p;
			}
			else if (z == z->p->right) {
				z = z->p;
				left_rotate(z);
			}
			z->p->p->color = 'R';
			z->p->color = 'B';
			right_rotate(z->p->p);
		}
		else {
			RB_Node* y = z->p->p->left;
			if (y->color == 'R') {
				y->color = 'B';
				z->p->color = 'R';
				z = z->p->p;
			}
			else if (z == z->p->left) {
				z = z->p;
				right_rotate(z);
			}
			z->p->p->color = 'R';
			z->p->color = 'B';
			left_rotate(z->p->p);
		}
	}
	root->color = 'B';
}

void RB_Tree::RB_TRANSPLANT(RB_Node* u, RB_Node* v) {
	if (u->p == nullptr)
		root = v;
	else if (u = u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if (v != nullptr)
		v->p = u->p;
}

RB_Node* RB_Tree::TREE_MINIMUM(RB_Node* node) {
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}

void RB_Tree::RB_DELETE(RB_Node* z) {
	RB_Node* y = z;
	RB_Node* x = nullptr;
	char y_original_color = y->color;
	if (z->left == nullptr) {
		x = z->right;
		RB_TRANSPLANT(z, z->right);
	}
	else if (z->right == nullptr) {
		x = z->left;
		RB_TRANSPLANT(z, z->left);
	}
	else {
		y = TREE_MINIMUM(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->p == z && x != nullptr)
			x->p = z;
		else {
			RB_TRANSPLANT(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		RB_TRANSPLANT(z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
		}
	delete z;
	if (y_original_color == 'B') {
		RB_DELETE_FIXUP(x);
	}
}

void RB_Tree::RB_DELETE_FIXUP(RB_Node* x) {
	while (x != nullptr && x != root && x->color == 'B') {
		if (x = x->p->left) {
			RB_Node* w = x->p->right;
			if (w->color == 'R') {
				w->color = 'B';
				x->p->color = 'R';
				left_rotate(x->p);
				w = x->p->right;
			}
			else if ((w->left == nullptr || w->left->color == 'B') && (w->right == nullptr && w->right->color == 'B')) {
				w->color = 'R';
				x = x->p;
			}
			else if (w->right == nullptr || w->right->color == 'B') {
				w->color = 'R';
				w->left->color = 'B';
				right_rotate(w);
				w = x->p->right;
			}
			w->color = x->p->color;
			w->right->color = 'B';
			x->p->color = 'B';
			left_rotate(x->p);
			x = root;
		}
		else {
			RB_Node* w = x->p->left;
			if (w->color == 'R') {
				w->color = 'B';
				x->p->color = 'R';
				right_rotate(x->p);
				w = x->p->left;
			}
			else if ((w->left == nullptr || w->left->color == 'B') && (w->right == nullptr && w->right->color == 'B')) {
				w->color = 'R';
				x = x->p;
			}
			else if (w->left == nullptr || w->left->color == 'B') {
				w->color = 'R';
				w->right->color = 'B';
				left_rotate(w);
				w = x->p->left;
			}
			w->color = x->p->color;
			w->left->color = 'B';
			x->p->color = 'B';
			right_rotate(x->p);
			x = root;
		}
	}
	root->color = 'B';
}