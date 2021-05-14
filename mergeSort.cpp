#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <iostream>
#include <chrono>
#include <assert.h>
#include <math.h>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock;


void merge(vector<int> &A, int l, int r, int m)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int a1[n1];
    int a2[n2];

    //2 temp arrays
    for( int i = 0; i < n1; ++i ) a1[i] = A[l + i];
    for( int j = 0; j < n2; ++j ) a2[j] = A[m + 1 + j];

    int k = 0, p = 0, n = l;

    //Actual merge
    while(k < n1 && p < n2) {
        if (a1[k] <= a2[p]) {
            A[n] = a1[k];
            k++;
        }
        else {
            A[n] = a2[p];
            p++;
        }
        n++;
    }

    //incase left over in either array
    while( k < n1 ) {
        A[n] = a1[k];
        n++;
        k++;
    }

    while( p < n2 ) {
        A[n] = a2[p];
        n++;
        p++;
    }
}


void mergeSort(vector<int> &A, int l, int r, int&total_num_calls)
{
    total_num_calls++;
    if ( r <= l ) return;
    int m = l + (r - l) / 2;
    mergeSort(A, l, m, total_num_calls);
    mergeSort(A, m + 1, r, total_num_calls);
    merge(A, l, r, m);
}

//--------------------------------------------//
// helper function to generage a random array //
//--------------------------------------------//

void getRandomArray(vector<int>& A, int n)
{
    for (unsigned int i = 0; i < n; i++)
        A.push_back((int) rand() * (int) rand() * (int) rand());
}


int main()
{

    int n = 10000;
    vector<int> A;

    // for tests on a random array, set this variable to false
    bool read_input_from_cin = true;
    
    if (read_input_from_cin)
    {
        int q;
        // read array A from standard input
        while(cin >> q)
            A.push_back(q);
    }
    else {
        getRandomArray(A, n);
    }

    
    auto start = get_time::now(); //use auto keyword to minimize typing strokes :)

    int total_num_calls = 0;
    mergeSort(A, 0, A.size() - 1, total_num_calls);
 
    auto end = get_time::now();
    auto diff = end - start;

    
    bool sorted = true;
    // print re-arranged A  to standard output    
    cout << A[0] << endl;
    for (int i = 1; i < A.size(); i++)
    {
        cout << A[i] << endl;
        if (A[i] < A[i - 1])
            sorted = false;       
    }
    
     cout << total_num_calls << endl;
        
    // uncomment this line to have running time printed to the standard output
    //cout << "Time to sort: " <<  chrono::duration <double, milli>(diff).count() << " ms" << endl;

    return 0;

}