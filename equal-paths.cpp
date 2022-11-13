#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int subH(Node* root){
    //should traverse until it finds a null node.
    //height of every node should be equal to 1 + height of everything before.
    if(root == NULL){
        return 0;
    }
    int left = subH(root->left);
    int right = subH(root->right);
    if(left > right){
        return left + 1;
    }
    else{
        return right + 1;
    }
}

bool equalPaths(Node * root)
{
	if(root == NULL){
		return 1;
	}
	int left = subH(root->left);
	int right = subH(root->right);
	if(left == 0 && right == 1){
		return 1;
	}
	else if(left == 1 && right == 0){
		return 1;
	}
	return (left == right);
    // Add your code below
}

