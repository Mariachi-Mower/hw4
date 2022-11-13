#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>


/*
COMPlETED, NOT TESTED:
* BST constructor
* void insert(const Key& key);
* operator !=
* operator ==
* iterator default constructor
* iterator ptr explicit constructor
* isBalanced
* cIfBalanced
* predecessor
* BST Destructor
* Node<Key, Value>* getSmallestNode();
* void clear():
* void remove(const Key& key);
* operator++:
*/






/*
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;//the node's name and value
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value>* getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current);
		static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		int cIfBalanced(Node<Key, Value>* root) const; //helper function for isBalanced
		static Node<Key, Value>* cPred(Node<Key, Value>* current);// TODO  helper function for predecessor
		static Node<Key, Value>* aPred(Node<Key, Value>* current, Node<Key, Value>* prev);
		static Node<Key, Value>* cSucc(Node<Key, Value>* current);// TODO  helper function for predecessor
		static Node<Key, Value>* aSucc(Node<Key, Value>* current, Node<Key, Value>* prev);// TODO helper function for predecessor
		void clearOut(Node<Key, Value>* root);// helper function for clear()
		Node<Key, Value>* traverse(Node<Key, Value>* current, const Key& key) const;//helper function for internalFind()


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) : current_(ptr)
{
    // TODO
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL)
{
    // TODO

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		if(this->current_ == nullptr || rhs.current_ == nullptr){
			//if either has a pointer to null, only compares if they are equal
			if(this->current_ == rhs.current_){
				return 1;
			}
			return 0;
		}
    if(this->current_->getKey() == rhs.current_->getKey()){
			//otherwise compares keys.
        return 1;
    }
    return 0;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		if(this->current_ == nullptr || rhs.current_ == nullptr){
			//if one of their pointers is null, them.
			if(this->current_ == rhs.current_){
				return 0;
			}
			return 1;
		}
    if(this->current_->getKey() == rhs.current_->getKey()){
			//otherwise compares their keys
        return 0;
    }
    return 1;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
		//this will call the successor function
		//write the successor function first.
    //implement after creating the find. 
		Node<Key, Value>* succ = successor(this->current_);
		current_ = succ;
		return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()  : root_(NULL)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    //should just call the clear function.
		clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}


/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //first handle an empty tree.
    //if the parent doesn't exist, then add the node to the binary search tree.
    if(root_ == NULL){
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
				return;
    }

    Node<Key, Value>* temp = root_;
    //start at the root.
    //keep going until you find the empty spot you need.
    while(1){
        if(keyValuePair.first == temp->getKey()){
					//if you find a matching existing key, update the value and break the loop.
						temp->setValue(keyValuePair.second);
            break;
        }
				if(keyValuePair.first < temp->getKey()){
            //if the value is less than the temp, go left.
            if(temp->getLeft() == nullptr){
                //if free spot, create a node and insert.
                Node<Key, Value>* final = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
                temp->setLeft(final);
                break;
            }
            else{
                //if no free spot, then temp is the left node and keep going.
                temp = temp->getLeft();
            }
        }
				else if(keyValuePair.first > temp->getKey()){
          //if the value is greater than the temp, go right.
            if(temp->getRight() == nullptr){
                //if free spot, create a new node and insert.
                Node<Key, Value>* final = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
                temp->setRight(final);
                break;
            }
            else{
                //if no free spot, then temp is the right node and keep going.
                temp = temp->getRight();
            }
        }
    }
}



/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
		//three possible cases.
    // TODO
		Node<Key, Value>* loc = internalFind(key);
		if(loc == nullptr){
			//if you try to delete an invalid node, the function returns and does nothing.
			return;
		}
		else if(loc->getLeft() == nullptr && loc->getRight() == nullptr){
			Node<Key, Value>* temp = loc;
			//if the node to be deleted is a leaf node.
			if(loc->getParent() != nullptr){
				//if you are not the root_
				if(loc->getParent()->getLeft() == loc){
					//if you are your parent's left child, their left is set to nullptr.
					loc->getParent()->setLeft(nullptr);
				}
				else{
					//if you are your parent's right child, their right is set to nullptr.
					loc->getParent()->setRight(nullptr);
				}
			}
			else{
				//if at root set the root to nullptr.
				root_ = nullptr;
			}
			delete temp;
			return;
		}
		else if(loc->getLeft() == nullptr || loc->getRight() == nullptr){
			//Node<Key, Value>* swap = loc;
			//you have to first figure out if you are a left or right child.
			Node<Key, Value>* temp = loc;
			if(loc->getParent() == nullptr){
				//if your parent is the nullptr, then you just promote it and remove
				if(loc->getLeft() != nullptr){
					root_ = loc->getLeft();
					loc->getLeft()->setParent(nullptr);
				}
				else{
					root_ = loc->getRight();
					loc->getRight()->setParent(nullptr);
				}
			}
			else{//(loc->getParent() != nullptr){
				if(loc->getParent()->getRight() == loc){
					//you are a right child.
					
					if(loc->getLeft() != nullptr){
						//and your only child is a left pointer.
						loc->getParent()->setRight(loc->getLeft());
						loc->getLeft()->setParent(loc->getParent());
					}
					else{
						//your only child is a right pointer.
						loc->getParent()->setRight(loc->getRight());
						loc->getRight()->setParent(loc->getParent());
					}
					
				}
				else{
					//you are a left child.
					if(loc->getLeft() != nullptr){
					//and your only child is a left pointer.
						loc->getParent()->setLeft(loc->getLeft());
						loc->getLeft()->setParent(loc->getParent());
					}
					else{
					//your only child is a right pointer.
					loc->getParent()->setLeft(loc->getRight());
					loc->getRight()->setParent(loc->getParent());
					}
				}
			}
			delete temp;
			return;
		}
		else{
			//if the node to be deleted has two children
			Node<Key, Value>* pred = predecessor(loc);//swap with your predecessor, turns into a one child or no child case.
			nodeSwap(loc, pred);
			//find its new loc.
			remove(loc->getKey());
		}
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::cPred(Node<Key, Value>* current){
	//this helper function runs when the left subtree exists.
	//will run while the right child exists.
	//base case is root->right == nullptr; return's the current.
	if(current == nullptr){
		return nullptr;
	}
	if(current->getRight() == nullptr){
		return current;
	}
	current = cPred(current->getRight());
  return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::cSucc(Node<Key, Value>* current){
	//this helper function runs when the right subtree exists.
	//will run while the left child exists.
	//base case is root->left == nullptr; return's the current.
	if(current == nullptr){
		return nullptr;
	}
	if(current->getLeft() == nullptr){
		return current;
		//formatlly return current->getParent();
		//must rewrite so that there is something to return here.
	}
	current = cSucc(current->getLeft());
  return current;
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::aPred(Node<Key, Value>* current, Node<Key, Value>* prev){
	//this helper function will run when left child doesn't exist.
	//it will go up the tree until it finds the first parent of a right child or returns nullptr otherwise.
    //if the parameter you pass in is equal to the right child of the current node. you have found the pred.
		if(current == nullptr){
			//base case is you reach root node without finding right child.
			//if not pred, then return nullptr.
			return nullptr;
		}
		if(current->getRight() == prev){
			//if you find the parent of a right node, return that parent.
			return current;
		}
		current = aPred(current->getParent(), current);//go up the ancestors.
		return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::aSucc(Node<Key, Value>* current, Node<Key, Value>* prev){
	//this helper function will run when right child doesn't exist.
	//it will go up the tree until it finds the first parent of a left child or returns nullptr otherwise.
    //if the parameter you pass in is equal to the left child of the current node. you have found the succ.
		if(current == nullptr){
			//base case is you reach root node without finding right child.
			//if not pred, then return nullptr.
			return nullptr;
		}
		if(current->getLeft() == prev){
			//if you find the parent of a right node, return that parent.
			return current;
		}
		current = aSucc(current->getParent(), current);//go up the ancestors.
		return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
		/*
		defined as the next smallest value in the tree
		if the left child exists, predecessor is the right most node in your left subtree.
		//if no left child exists, then it is the first left ancestor of the tree.
		//i have a feeling this one needs a helper function.
		//it should call one depending on what the sit is and return the val they produce.
		*/
		if(current == nullptr){
			//if pred is called on an invalid node, then it 
			return nullptr;
		}

		if(current->getLeft() == nullptr){
			return aPred(current->getParent(), current);
		}
		else{
			return cPred(current->getLeft());
		}
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current){
		if(current == nullptr){
			//if pred is called on an invalid node, then it returns nullptr.
			return nullptr;
		}

		if(current->getRight() == nullptr){
			//if no right child exists, goes up ancestor chain.
			return aSucc(current->getParent(), current);
		}
		else{
			//if right child exists, finds left most node in right subtree.
			return cSucc(current->getRight());
		}
}





