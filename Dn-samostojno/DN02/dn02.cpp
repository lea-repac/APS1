//APSTester ima drugačen izpis, namesto " " med elementi je "\n"



#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
typedef vector<int> VI;

void print(vector<VI> &sez) {
    for (int i = 0; i < sez.size(); i++){
        for(int j = 0; j < sez[i].size(); j++) cout << sez[i][j] << " ";
    }
    cout << endl;
}

void print(vector<int> &sez) {
    for (int i = 0; i < sez.size(); i++){
        cout << sez[i] << " ";
    }
    cout << endl;
}

void k_way_merge(vector<VI> &sez, int k){
    int n = sez.size();

    vector<VI> res;
    vector<int> temp; 

    int i = 0;

    while(i < n - n%k){
        for(int m = 0; m < sez[i].size(); m++){
            temp.push_back(sez[i][m]);
        } 
        if(i%k == k-1){
            sort(temp.begin(), temp.end());
            res.push_back(temp);
            temp = vector<int>();
        }
        i++;
    }

    for(int j = i; j < n; j++){
        for(int m = 0; m < sez[j].size(); m++) temp.push_back(sez[j][m]);
        if(j == n-1){
            sort(temp.begin(), temp.end());
            res.push_back(temp);
        }
    }
    
    sez = move(res);
}


int main(){
    //količina podatkov, k-zlivanje, število korakov
    int n, k, a;
    cin >> n >> k >> a;

    vector<VI> sez;
    vector<int> temp;
    int prev = 0;
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        
        if(t < prev){
            sez.push_back(temp);
            //print(sez);
            temp = vector<int>();
            temp.push_back(t);
            prev = t;
        } else {
            temp.push_back(t);
            prev = t;
        }
    }
    sez.push_back(temp);


    for(int i = 0; i < a; i++){
        k_way_merge(sez, k);
        if(sez.size() == 1) break;
    }
    print(sez);

    return 0;
}