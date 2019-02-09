#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FFMethod.cpp"
using namespace std;

int main(int argc, char* argv[])
{   
    if (argc < 2){
        cout << "incorrect input parameters" << endl;
        return 0;
    }
    ifstream f(argv[1]);
    ifstream answer(argv[2]);
	int n;
	f >> n;
	string w;
	f >> w;
	vector<string> cubes(n);
	for(int i = 0; i < n; ++i)
		f >> cubes[i];
	const int V = 2 + w.size() + n;
	//vector<vector<int> > m(V, vector<int>(V));
    int** m = new int* [V];
    for (int i = 0; i < V; ++i)
        m[i] = new int[V];
	// connecting 0
	for(int i = 0; i < w.size(); ++i)
		m[0][2 + i] = 1;
	// connecting 1
	for(int i = 0; i < cubes.size(); ++i)
		m[V - 1 - i][1] = 1;
	// connecting slovo -> kubiki =)
	for(int i = 0; i < w.size(); ++i)
		for(int k = 0; k < cubes.size(); ++k)
			if(cubes[k].find(w[i]) != string::npos){
				m[2 + i][2 + w.size() + k] = 1;
                m[2 + w.size() + k][2 + i] = 1;
            }
    int** MaxFlow = MaxFlowFinder(m, V);
    int sum = 0;
    for (int i = 0; i < V; ++i)
        sum += MaxFlow[0][i];
    string res;
    if (sum != w.size())
        res = "NO";
    else
        res = "YES";
    string ans;
    answer >> ans;
   if (res == ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    delete m;
    delete MaxFlow;
    return 1;
}













