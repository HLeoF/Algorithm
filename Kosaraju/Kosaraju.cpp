/*
* Author: Maiqi Hou
*/
#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <stack>
using namespace std;

class D_graph {
protected:
    int vertex;
    list<int>* adj_list;
public:
    D_graph(int);
    void add_edges(int, int);
    void dfs(int&, stack<int>&);
    void explore(int&, stack<int>&, bool[], int&, bool);
    void rGraph(D_graph, int);
    int kosaraju();
};

/*
* description: initialize the data in class
* return: None
* precondition: the int ver is valid
* postcondition: None
*/
D_graph::D_graph(int ver) {
    vertex = 0;
    vertex = ver;
    adj_list = new list<int>[ver + 1];

}

/*
* description: add a edge between two vertexs.
* return: None
* precondition: mem1 and mem2 are valid
* postcondition: None
*/
void D_graph::add_edges(int mem1, int mem2) {
    adj_list[mem1].push_back(mem2);
}

/*
* description: DFS, exlpore each vertexs of a directed graph
* return: None
* precondition: int v, stack sta, bool array visited, int count and bool t
*               are valid.
* postcondition: None
* This function reference by textbook(P95), and adding the additional ideas
*/

void D_graph::explore(int& v, stack<int>& sta, bool visited[], int& count, bool t) {
    list<int>::iterator neigbor;
    if (visited[v] == true) {
        return;
    }
    visited[v] = true;
    if (t == true) { // process first DFS
        sta.push(v); //push data into stack
    }
    else if (t == false) { // process second DFS
        count++;//count the number of strong compunts 
    }
    for (neigbor = adj_list[v].begin(); neigbor != adj_list[v].end(); neigbor++) {
        if (!visited[*neigbor]) {
            explore(*neigbor, sta, visited, count, t); //check next vertex is visitied
        }
    }
}

/*
* description: DFS initialize step and Check if there are 
                remaining vertex that has not been DFS
* return: None
* precondition: int v and stack path are valid
* postcondition: None
* This function reference by textbook(P96), and adding the additional ideas
*/
void D_graph::dfs(int& v, stack<int>& path) {
    bool* visited = new bool[vertex + 1];
    visited[0] = false;
    stack<int> store;
    bool graph_reverse = true;
    int count = 0;

    //initial visited vertex array "all false:
    for (int i = 0; i < vertex + 1; i++) {
        visited[i] = false; // initialize bool array 
                            //check a vertex visited.
    }
    if (path.empty()) {
        //chenk all vertex visited?
        for (int i = 1; i < vertex + 1; i++) {
            //check if there are remaining vertexs do not process DFS
            if (visited[i] != true) { 
                explore(i, store, visited, count, graph_reverse);
                while (store.size() != 0) {
                    //stack path copy visitied vertex from stack path
                    path.push(store.top()); 
                    store.pop();
                }
            }
        }
        delete[] visited; //deallocate bool array memory
    }
    else {
        count = 0;
        int temp = 0;
        graph_reverse = false;
        //second DFS process
        while (!path.empty()) { 
            v = path.top();
            explore(v, path, visited, count, graph_reverse);
            //declare temp store biggest number of Strong Components
            if (temp < count || temp == 0) {
                temp = count;
            }
            while (count != 0) {
                //pop vertex from stack path(means vertexs are visited)
                path.pop();
                count--;
            }

        }
        v = temp;
        delete[]visited; //deallocate memory
    }
}

/*
* description: Reverse original graph direction
* return: None
* precondition: rG and v are valid
* postcondition: None
*/
void D_graph::rGraph(D_graph rG, int v) {
    if (v <= vertex) {
        list<int>::iterator it;
        for (it = adj_list[v].begin(); it != adj_list[v].end(); it++) {
            rG.add_edges(*it, v);
        }
        v++;
        rGraph(rG, v);
    }
}

/*
* description: Computing Strong Components
* return: int
* precondition: None
* postcondition: return the number of strong components 
*/
int D_graph::kosaraju() {
    int val = 1;
    stack<int> path;
    //DFS first time, support alway start at vertex 1
    dfs(val, path);

    //reverse graph
    D_graph reverse(vertex);
    //start reverse graph at vertex 1
    rGraph(reverse, 1);
    val = 0;
    //Begin second DFS
    reverse.dfs(val, path);
    //return the biggest strong compoment
    return val;
}
/*
* Data Abstraction:
        Four string variable name, native, ol, and s. name is a member's name 
        native is a member's speaking language. ol is other languages that a member 
        can understand. Two linked-list nativeL and OtherL, which are stored the 
        member's speaking language and other understanding languages. 
        One int variable (val) for how many members. Stringstream sub, separating the ol 
        string by a space call D_graph g. Using these information create a direction graph
* Input:
        Enter the number of members
        Enter their speaking language and other understanding languages 
* Process:
        The program will create a directed graph using an adjacency list. Using the Kosaraju
        algorithm to find a group members can converse and kick members who can not converse.
* Output:
        Report the number of members who cannot converse.
* Assumption:
        It only suppose that users enter data maunally.
        Ensure the correctness of the input language words.
*/
int main() {
    string name, native, ol, s;
    list<string>* nativeL, * OtherL;
    int val = 0;
    cin >> val;

    stringstream sub;
    D_graph g(val);
   
    OtherL = new list<string>[val + 1];
    nativeL = new list<string>[val + 1];

    //I create two lists to store the Native language
    //and other understanding languages
    for (int i = 1; i <=val; i++) {
        cin >> name >> native;
        getline(cin, ol);
        nativeL[i].push_back(native);
        sub.clear();
        sub.str(ol);
        while (sub >> s) {
            OtherL[i].push_back(s);
        }
    }
    list<string>::iterator it, a;

    //Using the adjacency list to store the member's 
    //first language and other understanding languages.
    //Concrete a direction graph
    for (int i = 1; i <= val; i++) {
        string n1, n2;
        a = nativeL[i].begin();
        n1 = *a;
        for (int j = 1; j <= val; j++) {
            if (i != j) {
                for (it = OtherL[j].begin(); it != OtherL[j].end(); it++) {
                    n2 = *it;
                    if (n1.compare(n2)==0) {
                        g.add_edges(i, j);
                    }
                }
            }  
        }
    }
    cout << endl;
    cout << "The size of leaving set is " << val - g.kosaraju() << endl;
    return 0;
}