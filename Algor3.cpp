#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int val) : data(val), left(nullptr), right(nullptr) {}
	~Node() {
		std::cout << "Удаление узла с data: " << data << std::endl;
		delete left;
		delete right;
	}
};

class IdealBalancedTree {
private:
	Node* root = nullptr;

	Node* buildTree(const std::vector<int>& values, int n, int index) {
		if (n <= 0) return nullptr;

		Node* node = new Node(values[index++]);

		std::pair<int, int> lr = GetLeftRightHeight(n);

		node->left = buildTree(values, lr.first, index);
		node->right = buildTree(values, lr.second, index + lr.first);

		return node;
	}

	static std::pair<int,int> GetLeftRightHeight(int n) {
		int left, right;
		left = n / 2;
		right = n - left - 1;
		return { left, right };
	}


	static std::ostream& print_helper(std::ostream& os, const Node* root, int level=0) {
		if (!root) {
			os << std::string(level, '|') << "None" << '\n';
			return os;
		}

		
		os << std::string(level, '|') << root->data << '\n';
		print_helper(os, root->right, level + 1);
		print_helper(os, root->left, level + 1);
		
		
		return os;
	}

	void rnl_helper(Node* node, std::vector<int>& result) const {
		if (!node) return;

		rnl_helper(node->right, result);
		result.push_back(node->data);
		rnl_helper(node->left, result);
	}

	
public:
	IdealBalancedTree() = delete;

	IdealBalancedTree(const std::vector<int>& values) {
		root = buildTree(values, values.size(), 0);
	}

	friend std::ostream& operator<<(std::ostream& os, const IdealBalancedTree& tree){
		os << "Right" << "\n_______________________" << std::endl;
		print_helper(os, tree.root, 0);
		os << "_______________________\n" << "Left"  << std::endl;

		return os;
	}

	std::vector<int> rnl() const {
		std::vector<int> result;

		rnl_helper(root, result);

		return result;
	}


	~IdealBalancedTree() {
		std::cout << "Удаление дерева..." << std::endl;
		delete root;
	}
};

int main()
{
	setlocale(LC_ALL, "RU");

	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> dist(100, 999);
	
	int n = 26;
	std::vector<int> randomized(n);

	for (int i = 0; i < n; ++i) {
		int key;
		do {
			key = std::rand() % (999 - 100 + 1) + 100;
		} while (find(randomized.begin(), randomized.end(), key) != randomized.end());
		randomized[i] = key;
	}

	n = 10;
	randomized = std::vector<int>{ 67,11,36,44,38,19,81,55,24,73 };

	for (int i = 0; i < n; ++i)
		std::cout << randomized[i] << " ";
	std::cout << std::endl;

	IdealBalancedTree tree(randomized);

	std::cout << std::endl;
	std::cout << "обычный вывод:" << std::endl;
	std::cout << tree << std::endl;

	std::cout << "вывод обходом RNL:" << std::endl;
	auto vector = tree.rnl();
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;
	std::cout << std::endl;
	return 0;
}