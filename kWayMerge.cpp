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


//--------------------------------------------------------------------//
// a helper function to find the min element of a vector of ints      //
//--------------------------------------------------------------------//
int ArgMin(vector< pair< int, int >> M)
{
    int l = 0;
    for(int i = 0; i < M.size() ; ++i){
	    if ( M[i].first < M[l].first) l = i;
    }
    return l;
}

//-----------------------------------------//
// a helper function to print arrays       //
//-----------------------------------------//
void print(std::vector <int> const &a) 
{
    for(int i=0; i < a.size(); i++)
        std::cout << a.at(i) << " ";
    cout << endl;
}

//-----------------------------------------//
// splits A into k sub-arrays              //
//-----------------------------------------//
vector<vector<int>> split(const vector<int> & A, int k)
{
	vector<vector<int>> Aj;
	int q = A.size() / k;
	int r = A.size() % k;
	int idx = 0;

	for( int i = 0; i < r ; ++i){
		vector<int> sub;
		for( int j = 0; j <= q ; ++j){
			sub.push_back(A.at(idx));
			idx++;
		}
		Aj.push_back(sub);
	}

	for ( int l = r; l < k; ++l ){
		vector<int> sub;
	       for ( int r = 0; r < q ; ++r){
	       		sub.push_back(A.at(idx));
			idx++;
	       }
	       Aj.push_back(sub);
	}
return Aj;		
}

//-------------------------------------------------//
// k-way merge implemented as in the assignment    //
// if all Aj's are sorted, the output must be      //
// sorted as well                                  //
//-------------------------------------------------//
vector<int> kWayMerge(const vector<vector<int>> & Aj)
{
	int I[Aj.size()];
	int n = 0;
	for( int k = 0; k < Aj.size(); ++k) n += Aj[k].size();
	vector<int> A(n, 0);
	for ( int i = 0 ; i < n ; ++i){
		vector<pair<int, int>> M;
		for( int y = 0; y < Aj.size(); y++){
			if( I[y] != Aj[y].size()) M.push_back(make_pair(Aj[y][I[y]], y));
		}
		int l = ArgMin(M);
		int j = M[l].second;
		A[i] = Aj[j][I[j]];
		I[j] += 1;
	}
	return A;
}

//-----------------------------------------//
// mergesort                               //
//-----------------------------------------//
void kWayMergeSort(vector<int> & A, int k, int& total_num_calls)
{
	total_num_calls++;
	if (k <= 0) return;
	vector<vector<int>> Aj = split(A,k);
	for(int j = 0; j < k; ++j){
		if( Aj[0].size() == 1 ) break;
		kWayMergeSort(Aj.at(j) , k, total_num_calls);
	}
	A = kWayMerge(Aj);
}

int main()
{
	int k;
	int q;
	vector<int> A;

	cin >> k;
	// read array A from standard input
	while (cin >> q) A.push_back(q);
	auto start = get_time::now(); //use auto keyword to minimize typing strokes :)

	int total_num_calls = 0;
	kWayMergeSort(A, k, total_num_calls);

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

