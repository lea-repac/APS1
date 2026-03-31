#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

bool colour(vector<vector<int>>& connected, vector<int>& colours, int start){
    queue<int> temp;
    //začetnemu vozlišču dodam prvo barvo in ga dodam v vrsto
    colours[start] = 1;
    temp.push(start);

    //ko je vrsta prazna pomeni, da smo obdelali vse sosede začetnega vozlišča in tudi njihove sosede itd.
    while(!temp.empty()){
        //vzamem trenutno vozlišče in vse njegove sosede obarvam ter dodam v vrsto
        int current = temp.front();
        temp.pop();

        for(int neighboring : connected[current]){
            //če sosed še ni obravan, mu dodam nasprotno barvo kot trenutnemu
            if(colours[neighboring] == 0){
                colours[neighboring] = (colours[current] == 1 ? 2 : 1);
                temp.push(neighboring);
            //če je že obarvan ga ne dodajam v vrsto, ampak grem samo naprej razen če je obarvan v isto barvo -> potem graf ni dvodelni
            } else if(colours[neighboring] == colours[current]) return false;
        }
    }
    return true;
}

int main(){
    //n - število vozlošč, m - število parov na vhodu 
    int n, m;
    cin >> n >> m;

    //vektor, ki za vsako vozlišče hrani vse njegove sosede - povezana vozlišča
    vector<vector<int>> connected(n + 1);
    //vektor, ki za vsako vozlišče hrani barvo - 0 = neobarvan, 1 = prva skupina, 2 = druga skupina
    //inicializiramo na 1, ker so najprej vsi neobarvani
    vector<int> colours(n + 1, 0);

    int first = 0;
    int second = 0;
    for(int i = 0; i < m; i++){
        pair<int, int> input;
        cin >> input.first >> input.second;
        connected[input.first].push_back(input.second);
        connected[input.second].push_back(input.first);
    }

    //barvamo in sproti gledamo, ali je vrstni red leksikografski in ali je graf sploh dvodelni
    for(int i = 1; i <= n; i++){
        if(colours[i] == 0){
            if(!colour(connected, colours, i)){
                //če funkcija colour vrne false, smo ugotovili, da graf ni dvodelen/bipartiten/se ne da razdeliti otrok v dve skupini tako da ne klepetajo
                //lahko direktno končam program
                cout << "-1" << endl;
                return 0;
            }
        }
    }

    //izpis
    for(int i = 1; i <= n; i++) cout << colours[i] << "\n";

    return 0;
}