/**
* A helper recursive function for clearing a binary search tree.
*called by clear();
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearOut(Node<Key, Value>* root){
	//base case is a leaf node.
	if(root == nullptr){
		return;
	}
	if(root->getLeft() != nullptr || root->getRight() != nullptr){
		//if not at a leaf node, then it calls clearOut on both its left and right subtrees.
		clearOut(root->getLeft());
		clearOut(root->getRight());
	}
	//after the if the statement, you are now at a leaf node.
	//so you delete that leaf node and set its pointer to nullptr;
	Node<Key, Value>* temp = root;
	if(root->getParent() != nullptr){
		if(root->getParent()->getLeft() == root){
			root->getParent()->setLeft(nullptr);
		}
		else{
			root->getParent()->setRight(nullptr);
		}
	}
	delete temp;
	return;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
		//would just call clearOut.
		if(root_ == nullptr){
			return;
		}
		clearOut(root_);
		root_ = nullptr;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    //used by the iterator.
    //go up the entire tree until you find the smallest node.
		Node<Key, Value>* temp = root_;
		if(temp == nullptr){
			return nullptr;
		}
		while(temp->getLeft() != NULL){
			temp = temp->getLeft();
		}
		return temp;
    
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
		if(empty()){
			return nullptr;
		}
		Node<Key, Value>* final = traverse(root_, key);//calls helper to do work.
		return final;//returns result
}

/**
Recursive helper function to traverse a tree and find the a key.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::traverse(Node<Key, Value>* current, const Key& key) const{
	//should return a node or nullptr.
	//will keep traversing the right and left.
	if(current == nullptr){
		//base case non existent node.
		return nullptr;
	}
	if(current->getKey() == key){
		//if it finds the key, returns the pointer
		return current;
	}
	//traverse both the left and right child of each node. 
	Node<Key, Value>* left = traverse(current->getLeft(), key);
	Node<Key, Value>* right = traverse(current->getRight(), key);
	if(left != nullptr){
		//if the left child is the key, returns that pointer.
		return left;
	}
	else if(right != nullptr){
		//if the right child is the key, returns that pointer.
		return right;
	}
	return nullptr;
	//if neither of them are the key, returns nullptr.
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
		int height = cIfBalanced(root_);//calls helper to do work.
		if(height == -1){
			return 0;
		}
		return 1;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::cIfBalanced(Node<Key, Value>* root) const{
	if(root == nullptr){
		return 0;
	}

	int lh = cIfBalanced(root->getLeft());//gets height of left subtree.
	int rh = cIfBalanced(root->getRight());//gets height of right subtree.

	if(lh == -1){
		//if the left tree's height is -1, returns -1;
		return -1;
	}
	if(rh == -1){
		//if the left tree's height is -1, returns -1;
		return -1;
	}

	if(abs(lh - rh) > 1){
		//calculates difference of left and right, if the difference is more than 1
		//it will return -1;
		return -1;
	}
	else{
		//if the height is not more than 1, returns 1 + the max of the two heights.
		return 1 + std::max(lh, rh);
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif