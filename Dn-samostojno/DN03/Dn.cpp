#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

void print(vector<int> &sez){
    for(int i = 0; i < sez.size(); i++) cout << sez[i] << " ";
    cout << endl;
}

bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

int vidljivost(priority_queue<PII, vector<PII>, bool(*)(pair<int,int>, pair<int,int>)> &p, priority_queue<PII, vector<PII>, bool(*)(pair<int,int>, pair<int,int>)> &q, int k, int k_el, int n){
    if(!q.empty()){
        pair<int, int> t = q.top();
        p.push(t);
        q.pop();
    }

    int res = n - 1;
    int max_left;
    bool left = false;
    int max_right;
    bool right = false;
    while(!p.empty()){
        pair<int, int> tren = p.top();
        //visina trenutnega neboticnika
        int v = tren.first;
        //lokacija trenutnega neboticnika
        int l = tren.second;
        p.pop();
        q.push(tren);
        if(v > k_el && l < k && !left){
            res = res - (l+1);
            max_left = l;
            left = true;
        } else if(v > k_el && l < k && l > max_left){
            res = res - (l - max_left);
        } else if(v > k_el && l > k && !right){
            res = res - (n-l);
            max_right = l;
            right = true;
        } else if(v > k_el && l > k && max_right > l){
            res = res - (max_right - l);
        } else if(v <= k_el) break;
        //cout << res << " ";
    }

    return res;
}

int main(){
    //stevilo neboticnikov
    int n; 
    cin >> n;

    vector<int> neboticniki(n);
    for(int i = 0; i < n; i++) cin >> neboticniki[i];
    //print(neboticniki);

    priority_queue<PII, vector<PII>, bool(*)(pair<int,int>, pair<int,int>)> p(cmp);
    priority_queue<PII, vector<PII>, bool(*)(pair<int,int>, pair<int,int>)> q(cmp); 

    for(int i = 0; i < n; i++){
        p.push({neboticniki[i], i});
    }

    int sum = 0;
    for(int i = 0; i < n; i++){
        if(i%2==0) sum += vidljivost(p, q, i, neboticniki[i], n);
        else sum += vidljivost(q, p, i, neboticniki[i], n);
        //cout << sum << endl;
    }
    cout << sum << endl;

    return 0;
}