#include <vector>
#include <string>
#include <cassert>
using namespace std;

struct QuadTreeNode {
	QuadTreeNode* son[4];
	QuadTreeNode() {
		son[0] = son[1] = son[2] = son[3] = nullptr;
	}
	QuadTreeNode(QuadTreeNode *i0, QuadTreeNode *i1, QuadTreeNode *i2, QuadTreeNode *i3) {
		son[0] = i0;
		son[1] = i1;
		son[2] = i2;
		son[3] = i3;
	}
	string DisplaysNormal();
	string DisplaysDepth();
};

string dfs_normal(QuadTreeNode *root) {
	if (root == nullptr) return "B";
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (root->son[i] == nullptr) cnt++;
	}
	if (cnt == 4) return "N";
	string ret = "(";
	for (int i = 0; i < 4; i++) {
		ret += dfs_normal(root->son[i]);
	}
	return ret + ")";
}

string dfs_depth(QuadTreeNode *root, int depth) {
	if (root == nullptr) return "B" + to_string(depth);
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (root->son[i] == nullptr) cnt++;
	}
	if (cnt == 4) return "N" + to_string(depth);
	string ret = "(";
	for (int i = 0; i < 4; i++) {
		ret += dfs_depth(root->son[i], depth + 1);
	}
	return ret + ")";
}

string QuadTreeNode::DisplaysNormal() {
	return dfs_normal(this);
}

string QuadTreeNode::DisplaysDepth() {
	return dfs_depth(this, 0);
}

QuadTreeNode* White() {
	return nullptr;
}

QuadTreeNode* Black() {
	return new QuadTreeNode();
}

QuadTreeNode* Composed(QuadTreeNode *i0, QuadTreeNode *i1, QuadTreeNode *i2, QuadTreeNode *i3) {
	return new QuadTreeNode(i0, i1, i2, i3);
}

QuadTreeNode* from_string(const string &ret, int l, int r) {
	if (l == r) {
		if (ret[l] == 'B') {
			return White();
		}
		if (ret[l] == 'N') {
			return Black();
		}
	}
	if (ret[l] == '(' && ret[r] == ')') {
		return from_string(ret, l + 1, r - 1);
	}
	int from = l, index = 0, cnt = 0;
	QuadTreeNode *root = new QuadTreeNode();
	for (int i = l; i <= r; i++) {
		if (ret[i] == '(') cnt++;
		if (ret[i] == ')') cnt--;
		if (cnt == 0) {
			assert(index < 4);
			root->son[index++] = from_string(ret, from, i);
			from = i + 1;
		}		
	}
	assert(index == 4);
	return root;
}

QuadTreeNode* PlayBack(const string &str) {
	return from_string(str, 0, str.size() - 1);
}

bool IsBlack(QuadTreeNode* root) {
	if (root == nullptr) return false;
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (root->son[i] == nullptr) cnt++;
	}
	if (cnt == 4) return true;
	for (int i = 0; i < 4; i++) {
		if (!IsBlack(root->son[i])) return false;
	}
	return true;
}

bool IsWhite(QuadTreeNode* root) {
	if (root == nullptr) return true;
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (root->son[i] == nullptr) cnt++;
	}
	if (cnt == 4) return false;
	for (int i = 0; i < 4; i++) {
		if (!IsWhite(root->son[i])) return false;
	}
	return true;
}

QuadTreeNode* Diagonal(int p) {
	QuadTreeNode *root = new QuadTreeNode();
	if (p == 1) {
		return root;
	}
	root->son[0] = Diagonal(p - 1);
	root->son[3] = Diagonal(p - 1);
	root->son[1] = root->son[2] = nullptr;
	return root;
}

QuadTreeNode* QuarterTurn(QuadTreeNode *root) {
	if (root == nullptr) return nullptr;
	QuadTreeNode* ret = new QuadTreeNode();
	for (int i = 0; i < 4; i++) {
		ret->son[i] = QuarterTurn(root->son[(i + 3) % 4]);
	}
	return ret;
}

QuadTreeNode* Negative(QuadTreeNode *root) {
	if (IsBlack(root)) return White();
	if (IsWhite(root)) return Black();
	QuadTreeNode *ret = new QuadTreeNode();
	for (int i = 0; i < 4; i++) {
		ret->son[i] = Negative(root->son[i]);
	}
	return ret;
}

QuadTreeNode* simplify(QuadTreeNode *root) {
	if (IsBlack(root)) return Black();
	if (IsWhite(root)) return White();
	return root;
}

QuadTreeNode* SimplifyDepthP(QuadTreeNode *root, int p) {
	if (root == nullptr) return root;
	if (p == 0) return simplify(root);
	QuadTreeNode *ret = new QuadTreeNode();
	for (int i = 0; i < 4; i++) {
		ret->son[i] = SimplifyDepthP(ret->son[i], p - 1);
	}
	return ret;
}

int main() {
	return 0;
}