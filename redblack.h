#include "node.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
class RedBlack {
	node* root;
	int size;
	public:
	RedBlack() {
		root = NULL;
		size = 0;
	}
	
	void insert(int num) {
		node* x = (node*) calloc( 1, sizeof(node) );
		x->elem = num;
		x->isRed = true;

		if (root == NULL) {
			x->isRed = false;
			root = x;
		} else {
			node* y = search(root, num);
		
			if (y->elem > num)
				y->left = x;
			else
				y->right = x;
			
			x->parent = y;
			
			if (y->isRed) {
				node* y = x->parent;
				node* z = y->parent;
				node* s = z->left == y ? z->right : z->left;

				if (s == NULL || s->isRed == false) {
					// case 1
					restructure(x);
				} else {
					checkCaseTwoViolation(y);
				}
			}
		}
		
		size++;
	}
	
	void checkCaseTwoViolation(node* y) {
		node* z = y->parent;
		node* s = z->left == y ? z->right : z->left;
		if (s->isRed) {
			recolor(y, s, z);
		}
		
		checkCaseTwoViolation(z);
	}
	
	void recolor(node* y, node* s, node* z) {
		y->isRed = false;
		s->isRed = false;
		if (z != root)
			z->isRed = true;
	}
	
	node* search(node* n, int num) {
		if (n->elem >= num) {
			return n->left == NULL ? n : search(n->left, num);
		}
		
		return n->right == NULL ? n : search(n->right, num);
	}
	
	void restructure(node* x) {
		node *z, *y;
		
		if (x)
			y = x->parent;
		
		if (y)
			z = y->parent;
			
		if (z->right == y && y->right == x) {
			zigleft(x);
		} else if (z->left == y && y->left == x) {
			zigright(x);
		} else if (z->right == y) {
			zigright(x);
			zigleft(x);
		} else if (z->left == y) {
			zigleft(x);
			zigright(x);
		}
	}
	
    void zigleft(node* x) {
        node* y = x->parent;
        node* z = y->parent;

        if (y == NULL)
            return;

        y->parent = x;
        x->parent = z;

        y->right = x->left; 
        x->left = y;
         
        if (y->right)
            y->right->parent = y;

        if (z == NULL)
            root = x;
        else if (x->elem > z->elem)
            z->right = x;
        else
            z->left = x;
    }

    void zigright(node* x) {
        node* y = x->parent;
        node* z = y->parent;

        if (y == NULL)
            return;

        y->parent = x;
        x->parent = z;

        y->left = x->right; 
        x->right = y;
        
        if (y->left)
            y->left->parent = y;

        if (z == NULL)
            root = x;
        else if (x->elem > z->elem)
            z->right = x;
        else
            z->left = x;
    }
	
	void print() {
		cout << "Size: " << size << endl;
		print("", 'Q', root);
	}
	
	void print(string pre, char loc, node* n) {
		if (!n)
			return;
			
		print(pre + "    ", 'L', n->left);
		cout << pre << "|--" << loc << ": " << n->elem ;

		if (n->isRed)
			cout << "(R)" << endl;
		else
			cout << "(B)" << endl;
		print(pre + "    ", 'R', n->right);
	}
};
