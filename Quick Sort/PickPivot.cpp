/*
* Name: Maiqi Hou
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int Partition(int a[], int left, int right, int& count) {
    //This implemention according to the lecture 3.1
    count += (right - left);
    int p = a[left];
    int i = left + 1;
    for (int j = left + 1; j <= right; j++) {
        if (a[j] < p) {
            swap(a[i], a[j]);
            i++;
        }
    }
    swap(a[left], a[i - 1]);
    return i - 1;
}
int lPartition(int a[], int left, int right, int& count) {
    count += (right - left);
    int p = a[right];
    int i = left;
    for (int j = left; j <= right - 1; j++) {
        if (a[j] < p) {
            swap(a[i], a[j]);
            i++;
        }
    }
    swap(a[right], a[i]);
    return i;
}


//FIRST element of array as the pivot element.
int First_Pivot(int a[], int left, int right, int & count) {
    return Partition(a, left, right, count);
}

//LAST element of array as the pivot element.
int Last_Pivot(int a[], int left, int right, int & count) {
    swap(a[right], a[left]);
    return Partition(a, left, right, count);
}

//Random element of array as the pivot element.
int Random_Pivot(int a[], int left, int right, int& count) {
    int random =rand()%(right-left+1)+left; // Random pviot
    swap(a[random], a[left]);
    return Partition(a, left, right, count);
}

//Median of three pivot elemment
int MedianThree_Pivot(int a[], int left, int right, int& count) {
    int l = (right - left + 1);
    int mid = ((right - left + 1) / 2)+left;
    if (l % 2 == 0) {
        mid -= 1;
    }

    if ((a[left] < a[mid] && a[mid] < a[right]) 
        || (a[right] < a[mid] && a[mid] < a[left])) {
        swap(a[mid], a[left]);
    }
    if ((a[left] < a[right] && a[right] < a[mid]) 
        || (a[mid] < a[right] && a[right] < a[left])) {
        swap(a[right], a[left]);
    }
    return Partition(a, left, right, count);
}

void QuickSort(int array[], int left, int right, string c, int &count) {
    if (left < right) {
        int pviot = 0;
        if (c == "F") {
            pviot = First_Pivot(array, left, right, count);
        }
        else if (c == "L") {
            pviot = Last_Pivot(array, left, right,count);
        }
        else if (c == "R") {
            pviot = Random_Pivot(array, left, right,count);
        }
        else if (c == "M") {
            pviot = MedianThree_Pivot(array, left, right, count);
        }
        QuickSort(array, left, pviot-1, c, count);
        QuickSort(array, pviot+1, right, c, count);
    } 
}


int main() {
    const int Max = 10000;
    int* aF = new int[Max];
    int* aL = new int[Max];
    int* aR = new int[Max];
    int* aM = new int[Max];
    int cF = 0;
    int cL = 0;
    int cR = 0;
    int cM = 0;
    char a;
    ifstream file;
    ofstream out1, out2, out3, out4;
    out1.open("FirstPivot_QS.txt");
    out2.open("LastPivot_QS.txt");
    out3.open("RandomPivot_ QS.txt");
    out4.open("MedianThree_QS.txt");
 
    cout << "Please choose a file that you want to read " << endl;
    cout << "1. QuickSort10k.txt\n";
    cout << "2. QuickSort10kR.txt\n";
    cout << "3. QuickSort10Semi2K.txt\n";
    cout << "4. QuickSort10Semi4K.txt\n";
    cout << "(Enter 1 - 4) :";
    cin >> a;
    
    if (a == '1') {
        file.open("QuickSort10k.txt");
    }
    if (a == '2') {
        file.open("QuickSort10kR.txt");
    }
    if (a == '3') {
        file.open("QuickSort10kSemi2k.txt");
    }
    if (a == '4') {
        file.open("QuickSort10kSemi4k.txt");
    }

    for (int i = 0; i < Max; i++) {
        file >> aF[i];
        aM[i] = aR[i] = aL[i] = aF[i];
    }
    file.close();
    QuickSort(aF, 0, Max - 1, "F", cF);
    QuickSort(aL, 0, Max - 1, "L", cL);
    QuickSort(aR, 0, Max - 1, "R", cR);
    QuickSort(aM, 0, Max - 1, "M", cM);

    for (int i = 0; i < Max; i++) {
        out1 << aF[i] << endl;
        out2 << aL[i] << endl;
        out3 << aR[i] << endl;
        out4 << aM[i] << endl;
    }
    out1.close();
    out2.close();
    out3.close();
    out4.close();
    cout << endl << "Quick Sort is processing........." << endl;
    cout << "Done!" << endl << endl;
    cout << "QuickSort10k.txt comparisons: (From low to high)" << endl;

    if (cM < cR) {
        cout << "Median Three as pivot:   " << cM << endl;
        cout << "Random element as pivot: " << cR << endl;
    }
    else {
        cout << "Random element as pivot: " << cR << endl;
        cout << "Median Three as pivot:   " << cM << endl;

    }
    if (cF < cL) {
        cout << "First element as pivot:  " << cF << endl;
        cout << "Last element as pivot:   " << cL << endl;
        
    }
    else {
        cout << "Last element as pivot:   " << cL << endl;
        cout << "First element as pivot:  " << cF << endl;
    }
    cout << endl;

    cout << "The result of Quick Sort show in files, Please Check ^_^" << endl;
    delete[]aF;
    delete[]aL;
    delete[]aR;
    delete[]aM;

    return 0;
}