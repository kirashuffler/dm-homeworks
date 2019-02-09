#include <iostream>
#include <fstream>
#include "FFMethod.cpp"
#include <vector>
#define INT_MAX
void CopyV(vector <int> v1, vector <int> &v2){
    for (int i = 0; i < v1.size(); ++i)
        v2.push_back(v1[i]);
}
int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "kek";
        return 0;
    }
    ifstream f(argv[1]);
    ifstream answer(argv[2]);
    int n;
    f >> n;
    int** g = new int*[n];
    for (int i = 0; i < n; ++i)
        g[i] = new int [n];
    for (int u = 0; u < n; ++u)
        for(int v = 0; v < n; ++v)
           f >> g[u][v];
    vector<int> maxpath;
    vector<int> path;
    int mu, mv;
    int max = 0;
    int count = 0;
    while (BFS(g, n, path)){
        count++;
        mu = path[0];
        mv = path[1];
        int min = g[mu][mv];
        for (int i = 1; i < path.size() - 1; ++i)
            if (g[path[i]][path[i + 1]] < min){
            min = g[path[i]][path[i + 1]];
            mu = path[i];
            mv = path[i + 1];
            }
        if (min > max){
         /*   maxpath.clear();    
            CopyV(path, maxpath);*/
            max = min;
        }
        g[mu][mv] = 0;
        path.clear();
        cout << count << endl;
    }
    /*for (int i = 0; i < maxpath.size(); ++i)
        cout << maxpath[i] << " ";*/
    int ans;
    answer >> ans;
    if (max == ans)
        cout << "YES" << endl;
    else 
        cout << "NO" << endl;
    cout << max;
    return 1;
}
