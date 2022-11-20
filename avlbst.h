#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"





/*
TO DO List:
* remove()
* remove fix;
balance factor = height of left subtree - height of right subtree.
should always be 1, 0, or -1;
Completed Untested:
*/

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
		AVLTree();
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void left_rotate(const Key& key);
		void right_rotate(const Key& key);
		void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child);
		AVLNode<Key, Value>* look(const Key& key) const;
		AVLNode<Key, Value>* walk(AVLNode<Key, Value>* current, const Key& key) const;
		void removeFix(AVLNode<Key, Value>* current, int8_t diff);
		bool del(const Key& key);
};


template <class Key, class Value>
AVLTree<Key, Value>::AVLTree() : BinarySearchTree<Key, Value>()
{

}


template<class Key, class Value>
void AVLTree<Key, Value>::left_rotate(const Key& key)
{
/*
taking a right child, making it the parent
and making the og parent the new left child.
you will pass your og parent your left child.
it will become their right child.
*/
	AVLNode<Key, Value>* loc = look(key);
	if(loc == nullptr){
		//if the loc didn't exist, does nothing and returns;
		return;
	}
	AVLNode<Key, Value>* child = loc->getRight();
	if(child == nullptr){
		//if you don't have a child, also returns;
		return;
	}
	loc->setRight(child->getLeft());
	if(child->getLeft() != nullptr){
		//if it is a valid node, then sets that node's parent to loc.
		child->getLeft()->setParent(loc);
	}
	child->setParent(loc->getParent());
	if(loc->getParent() != nullptr){
		//sets the grandparent to point to its grandchild.
		if(loc->getParent()->getRight() == loc){
			loc->getParent()->setRight(child);
		}
		else{
			loc->getParent()->setLeft(child);
		}
	}
	loc->setParent(child);
	child->setLeft(loc);

	if(this->root_ == loc){
		//if the root was involved in the rotation, ensures that the root_ is accurate.
		this->root_ = child;
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::right_rotate(const Key& key)
{
			/*
		taking a left child, making it the parent
		and making the og parent the new right child.
		you will pass your og parent your right child.
		it will become their left child.
		*/
	AVLNode<Key, Value>* loc = look(key);
	if(loc == nullptr){
		return;
	}
	AVLNode<Key, Value>* child = loc->getLeft();
	if(child == nullptr){
		return;
	}
	loc->setLeft(child->getRight());
	if(child->getRight() != nullptr){
		child->getRight()->setParent(loc);
	}
	child->setParent(loc->getParent());
	if(loc->getParent() != nullptr){
		//makes grandparent point to grandchild
		if(loc->getParent()->getRight() == loc){
			loc->getParent()->setRight(child);
		}
		else{
			loc->getParent()->setLeft(child);
		}
	}
	loc->setParent(child);
	child->setRight(loc);

	if(this->root_ == loc){
		//ensures root is accurate
		this->root_ = child;
	}
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template <class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
		AVLNode<Key, Value>* final = nullptr;
		if(this->root_ == NULL){
			final = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);

			this->root_ = final;
			return;
    }

    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    //start at the root.
    //keep going until you find the empty spot you need.
    while(1){
        if(new_item.first == temp->getKey()){
					//if you find a matching existing key, update the value and break the loop.
						temp->setValue(new_item.second);
            break;
        }
				if(new_item.first < temp->getKey()){
            //if the value is less than the temp, go left.
            if(temp->getLeft() == nullptr){
                //if free spot, create a node and insert.
                final = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
                temp->setLeft(final);
								temp->updateBalance(-1);
                break;
            }
            else{
                //if no free spot, then temp is the left node and keep going.
                temp = temp->getLeft();
            }
        }
				else if(new_item.first > temp->getKey()){
          //if the value is greater than the temp, go right.
            if(temp->getRight() == nullptr){
                //if free spot, create a new node and insert.
                final = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
                temp->setRight(final);
								temp->updateBalance(1);
                break;
            }
            else{
                //if no free spot, then temp is the right node and keep going.
                temp = temp->getRight();
            }
        }
    }
		if(temp->getBalance() != 0){
			//after inserted into the bst
			insertFix(temp, final);
		}
		//update balances.
		//call insertfix on that new node and its parent.
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child){
	if(parent == nullptr){
		//if parent is null return;
		return;
	}

	AVLNode<Key, Value>* gp = parent->getParent();

	if(gp == nullptr){
		//if grandparent is null, return;
		return;
	}

	//update balance, then check what case it is.
	if(gp->getLeft() == parent){
		//became left heavy, -1 to its balance.
		gp->updateBalance(-1);
	}
	else if(gp->getRight() == parent){
		//became right heavy, + 1 to its balance.
		gp->updateBalance(1);
	}



	if(gp->getBalance() == 0){
		//if balanced, return;
		return;
	}

	else if(gp->getBalance() == -1 || gp->getBalance() == 1){
		//if the balance of the grandparent is -1 or 1 recurse;
		insertFix(gp, parent);
	}

	else{//gp's balance is either -2 or 2
		if(gp->getBalance() == -2){
			//left heavy tree.
			if(parent->getBalance() == -1){
				//if -2 and -1, left heavy zig zig.
				right_rotate(gp->getKey());
				gp->setBalance(0);
				parent->setBalance(0);
			}
			else{
				//if -2 and 1, left heavy zig zag.
				left_rotate(parent->getKey());
				right_rotate(gp->getKey());
				//three cases to update Balance.
				if(child->getBalance() == -1){
					parent->setBalance(0);
					gp->setBalance(1);
					child->setBalance(0);
				}
				else if(child->getBalance() == 1){
					parent->setBalance(-1);
					gp->setBalance(0);
					child->setBalance(0);
				}
				else{//b(n) == 0
					parent->setBalance(0);
					gp->setBalance(0);
					child->setBalance(0);
				}
			}
		}
		else{//gp balance is 2;
			if(parent->getBalance() == 1){//switched
				//if 2 and 1, right heavy zig zig.
				left_rotate(gp->getKey());//switched
				gp->setBalance(0);
				parent->setBalance(0);
			}
			else{
				//if 2 and -1, right heavy zig zag;
				
				right_rotate(parent->getKey());	
				left_rotate(gp->getKey());
				//three cases to update Balance.
				if(child->getBalance() == -1){
					parent->setBalance(1);
					gp->setBalance(0);
					child->setBalance(0);
				}
				else if(child->getBalance() == 1){
					parent->setBalance(0);
					gp->setBalance(-1);
					child->setBalance(0);
				}
				else{//b(n) == 0
					parent->setBalance(0);
					gp->setBalance(0);
					child->setBalance(0);
				}
				
			}

		}
		//perform zig zig or zig zag rotation.
	}
}


template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::look(const Key& key) const
{
    // TODO
		if(this->root_ == nullptr){
			return nullptr;
		}
		AVLNode<Key, Value>* final = walk(static_cast<AVLNode<Key, Value>*>(this->root_), key);//calls helper to do work.
		return final;//returns result
}

/**
Recursive helper function to traverse a tree and find the a key.
*/
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::walk(AVLNode<Key, Value>* current, const Key& key) const{
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
	AVLNode<Key, Value>* left = walk(current->getLeft(), key);
	AVLNode<Key, Value>* right = walk(current->getRight(), key);
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

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
		AVLNode<Key, Value>* child = look(key);
		if(child == nullptr){
			return;
		}
		AVLNode<Key, Value>* parent = nullptr;
		AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(child));
		AVLNode<Key, Value>* pPar = nullptr;
		bool paired = 0;
		int pSide = 0;
		
		if(pred != nullptr){
			pPar = pred->getParent();
			if(child == pred->getParent()){
				paired = 1;
			}
		}
		if(pPar != nullptr){
			if(pPar->getLeft() == pred){
				pSide = 1;//left;
			}
			else if(pPar->getRight() == pred){
				pSide = 2;//right;
			}
		}

		parent = child->getParent();
		int8_t diff = 0;
		if(parent != nullptr){
			if(parent->getLeft() == child){
				diff = 1;
			}
			else{
				diff = -1;
			}
		}
		bool swapped = del(key);
		if(swapped == 1){
			if(paired){
				parent = pred;
			}
			else{
				parent = pPar;
			}
			if(pSide == 1){
				diff = 1;
			}
			else{
				diff = -1;
			}
		}
		removeFix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* current, int8_t diff)
{
	if(current == nullptr){
		//if the node is null, does nothing
		return;
	}
	AVLNode<Key, Value>* parent = current->getParent();
	int8_t nextDiff;
	if(parent == nullptr){
		//if the parent is null sets nextDiff to an unused val
		nextDiff = 0;
	}
	else{
		if(parent->getLeft() == current){
			//if current is a left child, next diff will be 1
			nextDiff = 1;
		}
		else{
			//if current is a right child, next diff will be a -1
			nextDiff = -1;
		}
	}

	if(current->getBalance() + diff == -2){
		//if the balance of the grandparent is -2,
		//let c = left(n), the taller of the children
		AVLNode<Key, Value>* c = current->getLeft();
		if(c->getBalance() == -1){
			//zig zig case.
			c->setBalance(0);
			current->setBalance(0);
			right_rotate(current->getKey());
			removeFix(parent, nextDiff);
		}
		else if(c->getBalance() == 0){
			//zig zig case
			current->setBalance(-1);
			c->setBalance(1);
			right_rotate(current->getKey());
		}
		else{
			//
			AVLNode<Key, Value>* g = c->getRight();
			left_rotate(c->getKey());
			right_rotate(current->getKey());
			if(g->getBalance() == 1){
				current->setBalance(0);
				c->setBalance(-1);
				g->setBalance(0);
			}
			else if(g->getBalance() == -1){
				current->setBalance(1);
				c->setBalance(0);
				g->setBalance(0);
			}
			else{
				current->setBalance(0);
				c->setBalance(0);
				g->setBalance(0);
			}
		}
		removeFix(parent, nextDiff);
	}
	else if(current->getBalance() + diff == 2){
		AVLNode<Key, Value>* c = current->getRight();
		if(c->getBalance() == 1){
			//zig zig case
			left_rotate(current->getKey());
			current->setBalance(0);
			c->setBalance(0);
			removeFix(parent, nextDiff);
		}
		else if(c->getBalance() == 0){
			left_rotate(current->getKey());
			current->setBalance(1);
			c->setBalance(-1);
		}
		else{//c->getBalance() == -1
			AVLNode<Key, Value>* g = c->getLeft();
			right_rotate(c->getKey());
			left_rotate(current->getKey());
			if(g->getBalance() == -1){
				current->setBalance(0);
				c->setBalance(1);
				g->setBalance(0);
			}
			else if(g->getBalance() == 1){
				current->setBalance(-1);
				c->setBalance(0);
				g->setBalance(0);
			}
			else{
				current->setBalance(0);
				c->setBalance(0);
				g->setBalance(0);
			}
			removeFix(parent, nextDiff);
		}

	}
	else if(current->getBalance() + diff == -1){
		current->setBalance(-1);
	}
	else if(current->getBalance() + diff == 1){
		current->setBalance(1);
	}
	else{//(current->getBalance() + diff == 0){
		current->setBalance(0);
		removeFix(parent, nextDiff);
	}
}

