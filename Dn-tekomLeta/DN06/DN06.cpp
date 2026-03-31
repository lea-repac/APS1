#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int MAX = (int) 1e6;

//definiram strukturo, ki hrani števila od 1 do MAX in dovoljuje, da se število ponovi večkrat
//deluje podobno kot std::multiset (mnžica z več ponovitvami)
struct MultiSet{
    //največja dovoljena vrednost elementa
    int size;
    //Fenickowo drevo
    vector<int> tree;

    //konstruktor
    MultiSet(int n){
        size = n;
        tree = vector<int>(n + 1, 0);
    }

    //funckije, ki jih podpira

    //dodajanje ponovitve elementa a
    void add(int a){
        while (a <= size) {
            tree.at(a)++;
            //a postane število v desetiškem zapisu enako najmanjšemu bitu, ki je nastavljen na 1
            //to nam pove, kakšen interval pokriva tree[a]
            a += a & -a;
        }
    }

    //odstranjevanje ponovitve elementa a
    void remove(int a){
        while(a <= size){
            tree.at(a)--;
            a += a & -a;
        }
    }

    //vsota pojavitev elementov, ki so <= a
    int sum(int a){
        int res = 0;
        while(a > 0){
            res+= tree.at(a);
            a -= a & -a;
        }
        return res;
    }

    //koliko elementov (njihovih ponovitev) je na intervalu
    int range(int a, int b){
        if(a > b){
            return 0;
        } else {
            return sum(b) - sum(a-1);
        }
    }
};

int main() {
    int n;
    cin >> n;
    
    MultiSet mset(MAX);
    //hrani dejansko število elementov, s čimer si zagotovimo, da ne pride slučajno do odstranjevanja elementa, ki ga ni
    vector<int> count(MAX + 1, 0);

    long long int result = 0;

    for (int i = 0; i < n; ++i) {
        //op nam pove, kaj počnemo z elementom x
        int op, x;
        cin >> op >> x;

        //če je op < 0, x dodam v vrečo
        if (op < 0) {
            count.at(x)++;
            mset.add(x);
        //če je op = 0, x odstranim iz vreče
        } else if (op == 0) {
            //preverimo, če obstaja vsaj ena ponovitev x
            if (count.at(x) > 0) {
                count.at(x)--;
                mset.remove(x);
            }
        //če je op > 0, preverimo, koliko je elementov na intervalu [min(op, x), max(op, x)]
        } else if (op > 0) {
            int a = min(op, x);
            if(a < 0) a = 1;
            int b = max(op, x);
            result += mset.range(a, b);
        }
    }

    cout << result << endl;

    return 0;
}
