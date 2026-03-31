#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits> 

using namespace std;

vector<int> two_way_merge(vector<int>* a, vector<int>* b){
    vector<int> result;

    //indeksa najmanjših elementov v četah
    int i = 0, j = 0;

    //če se zgodi, da v kateri od čet "zmanjka" elementov, zaradi delne urejenosti samo
    //prekopiram elemente druge čete
    while(i < (*a).size() && j < (*b).size()){
        if((*a)[i] <= (*b)[j]){
            result.push_back((*a)[i]);
            i++;
        } else {
            result.push_back((*b)[j]);
            j++;
        }
    }

    //če se najprej sprazni b, prekopiram a
    while(i < (*a).size()){
        result.push_back((*a)[i]);
        i++;
    }

    //če se najprej sprazni a, prekopiram b
    while(j < (*b).size()){
        result.push_back((*b)[j]);
        j++;
    }

    /*cout << "two_way_merge: ";
    for(int j = 0; j < result.size(); j++){
        cout << result[j];
        if(j != result.size() - 1) cout << " ";
    }
    cout << endl;*/

    return result;
}

vector<int> k_way_recursive(int l, int r, vector<vector<int>>* t){
    if(l == r) return (*t)[l];
    if (l > r) return {};

    int mid = (l + r) / 2;

    vector<int> left = move(k_way_recursive(l, mid, t));
    /*cout << "k_way_recursive left (l: " << l << ", r: " << mid << "): ";
    for(int i = 0; i < left.size(); i++){
        cout << left[i];
        if(i != left.size() - 1) cout << " ";
    }
    cout << endl;*/

    vector<int> right = move(k_way_recursive(mid + 1, r, t));
    /*cout << "k_way_recursive right (l: " << mid+1 << ", r: " << r << "): ";
    for(int i = 0; i < right.size(); i++){
        cout << right[i];
        if(i != right.size() - 1) cout << " ";
    }
    cout << endl;*/

    return two_way_merge(&left, &right);
}

vector<vector<int>> k_way_merge(int k, vector<vector<int>>* t){
    vector<vector<int>> result;

    int t_size = (*t).size();
    
    int start = 0;
    int finish = k - 1;

    //zlivanj bo natanko št. čet / k
    for(int i = 0; i < t_size / k; i++){
        result.push_back(move(k_way_recursive(start, finish, t)));
        start += k;
        finish += k;
    }

    if(t_size % k != 0){
        result.push_back(move(k_way_recursive(start, t_size - 1, t)));
    }

    /*cout << "k_way_merge: ";
    for(int j = 0; j < result.size(); j++){
        for(int l = 0; l < result[j].size(); l++){
            cout << result[j][l];
            if(l != result[j].size() - 1) cout << " ";
        }
        if(j != result.size() - 1) cout << " ";
    }
    cout << endl;*/

    return result;
}

int main(){
    //število elementov zaporedja, število čet za sočasno zlivanje, število korakov
    int n, k, a;
    cin >> n >> k >> a;

    //vektor čet, ki so predstavljene kot vektorji elementov
    vector<vector<int>> t;
    t.push_back(vector<int>());

    //index trenutnega podseznama - čete
    int ceta = 0;

    //zadnji element
    int last_in = 0;

    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;

        if(temp < last_in){
           ceta++; 
           t.push_back(vector<int>());
        } 

        t[ceta].push_back(temp);
        last_in = temp;
    }

    /*for(int i = 0; i < t.size(); i++){
        for(int j = 0; j < t[i].size(); j++){
            cout << t[i][j] << " ";
        }
        cout << endl;
    }*/

    //uejanje po korakih
    for(int i = 0; i < a; i++){
        t = move(k_way_merge(k, &t));
        /*cout << "trenuten korak: ";
        for(int j = 0; j < t.size(); j++){
            for(int l = 0; l < t[j].size(); l++){
                cout << t[j][l];
                if(l != t[j].size() - 1) cout << " ";
            }
            if(j != t.size() - 1) cout << " ";
        }
        cout << endl;*/
    }

    //cout << "končni izpis: ";
    for(int i = 0; i < t.size(); i++){
        for(int j = 0; j < t[i].size(); j++){
            cout << t[i][j];
            if(j != t[i].size() - 1) cout << " ";
        }
        if(i != t.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}