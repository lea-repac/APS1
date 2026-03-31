#include <bits/stdc++.h>

using namespace std;
typedef vector<pair<int,int>> VII;
const int INF = numeric_limits<int>::max();

void dijkstra(vector<vector<int>> &graph, int start, vector<int> &distance, vector<int> &previous){
    int n = graph.size();  //n+1
    distance = vector<int>(n, INF); 
    previous = vector<int>(n, -1);
    vector<bool> used(n, false);

    distance[start] = 0;

    for(int it = start; it < n; it++){
        int x = -1;
        int best = INF;
        for(int i = start; i < n; i++){
            if(!used[i] && distance[i] < best){
                best = distance[i];
                x = i;
            } 
        }

        if (x == -1) break;
        used[x] = true;

        for (int y = start; y < n; ++y) {
            if (used[y]) continue;
            int w = graph[x][y];
            if (distance[x] + w < distance[y]) {
                distance[y] = distance[x] + w;
                previous[y] = x;
            }
        }
    }
}

int premer(int n, vector<vector<int>> &graph){
    vector<int> distance, previous;
    int longest = 0;

    for(int i = 1; i <= n; i++){
        dijkstra(graph, i, distance, previous);
        for(int j = i+1; j <= n; j++){
            if(longest < distance[j]) longest = distance[j];
        }
    } 

    return longest;
}

int main(){
    //graf je poln in neusmerjen
    //število vozišč v grafu, število spreminjanj grafa
    int n, k;
    cin >> n >> k;

    //n+1, ker začnemo oštevilčiti vozlišča z 1
    vector<vector<int>> graph(n+1, vector<int>(n+1));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> graph[i][j];
        }
    }
    
    //vektor rezultatov
    vector<int> res(k+1);
    //prvi graf - brez sprememb
    res[0] = premer(n, graph);

    //vsakič nov graf, ko nastopijo spremembe
    for(int i = 0; i < k; i++){
        int v, u, change;
        cin >> v >> u >> change;
        graph[v][u] = change;
        graph[u][v] = change;

        res[i+1] = premer(n, graph);
    }
    
    //izpis
    for(int i = 0; i < k+1; i++) cout << res[i] << endl;

    return 0;
}