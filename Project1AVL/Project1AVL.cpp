
#include <iostream>
#include <string>
#include <istream>
#include <sstream>
using namespace std;

//individual class for each student node, holding their info to be inserted
//into the tree

class Student {
	// private variables / data for students  
private:
	string name;
	string idChars;
	int idNum;
	int balance;
	Student* left;
	Student* right;
	Student* parent;
	int height;

public:

	// constructor
	Student(string name, string gatorID, Student* parent) {
		this->name = name;
		this->idChars = gatorID;
		idNum = stoi(gatorID);
		left = nullptr;
		right = nullptr;
		this->parent = parent;
		balance = 0;
	}

	// accessors(getters) and mutators(setters)
	string getName() {
		return name;
	}

	//string to account for the ids with 0 in the beginning, int for comparison
	string getID() {
		return idChars;
	}

	int getIDNum() {
		return idNum;
	}

	Student* getLeft() {
		return left;
	}

	Student* getRight() {
		return right;
	}

	Student* getParent() {
		return parent;
	}

	int getHeight() {
		if (this == nullptr) {
			return 0;
		}
		if (left == nullptr && right == nullptr) {
			return 1;
		}
		int leftH = 0;
		if (left != nullptr) {
			leftH = left->getHeight();
		}

		int rightH = 0;
		if (right != nullptr) {
			rightH = right->getHeight();
		}

		if (leftH > rightH) {
			return 1 + leftH;
		}
		else
			return 1 + rightH;
	}

	void setLeft(Student* left) {
		this->left = left;
	}

	void setRight(Student* right) {
		this->right = right;
	}

	void setParent(Student* parent) {
		this->parent = parent;
	}

	void setHeight(int height) {
		this->height = height;
	}

	int getBalance() {
		return balance;
	}
	void setBalance(int balance) {
		this->balance = balance;
	}


};

//overarching class holds info that describes the entire avl tree
class Tree {

private:
	int numIDs;
	Student* root;
	int height;
	int x;

public:
	Tree() {
		numIDs = 0;
		root = nullptr;
		height = 0;
		x = 0;
	}
	int getNumIDs() {
		return numIDs;
	}
	int getHeight() {
		return height;
	}
	void setHeight(int height) {
		this->height = height;
	}
	void setRoot(Student* root) {
		this->root = root;
	}
	Student* getRoot() {
		return root;
	}
	void addID() {
		numIDs += 1;
	}
	int getX() {
		return x;
	}
	void addX(int a) {
		if (a == 1) {
			x += 1;
		}
		if (a == 0) {
			x = 0;
		}
	}
	Student* insertStudent(Student* root, Student* parent, string name, string idChars);
};

//balancing methods!

Student* rotateLeft(Student* student, Tree* t) {

	//perform the single left rotation
	Student* grandchild = student->getRight()->getLeft();
	Student* rotatedPar = student->getRight();
	rotatedPar->setLeft(student);
	student->setRight(grandchild);

	//update the height of the node
	if (student == t->getRoot()) {
		t->setRoot(rotatedPar);
	}
	int leftHeight = rotatedPar->getLeft()->getHeight();
	int rightHeight = rotatedPar->getRight()->getHeight();
	if (leftHeight > rightHeight) {
		rotatedPar->setHeight(leftHeight + 1);
	}
	else {
		rotatedPar->setHeight(rightHeight + 1);
	}
	//return the rotated node
	return rotatedPar;
}

Student* rotateRight(Student* student, Tree* t) {

	//perform the single right rotation
	Student* grandchild = student->getLeft()->getRight();
	Student* rotatedPar = student->getLeft();
	student->setLeft(grandchild);
	rotatedPar->setRight(student);

	//update the height of the node
	if (student == t->getRoot()) {
		t->setRoot(rotatedPar);
	}
	int leftHeight = rotatedPar->getLeft()->getHeight();
	int rightHeight = rotatedPar->getRight()->getHeight();
	if (leftHeight > rightHeight) {
		rotatedPar->setHeight(leftHeight + 1);
	}
	else {
		rotatedPar->setHeight(rightHeight + 1);
	}
	//return the rotated node
	return rotatedPar;
}

