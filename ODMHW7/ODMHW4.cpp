#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
using namespace std;

bool BFS(vector < vector<int> >& g, int &s, vector <bool> &used, vector <bool> &is_black){
    queue <int> q;
    q.push (s);
    used[s] = true;
    while (!q.empty()){
        int now = q.front();
        q.pop();
        for( size_t i = 0; i < g[now].size(); ++i){
            int to = g[now][i];
            if (!used[to]){
                used[to] = true;
                if (is_black[now])
                    is_black[to] = false;
                else
                    is_black[to] = true;
                q.push (to);
            }
            if (used[to])
                if (is_black[now] == is_black[to])
                    return false;
        }
    }
    return true;
}

bool is_dual(int** G, int n){
    vector <bool> is_black (n, true);
    vector <bool> used (n, false);
    vector < vector<int> > g(n);
    for(int u = 0; u < n; ++u)
        for(int v = 0; v <n; ++v){
            if (G[u][v] > 0)
                g[u].push_back(v);
        }
    for (int i = 0; i < n; ++i)
        if (used[i])
            continue;
        else
            if (!BFS(g, i, used, is_black)){
                return false;
            }
    return true;
}
    
