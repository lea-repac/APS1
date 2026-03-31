#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
typedef pair<int,int> PII;

void dijkstra(vector<vector<pair<int, int>>>& graph, int start, vector<int> &distance, vector<int> &previous) {
    int n = graph.size();
    distance = vector<int>(n,-1);
    previous = vector<int>(n,-1);
    priority_queue<PII, vector<PII>, greater<PII>> pq;

    distance[start] = 0; 
    pq.push({0,start});

    while (!pq.empty()) {
        auto [d,x] = pq.top();
        pq.pop();
        
        if (distance[x] != d) continue;  // ignore old values
        
        for (auto [y,w] : graph[x]) {  // update neighbors
            int d = distance[x]+w;
            if (distance[y] == -1 || d < distance[y]) {
                distance[y] = d;
                previous[y] = x;
                pq.push({d,y});
            }
        }
    }
}

vector<vector<PII>> remove_povezava(vector<vector<PII>>& graph, int u, int v) {
    vector<vector<PII>> new_graph = graph;

    //odstranim u->v
    new_graph[u].erase(
        //premaknem vse elemente, ki ne ustrezajo pogoju 
        remove_if(new_graph[u].begin(), new_graph[u].end(),
        [&](PII& e){ return e.first == v; }), new_graph[u].end());

    //odstranim v->u
    new_graph[v].erase(remove_if(new_graph[v].begin(), new_graph[v].end(),
        [&](PII& e){ return e.first == u; }), new_graph[v].end());

    return new_graph;
}


int main(){
    //število vozlišč, število povezav
    int n, m;
    cin >> n >> m;

    //vektor, ki hrani za vsako vozlišče, njegove sosede in utež povezave 
    vector<vector<PII>> graph(n);

    for(int i = 0; i < m; i++){
        //vozlišče, sosed, utež
        int v, s, u;
        cin >> v >> s >> u;
        graph[v].push_back({s, u});
        graph[s].push_back({v, u});
    }
    
    //najdem najkrajšo pot
    vector<int> distance, previous;
    dijkstra(graph, 0, distance, previous);

    //če že najkrajša pot ne obstaja, potem izpišem -1
    if(distance[n-1] == -1){
        cout << "-1" << endl;
        return 0;
    }

    //rekonstruiram najkrajšo pot
    vector<int> path;
    for(int v = n - 1; v != -1; v = previous[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    
    int second = -1;

    //za vsako povezavo na najkrajši poti začasno odstranim to povezavo in najdem novo najkrajšo pot, tako pridobljene pa primerjam med seboj (aka Yennov algoritem)
    for(int i = 0; i < (int) path.size() - 1; i++){
        //vozlišči "na" povezavi
        int v = path[i];
        int u = path[i+1];    
    
        //odstranim povezavo
        vector<vector<PII>> graph_mod = remove_povezava(graph, u, v);
        //najdem novo najkrajšo pot
        vector<int> distance1, previous1;
        dijkstra(graph_mod, 0, distance1, previous1);
        
        //ni poti
        if(distance1[n-1] == -1) continue;
        //več najkrajših poti
        if(distance1[n-1] == distance[n-1]){
            second = distance[n-1];
            break;
        } else if(second == -1 || distance1[n-1] < second){
            second = distance1[n-1];
        }
    }

    //preverim ali imamo res drugo najkrajšo pot
    if(second == -1){
        cout << "-1" << endl;
        return 0;
    } else {
        cout << second << endl;
    }
    return 0;
}