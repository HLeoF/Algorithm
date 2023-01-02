/*
* Name: Maiqi Hou
*/
#include <iostream>
#include <fstream>
/*
* The running time of three merge sort is
* T(N) = O(N log3 N). 
*
* The example name: sample1.txt, sample2.txt, sample3.txt
*/

using namespace std;
void ThreeMerge(int a[], int l, int m1, int m2, int r) {
    int* temp = NULL;
    temp = new int[r+1];
    temp[0] = 1;
    int i = l;
    int g1 = l, g2 = m1 + 1, g3 = m2 + 1;

    //Suppose three group both have data
    while (g1 <= m1 && g2 <= m2 && g3 <= r) {
        if (a[g1] <= a[g2] && a[g1] <= a[g3]) {
            temp[i++] = a[g1++];
        }
        else if (a[g2] <= a[g1] && a[g2] <= a[g3]) {
            temp[i++] = a[g2++];
        }
        else if(a[g3] <= a[g1] && a[g3] <= a[g2]) {
            temp[i++] = a[g3++];
        }
    }
    //suppose still have two gourps have exist data unording
    while (g1 <= m1 && g2 <= m2) {
        if (a[g1] <= a[g2]) {
            temp[i++] = a[g1++];
        }
        else {
            temp[i++] = a[g2++];
        }
    }
    while (g1 <= m1 && g3 <= r) {
        if (a[g1] <= a[g3]) {
            temp[i++] = a[g1++];
           
        }
        else {
            temp[i++] = a[g3++];
          
        }
    }
    while (g2 <= m2 && g3 <= r) {
        if (a[g2] <= a[g3]) {
            temp[i++] = a[g2++];  
        }
        else {
            temp[i++] = a[g3++];
        }
        
    }
    //suppose only one group has exist data unording
    while (g1 <= m1) {
        temp[i++] = a[g1++];
    }
    while (g2 <= m2) {
        temp[i++] = a[g2++];
    }
    while (g3 <= r) {
        temp[i++] = a[g3++];
    }
   

    //copy data from temp array to array. 
    int k = 0;
    for (k = l; k <= r; k++) {
        a[k] = temp[k];
    }
    delete[] temp; //deallocate memory
}

void ThreeMergeSort(int array[], int left, int right) {
    if(left >= right){
        return;
    }
    int mid1 = left + (right - left) / 3;
    int mid2 = right - (right - left) / 3;
    ThreeMergeSort(array, left, mid1);
    ThreeMergeSort(array, mid1 + 1, mid2);
    ThreeMergeSort(array, mid2 + 1, right);
    ThreeMerge(array, left, mid1, mid2, right);
}


int main() {
    string file_name;
    ofstream out("sorted.txt");
    ifstream file;
    int data;
    int count = 0;
    int* m = nullptr;
    
    //Reading data in a file
    do {
        cout << "Please enter a file name";
        cout << "that you want to sort: ";
        cin >> file_name;
        file.open(file_name.c_str());
        if (!file) {
            cout << "Sorry,we can't find your file, please enter again." << endl;
        }
    } while (!file);
    while (file >> data) {
        count++;
    }
    m = new int[count+5];
    count = 0;
    file.close();
    file.open(file_name.c_str());

    while (file >> data) {
        m[count] = data;
        count++;
    }
    

    //Output the result file
    cout << "Reading file....." << endl;
    cout << endl;
    cout << "Three-way sort DONE " << endl;
    cout << "The result of sort SHOW on the sorted.txt file." << endl;
    ThreeMergeSort(m, 0, count-1);
    out << "Sort Done: " << endl;
    for (int i = 0; i < count; i++) {
        out << m[i] << endl;
    }
    cout << endl;
    out.close();
    file.close();

    delete[] m; //deallocate memory

    return 0;
}
