#include <iostream>
#include "redblack.h"

using namespace std;
int main() {
	RedBlack* tree = new RedBlack();
	char op;
	int num;
	do {
		cout << "Op: ";
		cin >> op;
		switch(op) {
			case 'i':
				cin >> num;
				tree->insert(num);
				break;
			case 'p':
				tree->print();
				break;
			case 'x':
				cout << "Exiting . . .";
		}
	} while (op != 'x');
	return 0;
}
