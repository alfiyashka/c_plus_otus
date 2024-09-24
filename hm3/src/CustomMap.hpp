#ifndef CUSTOM_MAP
#define CUSTOM_MAP

#include "CustomNode.hpp"
#include "CustomMapIterator.hpp"

#include <memory>
using namespace std;


template <class Key, class Value, class Comparator = std::greater<Key>,
    class Allocator = std::allocator<CustomNode<Key, Value> > >
class CustomMap
{
public:
    using value_type = CustomNode<Key, Value>;
private:
	value_type* root;
    
	size_t _size;
	Comparator comparator;
    Allocator allocator;

    value_type* newnode(const value_type& node)
    {
        value_type* nodePtr = allocator.allocate(1);
        _size ++;
        (*nodePtr) = node;
        return nodePtr;
    }

    value_type* insertion(value_type *root, const value_type& node)
    {
        if (root == nullptr)
        {
            root = newnode(node);
            return root;
        }
        if (this->comparator(root->getKey(), node.getKey()))
        {
            root->setLeft(insertion(root->getLeft(), node));   // recurse on left
            root->getLeft()->setParent(root);
        }
        else
        {
            root->setRight(insertion(root->getRight(), node)); // recurse on right
            root->getRight()->setParent(root);
        }

        return root;
    }

    void removeAll() { removeAll(this->root); }
    void removeAll(value_type *&node)
    {
        if (!node)
            return;

        removeAll(node->getLeft());
        removeAll(node->getRight());
       
        allocator.deallocate(node, 1);
        node = nullptr;
    }

public:
    using Iterator = CustomMapIterator<Key, Value, Comparator>;

    CustomMap(): root(nullptr), _size(0) {}
    ~CustomMap() { removeAll(); }

    void insert(const value_type& node)
    {
        root = insertion(root, node);
    }

    void insert(Key key, Value value)
	{
		const value_type node{key, value};
		root = insertion(root, node);
	}

    Iterator begin()
	{
		if (this->root == nullptr)
			return Iterator();
		value_type *tmp = this->root;
		while (tmp->getLeft()!= nullptr)
		{
			tmp = tmp->getLeft();
		}
		return Iterator(tmp);
	}
 
	Iterator end()
	{
		return Iterator();
    }



};


#endif