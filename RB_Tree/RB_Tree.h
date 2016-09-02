#ifndef RB_TREE_H
#define RB_TREE_H

struct RB_Node {
	RB_Node() :key(-1), color('B'), p(nullptr), left(nullptr), right(nullptr) {};
	RB_Node(int k) : key(k), color('R'), p(nullptr), left(nullptr), right(nullptr) {};
	int key;
	char color;
	RB_Node* p;
	RB_Node* left;
	RB_Node* right;

	//inline bool operator==(const RB_Node& node) {
	//	return this->color == node.color && this->p == node.p && this->left == node.left && this->right == node.right;
	//}
};

class RB_Tree {
public:
	RB_Tree() :root(nullptr) {};
	void rb_insert(RB_Node*);
	void rb_delete(RB_Node*);
	RB_Node* root;
private:
	void left_rotate(RB_Node*);
	void right_rotate(RB_Node*);
	void RB_INSERT(RB_Node*);
	void RB_INSERT_FIXUP(RB_Node*);
	void RB_TRANSPLANT(RB_Node*, RB_Node*);
	void RB_DELETE(RB_Node*);
	void RB_DELETE_FIXUP(RB_Node*);
	RB_Node* TREE_MINIMUM(RB_Node*);
};

#endif