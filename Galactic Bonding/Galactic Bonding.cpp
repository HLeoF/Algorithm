/*
* Author: Maiqi Hou
* Assignment 8.1: Galactic Bonding 
* Assignment Description: The program counts how many constellations.
* Due Date: 8/2/2021
* Date Created: 7/24/2021
* Date Last Modified: 7/30/2021
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Points;
class disjointSet {
    private:
        vector<int> pset;

        // add a frined class, which can call 
        // functions in this class
        friend class Points; 
    public:
        /*
        * description: default constructor
        * return: None
        * precondition: n is valid(n = number of sets)
        * postcondition: None
        */
        disjointSet(int n) {
            pset.assign(n, 0);
        }
        /*
        * description: initial disjoint set
        * return: None
        * precondition: n is valid(n = number of sets)
        * postcondition: None
        */
        void initSet(int n) {
            for (size_t i = 0; i < n; i++) {
                pset[i] = i;
            }
        }

        /*
         * description: find set 
         * return: int 
         * precondition: i is valid
         * postcondition: if find set, return i
         */
        int findSet(int i) {
            if (pset[i] == i)
                return i;
            else
                return (pset[i] = findSet(pset[i]));
        }

        /*
        * description: check two set are same
        * return: bool type
        * precondition: i and j is valid
        * postcondition: if set i and j not equal, two set are not same.
        *                if set i and j equal, two set are same.
        */
        bool isSameSet(int i, int j) {
            return findSet(i) == findSet(j);
        }

        /*
        * description: union two 
        * return: bool type
        * precondition: i and j is valid
        * postcondition: if i not equal to j, they are not at same set
        */
        void unionSet(int i, int j) {
            pset[findSet(i)] = findSet(j);
        }

        /*
        * description: count set
        * return: int type
        * precondition: n is valid
        * postcondition: number of sets
        */
        int countSet(int n) {
            int count = 0;
            for (size_t i = 0; i < n; i++) {
                if (pset[i] == i)
                    count++;
            }
            return count;
        }
};

class Points {
    private:
        double x, y;
    public:
        /*
        * description: default constructor
        * return: None
        * precondition: None
        * postcondition: None
        */
        Points() {
            x = 0.0;
            y = 0.0;
        }

        /*
        * description: get the value of x 
        * return: double
        * precondition: None
        * postcondition: value of x
        */
        double gX() {
            return x;
        }
        /*
        * description: get the value of y
        * return: double
        * precondition: None
        * postcondition: value of y
        */
        double gY() {
            return y;
        }

        /*
        * description: store the stars x and y coordinates
        * return: None
        * precondition: x, y and vertor v are valid
        * postcondition: None
        */
        void set(double x_c, double y_c, vector<Points>& v) {
            Points p;
            p.x = x_c;
            p.y = y_c;
            v.push_back(p);
        }

        /*
        * description: counting the distance between two stars and sets
        * return: None
        * precondition: vetcor v, x, d, disjointSet set are valid
        * postcondition: None
        */
        void dis(vector<Points> v, int& n, double d, disjointSet set) {
            double distance = 0.0;
            int s = v.size();

            //if number of stars greater than vector size(store stars' coordinates)
            //return and print the number of sets.
            if (n >= s) {
                n = set.countSet(s);
                return;
            }
            for (int i = n+1; i < s; i++) {
                distance = sqrt(pow((v[i].gX() - v[n].gX()), 2.0)
                    + pow((v[i].gY() - v[n].gY()), 2.0));
                //cout << n << " --> " << i <<" = " << distance << endl;
                if (distance <= d) {
                    if (!set.isSameSet(i, n)) {
                        set.unionSet(i, n);
                    }
                }
            }
            n += 1;
            dis(v, n, d,set);
        }
};

/*
* Data Abstraction:
        3 int variables t_case, star, count. The t_case is counting how 
        many cases users enter. Three double variables x, y, and d.The x
        and y is coordinate position. The d is the distance between two stars
* Input:
        user enter The number of tests T (T ≤ 50) is on the first line.
        Each test case contains the number of stars N (0 ≤ N ≤ 1000) 
        a real distance D (0.00 ≤ D ≤ 1000.00). The next N lines have a 
        pair of real coordinates X Y (−1000.00 ≤ X, Y ≤ 1000.00) 
        for each star.
* Process:
        Computing distance between two stars. If the distance is less or equal 
        to the D unit. Unioning these two stars into one set. Counting the number of 
        set of stars. 
* Output:
        Reporting the order of the case and the number of constellations of each case.
*/
int main() {
    
    int t_case = 0;
    int star = 0;
    double d = 0.0;
    double x, y = 0.0;
    int count = 0;

    cout << "Counting Constellations System" << endl << endl;
    cin >> t_case;

    int* array = new int[t_case+1];

    while (count < t_case) {
        Points p;
        vector<Points> v;
        int n = 0;

        cin >> star >> d; // read the number of stars
        //initial disjoint set
        disjointSet set(star);
        set.initSet(star);

        while (star != 0) {
            cin >> x >> y;
            p.set(x, y, v);
            star--;
        }
        p.dis(v, n, d, set);//counting number of constellations
        array[count] = n;
        count++;
    }
    cout << endl << endl;

    //report each case
    for (int i = 0; i < t_case; i++) {
        cout << "case " << i + 1 << ": " << array[i] << endl;
    }
    delete[] array;
    cout << endl;

    return 0;

}