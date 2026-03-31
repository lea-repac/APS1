//vključim skoraj vse knjižnice
#include <bits/stdc++.h>
using namespace std;

bool matchFrom(string &S, string &T, int start, int &end) {
    int indexT = start;   //indeks v T
    int indexS = 0;       //indeks v S

    int lastStar = -1;        //zadnji * v S
    int matchAfterStar = -1; //indeks v T, kjer se je * začel

    while (indexT < (int)T.size()) {
        //ujemanje znaka ali ? -> enostavno povečam indekse, ker je pomembno samo da se znaka ujemata oz, da je samo en znak
        if (indexS < (int)S.size() &&
            (S[indexS] == T[indexT] || S[indexS] == '?')) {
            indexT++;
            indexS++;
        }

        //* v vzorcu -> updejtam indekse povezane z zvezdicami
        else if (indexS < (int)S.size() && S[indexS] == '*') {
            lastStar = indexS;
            matchAfterStar = indexT;
            indexS++;  // '*' najprej ujame 0 znakov
        }
        //znak se niti ne ujema, niti ni samo en, niti ni zvezdica, zato nam preostane samo, da probamo razširit prejšnjo zvezdico (če obstaja) ali pa se zadeva ne ujema
        else if (lastStar != -1) {
            indexS = lastStar + 1;
            matchAfterStar++;
            indexT = matchAfterStar;
        }
        //popoln neuspeh - ne moremo razširit prešnje zvezdice, ker je ni 
        else {
            return false;
        }

        //če pridem do konca celotnega S niza, potem smo našli ujemanje
        if (indexS == (int)S.size()) {
            end = indexT - 1;
            return true;
        }
    }

    // preverimo, ali so v vzorcu ostali samo *
    while (indexS < (int)S.size() && S[indexS] == '*') {
        indexS++;
    }

    //če pridem do konca celotnega S niza, potem smo našli ujemanje 
    if (indexS == (int)S.size()) {
        end = indexT - 1;
        return true;
    }

    return false;
}

int main() {
    //pohitri branje in pisanje
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string S, T;
        cin >> S >> T;

        bool found = false;

        for (int start = 0; start < (int)T.size(); start++) {
            int end;
            if (matchFrom(S, T, start, end)) {
                if(end < 0) end = 0; // recimo primer, da je celoten S *
                cout << start << " " << end << endl;
                found = true;
                break; // najmanjši začetni indeks
            }
        }

        if (!found) {
            cout << "-1" << endl;
        }
    }

    return 0;
}
