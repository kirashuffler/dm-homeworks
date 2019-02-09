#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool BFS(int** ResNet,int &n, vector <int> &path){
    vector < vector<int> > g(n);
    for(int u = 0; u < n; ++u)
        for(int v = 0; v <n; ++v)
            if (ResNet[u][v] > 0)
                g[u].push_back(v);
           /* else if(ResNet[u][v] < 0)
                g[v].push_back(u);*/
    queue <int> q;
    q.push (0);
    vector <bool> used (n);
    vector <int> p(n);
    used[0] = true;
    p[0] = -1;
    while (!q.empty()){
        int now = q.front();
        q.pop();
        for( size_t i = 0; i < g[now].size(); ++i){
            int to = g[now][i];
            if (!used[to]){
                used[to] = true;
                q.push (to);
                p[to] = now;
            }
        }
    }
    if (!used[1])
        return false;
    else {
        for (int v = 1; v != -1; v = p[v])
            path.push_back (v);
        reverse(path.begin(), path.end());
    }
    return true;
}

void PrintM(int** M, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j)
            cout << M[i][j] << " ";
        cout << endl;
    }
}


int** MaxFlowFinder(int** ResNet, int n){// returns pointer on 2d array which contains maxflow of Residual Network, don't forget delete this array after using 
    vector <int> path;
    int ** Flow = new int* [n];
    for (int i = 0; i < n; ++i)
        Flow[i] = new int[n];
    for (int u = 0; u < n; ++u)
         for (int v = 0; v < n; ++v)
            Flow[u][v] =0;   
    while(BFS(ResNet, n, path)){
        int min = ResNet[path[0]][path[1]];
        for (int i = 1; i < path.size() - 1; ++i)
            if (min > ResNet[path[i]][path[i + 1]])
                min = ResNet[path[i]][path[i + 1]];
        for (int i = 0; i < path.size()-1; ++i){
            int u = path[i], v = path[i + 1];
            Flow[u][v] += min;
            Flow[v][u] = -Flow[u][v]; 
            ResNet[u][v] -= min;
            ResNet[v][u] += min;
        }
        path.clear();
    }
    return Flow;
}

int FlowsCapacity(int** Flow, int n){
    int Capacity = 0;
    for (int i = 0; i < n; ++i)
        Capacity += Flow[0][i];
    return Capacity;
}
