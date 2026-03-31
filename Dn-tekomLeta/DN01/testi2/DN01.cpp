#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    //dolžina ulice
    int m;
    //število luči
    int n;

    cin >> m >> n;

    if(n == 0){
        cout << m << endl;
        return 0;
    }
    
    //vektor, ki hrane intervale
    vector<pair<int, int>> intervals;
    for(int i = 0; i < n; i++){
        //direktno preberem lokacijo in domert
        int location, illumination;
        cin >> location >> illumination;

        //če je luč "pokvarjena"
        if(illumination == 0) continue;

        //izračunam začetek in konec intervala
        int start_interval = location - illumination;
        int end_interval = location + illumination;
        
        pair<int, int> interval;
        interval.first = max(0, start_interval);
        interval.second = min(m, end_interval);

        //če je interval veljaven, ga dodam v vektor
        if(interval.first < interval.second) intervals.push_back(interval);
    }

    //če sličajno ni nobenega osvetljenega intervala, končam
    if(intervals.empty()){
        cout << m << endl;
        return 0;
    }

    sort(intervals.begin(), intervals.end());

    //vektor, ki hrani združene intervale
    vector<pair<int, int>> merged;
    //pushamo prvi intrval - ker še ni potrebe po združevanju, saj je samo en interval
    merged.push_back(intervals[0]);
    for(int i = 1; i < intervals.size(); i++){
        //zadnji mergan
        int last_end = merged.back().second;

        //če se trenutni interval ne prekriva z zadnjim intervalom, ga dodamo kot novega
        if(last_end < intervals[i].first){
            merged.push_back(intervals[i]);
            continue;
        }

        //če je zgornja meja zadnjega združenega intervala večja od spodnje meje trenutnega intervala,
        //to pomeni, da zadnji združeni interval vsebuje del ali celoten trenutni interval
                //posodobimo zgornjo mejo zadnjega združenega intervala na večjo od zgornjih mej
        //če je zgornja meja zadnjega združenega intervala enaka spodnji meji trenutnega intervala,
        //to pomeni, da se zadnji združeni interval dotika trenutnega intervala
                //posodobimo ugornjo mejo zadnjega združenega intervala na zgornjo mejo trenutnega intervala
        if(last_end >= intervals[i].first){
            merged.back().second = max(last_end, intervals[i].second);
        }
    }

    /*for(int i = 0; i < merged.size(); i++){
        cout << "[" <<merged[i].first << ", " << merged[i].second << "], ";
    }*/

    int not_illuminated = merged[0].first;
    //cout << not_illuminated;
    for(int i = 0; i < merged.size() - 1; i++){
        not_illuminated += merged[i + 1].first - merged[i].second;
        //cout << not_illuminated;
    }
    not_illuminated += m - merged.back().second;
    //cout << not_illuminated;

    cout << not_illuminated << endl;

    return 0;
}