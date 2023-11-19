/*
* Author: Maiqi Hou
* Assignment 6.1: BBST SELECT
* Assignment Description: 
*   This program is creat a Balanced Binary Tree. After that,
*   User can enter a order of BBST. The program will report the 
*   the value at that order of BBST.
* Due Date: 7/11/2021
* Date Created: 7/2021
* Date Last Modified: 7/10/2021
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class BBST;
class BBSTNode {
    protected:
        int data;
        BBSTNode* left, * right;
    public:
        friend class BBST;
        BBSTNode() { data = 0; right = left = NULL; }
        BBSTNode(int value) { data = value; right = left = NULL;}
        ~BBSTNode() {
            if (left != NULL) { delete left;}
            if (right != NULL) { delete right; }
        }
};
class BBST {
    protected:
        BBSTNode* root;

        BBSTNode* insertNode(BBSTNode*, const int);
        BBSTNode* singlelr(BBSTNode*);
        BBSTNode* singleRr(BBSTNode*);
        BBSTNode* dLRr(BBSTNode*);
        BBSTNode* dRLr(BBSTNode*);
        BBSTNode* checkBalance(BBSTNode*);

        int height(BBSTNode*);
        void inorderSearch(BBSTNode*, vector<int>&);

    public:
        BBST() { root = NULL;}
        virtual ~BBST() { delete root;}
        void insert(const int);
        void Select(int[],int&);
};

/*
* description: insert a new node to a tree
* return: BBSTNode*
* precondition: root and key are valid
* postcondition: return root node of whole tree
*/
BBSTNode* BBST::insertNode(BBSTNode* root, const int key) {
    if (!root) {
        root = new BBSTNode(key);
    }
    else {
        if (key < root->data) {
            root->left = insertNode(root->left, key);
            root = checkBalance(root);
        }
        if (root->data < key) {
            root->right = insertNode(root->right, key);
            root = checkBalance(root);
        }
        if (root->data == key) {
            return root;
        }
    }
    return root;
}

/*
* description: Balanced Binary Tree single left rotation
* return: BBSTNode
* precondition: root is valid
* postcondition: returns node after single left rotation
*/
BBSTNode* BBST::singlelr(BBSTNode* root) {
    BBSTNode* node = root->right;
    root->right = node->left;
    node->left = root;

    height(node); //update the height
    height(root); //update the height root node
    return node;
}

/*
* description: Balanced Binary Tree single right rotation
* return: BBSTNode
* precondition: root is valid
* postcondition: returns node after single right rotation
*/
BBSTNode* BBST::singleRr(BBSTNode* root) {
    BBSTNode* node = root->left;
    root->left = node->right;
    node->right = root;

    height(root);//update the height
    height(node); //update the height
    return node;  
}

/*
* description: Balanced Binary Tree double left-right rotation
* return: BBSTNode
* precondition: root is valid
* postcondition: returns node after double left-right rotation
*/
BBSTNode* BBST::dLRr(BBSTNode* root) {
    BBSTNode* node = root;
    node->left = singlelr(node->left);
    return singleRr(node);
}

/*
* description: Balanced Binary Tree double right-left rotation
* return: BBSTNode
* precondition: root is valid
* postcondition: returns node after double right-left rotation
*/
BBSTNode* BBST::dRLr(BBSTNode* root) {
    BBSTNode* node = root;
    node->right = singleRr(node->right);
    return singlelr(node);
}

/*
* description: Check the BBST balanced, if it not balance
*   it will begin rotation according the different height between
*   spling node.
* return: int
* precondition: root is valid
* postcondition: returns BBST root after it balanced.
*/
BBSTNode* BBST::checkBalance(BBSTNode* root) {
    int Hdiff = height(root->left) - height(root->right);

    if (Hdiff > 1) {
        int diff = height(root->left->left) - height(root->left->right);
        if (diff < 0) {
            root = dLRr(root);
        }
        else {
            root = singleRr(root);
        }
    }
    else if (Hdiff < -1) {
        int diff = height(root->right->left) - height(root->right->right);
        if (diff < 0) {
            root = singlelr(root);
        }
        else {

            root = dRLr(root);
        }

    }
    height(root); //updata root height
    return root;
}
/*
* description: get the each node hight of BBST
* return: int
* precondition: root is valid
* postcondition: returns node height of a BBST
*/
int BBST::height(BBSTNode* root) {
    if (!root) {
        return 0;
    }
    int lefth = (height(root->left));
    int righth = (height(root->right));
    return (lefth > righth ? lefth : righth) + 1;
}
/*
* description: Inorder travel the whole Balanced Binary Tree
* return: None
* precondition: root and key are valid
* postcondition: None
*/
void BBST::inorderSearch(BBSTNode* root, vector<int>& v) {
    if (!root) {
        return;
    }
    inorderSearch(root->left, v);
    // push the tree value for inoder travel
    v.push_back(root->data);
    inorderSearch(root->right, v);
}


/*
* description: insertNode function external interface, passing the 
*   value to insertNode function. Adding a new node into BBST.
* return: None
* precondition: key is valid
* postcondition: None
*/
void BBST::insert(const int key) {
    root = insertNode(root, key);//add new node into BBST
}

/*
* description: Seach the value of order of the select statistic from BBST
* return: N
* precondition: array and value are valid
* postcondition: val will pass the value of selection order from BBST
*/
void BBST::Select(int arr[] ,int& val) {
    vector<int> a;
    inorderSearch(root, a);//inorder travel whole BBST, store the values
                           //into a vector
    int j = 0;
    for (auto i = a.begin(); i != a.end(); i++) {
        arr[j] = *i; //put the data for the vector into a array.
        j++;
    }
    val = arr[val];//return the value that user select order from BBST.
}


/*
* Data Abstraction:
*       User enters two-line information. several values which
*       insert into Balanced Binary Tree and order of the select
*       statistic. After that, the program will show the value of order
*       the select statistic.
*
* Input:
        Input two lines
        The first line is a space-delimited set of numerical values which you will
            insert into a Balanced Binary Search Tree.
        The second line is the order of the select statistic which will be SELECTED
            from the BBST(Balanced Binary Tree).
* Process:
        insert the number of values into a BBST.
        Search the value of select Statistic from the BBST.
        report the value of the order of select from the BBST.
* Output:
        value of the selected order of statistics which was found in the
        BBST and a newline.
* Assumptions:
        It is assumed only a user enters some integer number.
        It is assumed only a user one order of select statics from BBST
*/
int main() {
    BBST bst;
    string number;
    int c = 0;
    
    cout << "Please enter some elements(integer): ";
    getline(cin, number);// input a line integer
    stringstream(num); 

    num.str(number);// splitting according to a space-delimited set
    int val;
    while (num >> val) {
        bst.insert(val);//insert values into a BBST
        c++;
    }
    cout << "Order Of Statistic: ";
    cin >> val;

    int* arr = new int[c];
    arr[0] = 0;

    if (val >= c) { //if select order out of range of BBST
        cout << "No Found" << endl; //report no found
    }
    else {
        val -= 1;
        bst.Select(arr, val);
        cout << "The value is " << val << endl;
    }
    
    return 0;
}