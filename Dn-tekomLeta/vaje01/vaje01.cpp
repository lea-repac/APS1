#include  <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //stevilo oseb
    int n;
    cin >> n;
    
    //stevilo najstarejsih
    int old;
    cin >> old;

    //seznam oseb - parov
    vector<pair<string, int>> people;
    for(int i = 0; i < n; i++){
        pair<string, int> temp;
        cin >> temp.first >> temp.second;
        people.push_back(temp);
    }

    //urejanje po padajoči starosti - bubble sort
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1; j++){
            if(people[j].second < people[j + 1].second) swap(people[j], people[j + 1]);
        }
    }

    //seznam imenov starejših oseb
    vector<string> names;
    for(int i = 0; i < old; i++){
        //indeks para v seznamu people, katerega ime bo na indeksu i v seznamu names
        names.push_back(people[i].first);
    }

    sort(names.begin(), names.end());

    for(string x : names) cout << x << endl;
    cout << flush;

    return 0;
}