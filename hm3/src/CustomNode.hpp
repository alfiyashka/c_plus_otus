#ifndef CUSTOM_NODE
#define CUSTOM_NODE

template <class Key, class Value>
class CustomNode
{
public:
	CustomNode() noexcept : parent(nullptr), left(nullptr), right(nullptr) {}
    CustomNode(Key k, Value v) noexcept : key(k), value(v), parent(nullptr), left(nullptr), right(nullptr) {}
    CustomNode(const CustomNode& node) noexcept : key(node.key), value(node.value), parent(node.parent), left(node.left), right(node.right) {}
	CustomNode& operator=(const CustomNode& node) noexcept
	{
		this->key = node.key;
		this->value = node.value;
		this->parent = node.parent;
		this->left = node.left;
		this->right = node.right;
		return *this;
	}
	CustomNode& operator=(CustomNode&& node) noexcept = delete;

	CustomNode(CustomNode&& node) = delete;
	
	~CustomNode()
	{ 
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

    Key getKey() const { return key; }
    const Value& getValue() const { return value; }

    void setParent(CustomNode* node) { parent = node; }
    auto getParent() { return parent; }

    auto& getLeft() { return left; }
	const auto getLeft() const { return left; }
	void setLeft(CustomNode* node) { left = node; }

	auto& getRight() { return right; }
	const auto getRight() const { return right; }
	void setRight(CustomNode* node) { right = node; }

private:
	Key key;
	Value value;

	CustomNode<Key, Value>* parent;
	CustomNode<Key, Value>* left;
	CustomNode<Key, Value>* right;

};


#endif