Student* rotateLeftRight(Student* student, Tree* t) {
	//perform the double rotation
	student->setLeft(rotateLeft(student->getLeft(), t));
	return rotateRight(student, t);

}

Student* rotateRightLeft(Student* student, Tree* t) {
	//perform double rotation
	student->setRight(rotateRight(student->getRight(), t));
	return rotateLeft(student, t);
}


//search for a student by their id
Student* inorderSearchID(Student* root, string gatorID) {
	Student* found = nullptr;
	if (root == nullptr) {
		return nullptr;
	}
	if (root->getID() == gatorID) {
		return root;
		//if found, return the pointer
	}
	else {
		//search left subtree
		found = inorderSearchID(root->getLeft(), gatorID);
		//search right subtree
		if (found == nullptr) {
			found = inorderSearchID(root->getRight(), gatorID);
		}
	}
	return found;
}

//search for a student by their name
int inorderSearchName(Student* root, string name) {
	Student* found = nullptr;
	int sum = 0;
	if (root == nullptr) {
		return 0;
	}

	//search left subtree
	sum += inorderSearchName(root->getLeft(), name);
	//node
	if (root->getName() == name) {
		cout << root->getID() << endl;
		sum += 1;
	}
	//search right subtree
	sum += inorderSearchName(root->getRight(), name);

	return sum;
}
//PRINT STATEMENTS

//print preorder
void printPreOrder(Student* root, Tree* t) {
	if (root == nullptr) {
	}
	else {
		if (root != t->getRoot()) {
			cout << ", ";
		}
		cout << root->getName();
		printPreOrder(root->getLeft(), t);
		printPreOrder(root->getRight(), t);
	}
}

//print postorder
void printPostOrder(Student* root, Tree* t) {
	if (root == nullptr) {
	}
	else {
		printPostOrder(root->getLeft(), t);
		printPostOrder(root->getRight(), t);

		cout << root->getName();
		if (root != t->getRoot()) {
			cout << ", ";
		}
	}
}

//print inorder
void printInorder(Student* root, Tree* t) {
	if (root == nullptr) {
	}
	else {
		printInorder(root->getLeft(), t);
		if (t->getX() != 0) {
			cout << ", " << root->getName();
		}
		else {
			cout << root->getName();
			t->addX(1);
		}
		printInorder(root->getRight(), t);
	}
}

//print levelCount
void printLevelCount(Tree* tree) {
	cout << tree->getRoot()->getHeight() << endl;
}

//insert a student

