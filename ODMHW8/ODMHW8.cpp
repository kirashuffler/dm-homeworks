#include <iostream>
#include "FFMethod.cpp"
#include <fstream>
#include <climits>
#include <string.h>
using namespace std;
int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "incorrect input parameters";
        return 0;
    }
    ifstream f(argv[1]);
    ifstream answer(argv[2]);
    int ans;
    answer >> ans; 
    int m, n;
    f >> m >> n;
    int mSize = 2 + m + n;
    int** g = new int* [mSize];
    for (int i = 0; i < mSize; ++i)
        g[i] = new int [mSize];
    for (int i = 2; i < m + 2; ++i){
        int a;
        f >> a;
        g[0][i] = a;
    }
    for (int i = m + 2; i < mSize; ++i){
        int b;
        f >> b;
        g[i][1] = b;
    }

    for (int u = 2; u < m + 2; ++u)
        for (int v = m + 2; v < mSize; ++v)
            g[u][v] = INT_MAX;
    int** MaxFlow = MaxFlowFinder(g, mSize);
    int ** res = new int* [m];
    for (int i = 0; i < m; ++i)
        res[i] = new int [n];
    int sum = 0;
    for (int a = 0; a < m; ++a){
        for (int b = 0; b < n; ++b){
            res[a][b] = MaxFlow[a + 2][m + 2 + b];
            sum += res[a][b];
        }
    }
    if (sum == ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    delete g;
    delete MaxFlow;
    delete res;
    return 0;
}

