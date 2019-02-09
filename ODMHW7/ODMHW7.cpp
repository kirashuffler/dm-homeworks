#include "FFMethod.cpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "kek";
        return 0;
    }
    ifstream f(argv[1]);
    ifstream answer(argv[2]);
    int n, m;
    f >> n >> m;
    int mSize = n + m + 2;
    int** g = new int* [mSize];
    for (int i = 0; i < mSize; ++i)
        g[i] = new int[mSize];
    for (int i = 0; i < n; ++i){
        g[0][i + 2] = 1;
    }
    for (int i = n + 2; i < mSize; ++i){
        g[i][1] = 1;
    }
    for (int i = 0; i < n; ++i){
        int count;
        f >> count;
        for (int j = 0; j < count; ++j){
            int v;
            f >> v;
            g[i + 2][v + n + 2] = 1;
            g[v + n + 2][i + 2] = 0;
        }
    }
    //PrintM(g, mSize);
    int** MaxFlow = MaxFlowFinder(g, mSize);
    PrintM(g, mSize);
    int maxPairs = 0;
    for (int i = 0; i < mSize; ++i)
        maxPairs += MaxFlow[0][i];
    int ans;
    answer >> ans;
   /* cout << maxPairs << ' ' << ans;*/
   if (maxPairs == ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    delete MaxFlow;
    delete g;
}