Student* studentInsert(Tree* t, Student* root, string idChars, string name) {
	//or goes through tree to find opening
	Student* parent = root;
	Student* curStudent = new Student(name, idChars, parent);
	if (parent == nullptr) {
		return curStudent;
	}
	else {
		if (parent->getIDNum() > stoi(idChars))
			parent->setLeft(studentInsert(t, root->getLeft(), idChars, name));
		else
			parent->setRight(studentInsert(t, root->getRight(), idChars, name));
	}

	//update the height of the node
	int leftHeight;
	int rightHeight;

	if (parent != nullptr && parent->getLeft() != nullptr) {
		leftHeight = parent->getLeft()->getHeight();
	}
	else leftHeight = 0;
	if (parent != nullptr && parent->getRight() != nullptr) {
		rightHeight = parent->getRight()->getHeight();
	}
	else rightHeight = 0;

	if (parent != nullptr && leftHeight > rightHeight) {
		parent->setHeight(leftHeight + 1);
	}
	else if (parent != nullptr) {
		parent->setHeight(rightHeight + 1);
	}
	// check if heavy, balance the tree
	if (parent != nullptr) {
		parent->setBalance(leftHeight - rightHeight);

		//left heavy
		if (parent->getBalance() > 1) {
			if (parent->getLeft() != nullptr) {
				// left sub left heavy
				if (parent->getLeft()->getIDNum() > stoi(idChars)) {
					return rotateRight(parent, t);
				}
				// left sub right heavy
				else {
					return rotateLeftRight(parent, t);
				}
			}
		}
		//right heavy
		if (parent->getBalance() < -1) {
			if (parent->getRight() != nullptr) {
				//right sub left heavy
				if (parent->getRight()->getIDNum() < stoi(idChars)) {
					return rotateLeft(parent, t);
				}
				//right sub right heavy
				else {
					return rotateRightLeft(parent, t);
				}
			}
		}
	}
	return root;
}
Student* Tree::insertStudent(Student* root, Student* parent, string name, string idChars) {
	// checks that name requirements are correct
	bool nameCorrect = true;
	for (unsigned int i = 0; i < name.size(); i++) {
		if ((name.at(i) >= 'A' && name.at(i) <= 'Z') || (name.at(i) >= 'a' && name.at(i) <= 'z') || name.at(i) == ' ') {
		}
		else {
			nameCorrect = false;
		}
	}
	// name requirements, gatorID length, and uniqueness must all be met
	if (inorderSearchID(root, idChars) != nullptr || idChars.size() != 8 || nameCorrect == false) {
		return nullptr;
	}
	this->setRoot(studentInsert(this, root, idChars, name));
	return this->getRoot();
}
//to find Inorder Successor
Student* findInorderSuccessor(Student* toDelete, Student* root) {
	if (root == nullptr) {

	}
	else if (root == toDelete) {
		root = root->getRight();
		while (root->getLeft() != nullptr) {
			root = root->getLeft();
		}
		return root;
	}
	findInorderSuccessor(toDelete, root->getLeft());

	findInorderSuccessor(toDelete, root->getRight());
	return nullptr;
}
// remove Inorder N
Student* removeInorder(int& n, int count, Student* root, Student* track) {
	if (track != nullptr) {
		return track;
	}
	else if (root == nullptr) {

	}
	else {
		track = removeInorder(n, count, root->getLeft(), track);
		n += 1;
		if (n == count + 1) {
			track = root;
			return track;
		}
		if (track == nullptr) {
			track = removeInorder(n, count, root->getRight(), track);
		}
	}
	return track;
}
Student* findParent(Student* root, Student* student) {
	Student* track = nullptr;

	if (root == student || root == nullptr) {
		return track;
	}
	if (root->getLeft() == student || root->getRight() == student) {
		return root;
	}
	track = findParent(root->getLeft(), student);
	if (track == nullptr) {
		track = findParent(root->getRight(), student);
	}
	return track;
}
// remove ID 
bool remove(Student* found, Tree* t) {
	if (found == nullptr) {
		return false;
	}
	found->setParent(findParent(t->getRoot(), found));
	if (found->getLeft() == nullptr && found->getRight() == nullptr) {

		if (found->getParent() != nullptr) {
			Student* tempParent = found->getParent();
			if (tempParent->getLeft() == found) {
				tempParent->setLeft(nullptr);
			}
			else if (tempParent->getRight() == found) {
				tempParent->setRight(nullptr);
			}
			tempParent->setHeight(tempParent->getHeight() - 1);
		}
		delete found;
		return true;
	}
	// 1 kid
	else if (found->getLeft() == nullptr && found->getRight() != nullptr) {
		Student* temp = found->getRight();
		if (found->getParent() != nullptr) {
			Student* parent = found->getParent();
			temp->setParent(parent);
			if (found->getParent()->getRight() == found) {
				parent->setRight(temp);
			}
			else if (found->getParent()->getLeft() == found) {
				parent->setLeft(temp);
			}
			parent->setHeight(parent->getHeight() - 1);
			temp->setHeight(temp->getHeight() - 1);
		}
		else { t->setRoot(temp); }
		delete found;
		return true;
	}
	else if (found->getLeft() != nullptr && found->getRight() == nullptr) {
		Student* temp = found->getLeft();
		if (found->getParent() != nullptr) {
			Student* parent = found->getParent();
			temp->setParent(parent);
			if (found->getParent()->getRight() == found) {
				parent->setRight(temp);
			}
			else if (found->getParent()->getLeft() == found) {
				parent->setLeft(temp);
			}
			parent->setHeight(parent->getHeight() - 1);
			temp->setHeight(temp->getHeight() - 1);
		}
		else { t->setRoot(temp); }
		delete found;
		return true;
	}
	//two kids
	else if (found->getLeft() != nullptr && found->getRight() != nullptr) {
		Student* tempLeft = found->getLeft();
		Student* tempRight = found->getRight();
		Student* successor = findInorderSuccessor(found, t->getRoot());
		Student* successorP = findParent(t->getRoot(), successor);
		if (found->getParent() != nullptr) {
			Student* tempParent = found->getParent();
			if (found->getParent()->getRight() == found) {
				tempParent->setRight(successor);
			}
			else if (found->getParent()->getLeft() == found) {
				tempParent->setLeft(successor);
			}
			successor->setParent(tempParent);
		}
		else { t->setRoot(successor); }
		if (tempLeft != successor) {
			successor->setLeft(tempLeft);
		}
		if (tempRight != successor) {
			successor->setRight(tempRight);
		}

		if (successorP->getLeft() == successor) {
			successorP->setLeft(nullptr);
		}
		else if (successorP->getRight() == successor) {
			successorP->setRight(nullptr);
		}
		return true;
	}
	delete found;
	return true;
}
// main function
int main()
{
	int numCommands;
	string inp;
	getline(cin, inp);
	numCommands = stoi(inp);
	Tree* t = new Tree();

	for (int i = 0; i < numCommands; i++) {
		getline(cin, inp);
		string word;
		string name;
		string num;
		char str[] = "";

		istringstream s(inp);
		s >> word;

		//these if statements could be made more efficient through a switch statement

		if (word == "insert") {
			s >> name;
			string lastName;
			if (name.at(name.size() - 1) == '"') {
				name = name.substr(1, name.size() - 2);
			}
			else {
				s >> lastName;
				name = name + ' ' + lastName;
				while (lastName.at(lastName.size() - 1) != '"') {
					s >> lastName;
					name = name + ' ' + lastName;
				}
				name = name.substr(1, name.size() - 2);
			}
			s >> num;
			Student* s = t->insertStudent(t->getRoot(), nullptr, name, num);
			if (s != nullptr) {
				cout << "successful";
			}
			else {
				cout << "unsuccessful";
			}
			cout << endl;
		}
		// removes a specific id
		if (word == "remove") {
			s >> num;
			Student* found = inorderSearchID(t->getRoot(), num);
			bool removed = remove(found, t);
			if (removed) {
				cout << "successful";
			}
			else {
				cout << "unsuccessful";
			}
			cout << endl;
		}
		// removes by number of location in inorder parsing
		if (word == "removeInorder") {
			s >> num;
			int n = 0;
			Student* Find = removeInorder(n, stoi(num), t->getRoot(), nullptr);
			bool removed = remove(Find, t);
			if (removed) {
				cout << "successful";
			}
			else {
				cout << "unsuccessful";
			}
			cout << endl;
		}
		//search by number or name, takes in input to check which
		if (word == "search") {
			s >> name;
			string lastName;
			Student* find = nullptr;
			if (isdigit(name.at(1))) {
				find = inorderSearchID(t->getRoot(), name);
				if (find != nullptr) {
					cout << find->getName();
				}
				else {
					cout << "unsuccessful";
				}
				cout << endl;
			}
			else {
				if (name.at(name.size() - 1) == '"') {
					name = name.substr(1, name.size() - 2);
				}
				else {
					s >> lastName;
					name = name + ' ' + lastName;
					while (lastName.at(lastName.size() - 1) != '"') {
						s >> lastName;
						name = name + ' ' + lastName;
					}
					name = name.substr(1, name.size() - 2);
				}
				int withName = inorderSearchName(t->getRoot(), name);
				if (withName == 0) {
					cout << "unsuccessful";
					cout << endl;
				}
			}
		}
		//printing statements
		if (word == "printInorder") {
			printInorder(t->getRoot(), t);
			cout << endl;
			t->addX(0);
		}
		if (word == "printPreorder") {
			printPreOrder(t->getRoot(), t);
			cout << endl;
		}
		if (word == "printPostorder") {
			printPostOrder(t->getRoot(), t);
			cout << endl;
		}
		if (word == "printLevelCount") {
			printLevelCount(t);
		}
	}

}

