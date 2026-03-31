#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

void print(vector<pair<int, int>> &sez) {
    for (auto [a, b] : sez) cout << a << " " << b << "\n";
    cout << endl;
}

vector<pair<int, int>> merge(vector<pair<int, int>> &s){
    vector<pair<int, int>> merged; 
    
    pair<int, int> temp = s[0];
    for(int i = 1; i < s.size(); i++){
        if(temp.second >= s[i].first) temp.second = max(s[i].second, temp.second);
        else{
            merged.push_back(temp);
            temp = s[i];
        }
    }

    merged.push_back(temp);
    //print(merged);
    return merged;
}

int unlighted(vector<pair<int, int>> &s, int m){
    int un = 0;
    int n = s.size();

    //preverimo levi rob
    if(s[0].first > 0) un += s[0].first;
    //najdemo vse dele ceste, kjer se intervali ne pokrivajo
    for(int i = 1; i < n; i++){
        if(s[i-1].second < s[i].first) un += (s[i].first - s[i-1].second);
    }
    //preverimo desni rob
    if(s[n-1].second < m) un += (m - s[n-1].second);
    return un;
}

int main(){
    //imamo m dolgo ulico z n svetilkami
    int n, m;
    cin >> m >> n;

    //ni svetilk na ulici - vse je neosvetljeno
    if(n == 0){
        cout << m << endl;
        return 0;
    }

    //intervali, ki so osvetljeni
    vector<pair<int, int>> intervals;
    
    for(int i = 0; i < n; i++){
        //x je lokacija svetilke, d pa domet v eno stran
        int x, d;
        cin >> x >> d;
        //svetilka ne dela
        if(d == 0) continue;

        int left = max(0, x - d);
        int right = min(m, x + d);

        if(left < right) intervals.push_back({left, right});
    }
    //print(intervals);
    
    //ni osvetljenih intervalov
    if(intervals.empty()){
        cout << m << endl;
        return 0;
    }

    //uredimo intervale po začetkih intervala
    sort(intervals.begin(), intervals.end());
    vector<pair<int, int>> merged = merge(intervals);

    //število neosvetljenih metrov
    cout << unlighted(merged, m) << endl;
    return 0;
}