template<class Key, class Value>
bool AVLTree<Key, Value>::del(const Key& key){
	//method for deleting a node from the the AVL Tree.
	//returns a bool indicating whether or not a swap was performed.
		AVLNode<Key, Value>* loc = look(key);
		if(loc == nullptr){
			//if you try to delete an invalid node, the function returns and does nothing.
			return 0;
		}
		else if(loc->getLeft() == nullptr && loc->getRight() == nullptr){
			AVLNode<Key, Value>* temp = loc;
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
				this->root_ = nullptr;
			}
			delete temp;
			return 0;
		}
		else if(loc->getLeft() == nullptr || loc->getRight() == nullptr){
			//Node<Key, Value>* swap = loc;
			//you have to first figure out if you are a left or right child.
			AVLNode<Key, Value>* temp = loc;
			if(loc->getParent() == nullptr){
				//if your parent is the nullptr, then you just promote it and remove
				if(loc->getLeft() != nullptr){
					this->root_ = loc->getLeft();
					loc->getLeft()->setParent(nullptr);
				}
				else{
					this->root_ = loc->getRight();
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
			return 0;
		}
		else{
			//if the node to be deleted has two children
			AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(loc));//swap with your predecessor, turns into a one child or no child case.
			this->nodeSwap(loc, pred);
			if(this->root_ == loc){
				this->root_ = pred;
			}
			bool inter = del(key);
			return 1;
		}
}
template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}
#endif