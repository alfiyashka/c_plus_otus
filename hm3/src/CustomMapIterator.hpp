#ifndef CUSTOM_MAP_ITERATOR
#define CUSTOM_MAP_ITERATOR

#include "CustomMap.hpp"
#include "CustomNode.hpp"

template <class Key, class Value, class Comparator = std::greater<Key> >
struct CustomMapIterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = CustomNode<Key, Value>;
    using pointer = CustomNode<Key, Value> *;
    using reference = CustomNode<Key, Value> &;

	Comparator comparator;

    CustomMapIterator(pointer ptr) : m_ptr(ptr), m_start_ptr(ptr) {}
    CustomMapIterator() : m_ptr(nullptr), m_start_ptr(nullptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    CustomMapIterator &operator++(int ) = delete;
    CustomMapIterator &operator++()
    {
        if (this->m_ptr == nullptr)
        {
            return *this;
        }
        value_type *tmpPtr = this->m_ptr;
        if (tmpPtr->getLeft() == nullptr && tmpPtr->getRight() == nullptr)
		{
			if (this->m_ptr == this->m_start_ptr)
			{
				this->m_ptr = tmpPtr->getParent();
			}
			else
			{
				while (tmpPtr->getParent() != nullptr)
				{
					tmpPtr = tmpPtr->getParent();
				    if (tmpPtr->getLeft() != nullptr 
					   && tmpPtr->getRight() != nullptr
					   && comparator(tmpPtr->getKey(), m_ptr->getKey()))
					{
						this->m_ptr = tmpPtr;
						break;
					}
					else if (tmpPtr->getLeft() != nullptr 
					   && tmpPtr->getRight() != nullptr
					   && comparator(tmpPtr->getKey(), m_ptr->getKey()))
					{
						this->m_ptr = tmpPtr->getParent();
						break;
					}
					else if (tmpPtr->getLeft() != nullptr && tmpPtr->getRight() == nullptr)
					{
						this->m_ptr = tmpPtr;
						break;
					}
				}
			}
			if (!comparator(tmpPtr->getKey(), this->m_ptr->getKey())
			   && tmpPtr->getParent() == nullptr
			   && tmpPtr->getLeft() == nullptr)
            {
                this->m_ptr = nullptr;
                return *this;
            }
			return *this;
		}
            Key key = this->m_ptr->getKey();
            if (tmpPtr->getRight() != nullptr)
            {
                tmpPtr = tmpPtr->getRight();

                while (tmpPtr->getLeft() != nullptr && !comparator(key, tmpPtr->getLeft()->getKey()))
                {
                    tmpPtr = tmpPtr->getLeft();
                }
				
				this->m_ptr = tmpPtr;           

                return *this;
            }
            else
            {
                if (tmpPtr->getParent() != nullptr)
                {
                    tmpPtr = tmpPtr->getParent();
                    if (comparator(tmpPtr->getKey(), key))
                    {
						m_ptr = tmpPtr;
						return *this;
					}
					else
					{
						while (!comparator(tmpPtr->getKey(), m_ptr->getKey()))
						{
							if (tmpPtr->getParent() == nullptr)
                        	{
								this->m_ptr = nullptr;
								return *this;
                        	}
							tmpPtr = tmpPtr->getParent();
						}
						m_ptr = tmpPtr; 
						return *this;              
                    }
                }
            }
            this->m_ptr = nullptr;
            return *this;
        }



    friend bool operator==(const CustomMapIterator &a, const CustomMapIterator &b) 
    { 
        return a.m_ptr == b.m_ptr; 
    }

    friend bool operator!=(const CustomMapIterator &a, const CustomMapIterator &b)
    { 
        return a.m_ptr != b.m_ptr; 
    }

private:
    pointer m_ptr;
	pointer m_start_ptr;
};

#endif