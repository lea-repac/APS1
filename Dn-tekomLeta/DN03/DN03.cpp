#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    //stevilo neboticnikov
    int n;
    cin >> n;

    vector<int> ulica;
    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        ulica.push_back(temp);
    }

    sort(ulica.begin(), ulica.end(), greater<int>());

    //overall vsota
    int z = 0;
    int last = 0;
    int last_zn = 0;
    for(int i = 0; i < n; i++){
        //trenutna vsota
        int zn = 0;
        if(ulica[i] == last){
            z += last_zn;
        } else {
            for(int j = i+1; j < n; j++){
                if(ulica[i] >= ulica[j] && j != i) zn++;
            }
            z += zn;
            last_zn = zn;
        }
        last = ulica[i];
    }

    cout << z << endl;

    return 0;
}