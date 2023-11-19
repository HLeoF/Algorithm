/*
* Author: Maiqi Hou
* Assignment 10.1: Huffman Encoding
* Assignment Description: This program using Huffman's theory 
                          to compress and uncompress file
* Due Date: 8/11/2021
* Date Created: 8/9/2021
* Date Last Modified: 8/10/2021
*/

#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <fstream>
#include <queue>
#include <map>
using namespace std;
class compare;
class HuffmanTree;

class Node {
private:
    int ch;
    int weight;
    Node* right;
    Node* left;
    friend class compare;
    friend class HuffmanTree;
public:
    /*
    * description: default constructor
    * return: None
    * precondition: char and weight are valid
    * postcondition: None
    *
    */
    Node(int c, int w) {
        ch = c;
        weight = w;
        left = right = NULL;
    }
};
class compare {
    public:
        /*
        * description: bool operator
        * return: None
        * precondition: Node a and Node b are valid
        * postcondition: if Node a's weight is equal to Node b's weight
                         return a'char lager than b'char
                         else return a'weight lager than b'weight
        *
        */
        bool operator()(Node* a, Node* b) {
            if (a->weight == b->weight) {
                return a->ch > b->ch;
            }
            return a->weight > b->weight;
            
        }
};

class HuffmanTree {
    private:
        map<int, string>m;
        string a;
        priority_queue<Node*, vector<Node*>, compare> pq;

    public:
       /*
       * description: Creat a priority queue
       * return: None
       * precondition: store char array and priority q are valid
       * postcondition: None;
       *
       */
        void priorityQ(int array[]) {
            for (int i = 0; i < 128; i++) {
                if (array[i] != 0) {
                    Node* n = new Node(i, array[i]);
                    pq.push(n);
                }
            }
            string in = "en";
            tree(pq,in);
        }
       /*
       * description: concerte a Huffman Tree
       * return: None
       * precondition: priority queue and string in are valid
       * postcondition: None
       *
       */
        void tree(priority_queue<Node*, vector<Node*>, compare>& q, string in) {

            while (q.size() != 1) {
                Node* left = q.top();
                q.pop();
                Node* right = q.top();
                q.pop();
                Node* node = new Node(128, left->weight + right->weight);
                node->left = left;
                node->right = right;
                q.push(node);
            }
            Node* root = q.top();
            //if the command is en, It executes decode task
            if (in == "en") {
                char a[128];
                int index = 0;
                huffcode(root, m, index,a);   
            }

        }
        /*
        * description: Record the code of the character
        * return: None
        * precondition: Node t, map m, int index, and char array a are valid
        * postcondition: None
        *
        */
        void huffcode(Node* t, map<int, string>& m, int index, char a[]) {
            if (t->left) {
                a[index] = '0';
                huffcode(t->left, m, index+1,a);
            }
            if (t->right) {
                a[index] = '1';
                huffcode(t->right, m, index+1,a);
            }
            //if node'right and left are nullptr;
            //find the character and record the path
            if (!t->left && !t->right) {
                string chara;
                for (int i = 0; i < index; i++) {
                    chara += a[i];
                }
                m[t->ch] = chara;
            }
       
        }
        /*
        * description: Pass the map to main, storing each character's code
        * return: None
        * precondition: map table is valid;
        * postcondition: None
        *
        */
        void Encode(map<int, string>& table) {
            table = m;
        }

        /*
        * description: Read compressed file, read the character's counts
                       prepare recrate huffman tree
        * return: None
        * precondition: int array a, string s, and ofstream& a are valid
        * postcondition: None
        *
        */
        void Store(int array[], string s, ofstream& a) {
            //character counts stored in the compressed file
            //It facilitates decoding tasks and reconstructing Huffman Tree
            a << "Store:" << endl;
            for (int i = 0; i < 128; i++) {
                if (array[i] != 0) {
                    a << i << " " << array[i] << endl;
                }
            }
        }
        /*
        * description:  recreate huffman tree
        * return: None
        * precondition: string filen are valid
        * postcondition: None
        *
        */
        void ReCreateTree(string filen) {
            ifstream f;
            f.open(filen);
            int index = 0, n = 0, ti = 0;
            while (!pq.empty()) {
                pq.pop();
            }
            string temp;
            //read store characters count at first
            while (temp != "Store:") {
                getline(f, temp);
            }
            //recreate huffman tree
            while (!f.eof()) {
                f >> index >> n;
                if (ti != index) {
                    Node* node = new Node(index, n);
                    pq.push(node);
                }
                ti = index;
            }
            f.close();
            string in = "de";
            tree(pq, in);
        }
        /*
        * description: Codes decode each character
        * return: None
        * precondition: string s and c are valid
        * postcondition: None
        *
        */
        void Decode(string s, string& c) {
            Node* temp = pq.top();
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '0') {
                    temp = temp->left;
                }
                else if (s[i] == '1'){
                    temp = temp->right;
                }
                if (!temp->left && !temp->right) {
                    c += char(temp->ch);
                    temp = pq.top();
                }
            }
        }
   
};
/*
   Data Abstraction:
        int array with size = 128(ASCII code), ifstream file, ofstream output
        string command, source, destination, s store, and c
        priority queue q and map table, and HuffmanTree ht;
 Input:
       -huff: compresses a given file
       -unhuff: uncompresses a file compressed by huff
       <source>: file to be compressed or uncompressed
       <destination>: output file
 Process：
     To compress the files：
        Read file,and count how many times every character occurs in a file,
        Build the Huffman tree.Create a table or map of characters to codings
        read the input file a second time. For each character write the encoding 
        of the character to the compressed file.
     To uncompress the files:
        Recreate the huffman tree which was used to compress the file originally.
        For codes write the decoding of the character to the uncompressed file. 
 Output:
        The destination file
*/
int main() {
    int array[128] = { 0 };
    ifstream file;
    ofstream output;
    string command, source, destination, s, store, c = "";
    priority_queue<Node*, vector<Node*>, compare> q;
    map<int, string> table;
    HuffmanTree ht;

    cin >> command >> source >> destination;

    //earse "<" and ">" char in string source and destination
    source.erase(0, 1);
    source.erase(source.length() - 1, 1);
    destination.erase(0, 1);
    destination.erase(destination.length() - 1, 1);
    
    //Encode Part
    if (command == "-huff" || command == "huff") {
        file.open(source);
        //count characters
        while (!file.eof()) {
            getline(file, s);
            for (int i = 0; i < s.length(); i++) {
                array[int(s[i])] += 1;
            }
            s.clear();
        }
        file.close();

        ht.priorityQ(array);
        ht.Encode(table);

        file.open(source);
        output.open(destination);
        output << "2" << endl;// "magic number" add to compressed files
        //record the character's code
        while (!file.eof()) {
            getline(file, s);
            for (int i = 0; i < s.length(); i++) {
                output << table[int(s[i])];
            }
            output << endl;
            s.clear();
        }
        ht.Store(array, destination, output);
        file.close();
        output.close();
        source.clear();
        destination.clear();


    }
    //decode part
    if (command == "-unhuff" || command == "unhuff") {
        file.open(source);
        output.open(destination);
        getline(file,s);
        //determine file is compressed file or not.
        if (s != "2") {
            cout << "Sorry, this file has not been compressed" << endl;
        }
        else {
            ht.ReCreateTree(source);
            while (s != "Store:") {
                getline(file, s);
                if(s != "Store:"){
                    ht.Decode(s, c);
                    output << c << endl;
                    c.clear();
                }
            }
        }
        file.close();
        output.close();
    }
    return 0;
}