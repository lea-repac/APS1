 #include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

/*bool dotika(pair <int, int>* p1, int* x, int* d)
{
    /*cout << "(" << p1 -> first << ", " << p1 -> second << ") ";
    for (int i = p1 -> first; i <= p1 -> second; i++)
    {
   //     cout << "1";
        for (int j = *x + *d; j >= *x - *d; j--)
            //Prej bo najdlo, če se ena stran pomika proti desni in druga proti levi.
        {
     //       cout << "(" << i << ", " << j << ")" << " (" << p1 -> first << ", " << p1 -> second << ") |";
            if (i == j)
            {
                cout << "true";
                return true;
            }
        }
    }
        return false; //Je malo prepočasno za velike vrednosti.

    return max(p1 -> first, *x - *d) <= min(p1 -> second, *x + *d);
}*/

/*bool samoNotri(pair <int, int>* p1, int* x, int* d)
{
    return p1 -> first <= *x - *d && p1 -> second >= *x + *d;
}*/

bool dotikaIntervali(pair <int, int>& p1, pair <int, int>& p2) {

    return max(p1.first, p2.first) <= min(p1.second, p2.second);
}

bool samoNotriKoncno (pair <int, int>& p1, pair <int, int>& p2)
{
 //   if (p1 -> first < p2 -> first && p1 -> second > p2 -> second) cout << "samoNotriKoncno";
    return p1.first < p2.first && p1.second > p2.second;
}

int main()
{
    int M, N;
    cin >> M >> N;

    if (N == 0) {
        cout << M << "\n";
        return 0;
    }

    vector <pair<int, int>> t1(N);

    int x, d;
    for (int i = 0; i < N; i++)
    {

        cin >> x >> d;

        //Dodaj prvi interval.
        int a, b = 0;
        if (x - d < 0) a = 0;
        else a = x - d;
        if (x + d > M) b = M;
        else b = x + d;

        t1.push_back({a, b});
    }
        //Dodaj nov interval ali ga vključi v obstoječe ali ga zavrži
        /*for (int j = 0; j < t1.size(); j++)
        {
            if (samoNotri(&t1[j], &x, &d)) continue; //Če je znoraj že zapisanega intervala grem na naslednjo luč.
            else if (dotika(&t1[j], &x, &d))
            {
                //Potrebno je imeti tabelo intervalov.
            //    cout << "1";
                if (x - d < t1[j].first && x - d >= 0) t1[j].first = x - d;
                else if (x - d < t1[j].first && x - d < 0) t1[j].first = 0;
                if (x + d > t1[j].second && x + d <= M) t1[j].second = x + d;
                else if (x + d > t1[j].second && x + d > M) t1[j].second = M;
              //  cout << "[" << t1[j].first << ", " << t1[j].second << "]";
                break;
            } else if (j == t1.size() - 1)
            {
                t1.push_back({x - d, x + d});
                break;
            }
        }*/
        //for (int k = 0; i < t1.size(); k++) cout << "(" << t1[k].first << ", " << t1[k].second << ")";

    //Pregled obstoječih intervalov.
    /*if (t1.size() >= 2) {
        sort(t1.begin(), t1.end());
        for (int i = 0; i < t1.size() - 1; i++)
            for (int j = i + 1; j < t1.size(); j++)
                if (dotikaIntervali(&t1[i], &t1[j]))
                {
                    if (t1[j].first < t1[i].first) t1[i].first = t1[j].first;
                    if (t1[j].second > t1[i].second) t1[i].second = t1[j].second;
                    t1.erase(t1.begin() + j);
                    j--;
                }*/

    //Združi intervale, ki se prekrivajo.
    vector <pair<int, int>> t2(0); //Naredi novo tabelo.
    if (t1.size() >= 2) {
        sort(t1.begin(), t1.end()); //Sortiraj intervale.

        pair <int, int> p1 = t1[0]; //Naredi prvi pair.

        for (int i = 1; i < t1.size(); i++) { //Išči nove intervale za novo tabelo.
            if (dotikaIntervali(p1, t1[i])) {
                if (t1[i].second > p1.second) p1.second = t1[i].second;
                else if (samoNotriKoncno(p1, t1[i])) continue;
                } else {
                t2.push_back(p1);
                p1 = t1[i];
            }
            //for (pair <int, int> p : t2 ) cout << "(" << p.first << ", " << p.second << ")";
            //cout << "\n";
            //cout << "(" << p1.first << ", " << p1.second << ")";
        }
        t2.push_back(p1);
 //     for (pair <int, int> p : t2) cout << "(" << p.first << ", " << p.second << ")";
 //     cout << "\n";
    } else t2.push_back(t1[0]); //If the size of t1 is 1 or less (it can't be less because that is solved at the
                                //beginning the the program.

    t1.clear();
    t1.shrink_to_fit();
    //Potrebno je še uničiti tabelo t1, delete t1;.

   /* for (int i = 0; i < t1.size(); i++)
        for (int j = i + 1; j < t1.size(); j++) {
            if (j > t1.size()) break;
            if (samoNotriKoncno(&t1[i], &t1[j])) {
                t1.erase(t1.begin() + j)); //Izbriše samo en takšen element (lahko je bug).
                //Ni problem, ker predhodnji del programa naredi, da kopij (popolnoma enakih vrednosti) ni v t1.
                break;
            }

        }*/

    //cout << "\n";

    //for (int i = 0; i < t1.size(); i++) cout << t1[i].first << " " << t1[i].second << "| ";
    //cout << "\n";

    //Najdi število neosvetljenih mest.
    int count = 0;
    if (t2[0].first >= 0) count += t2[0].first; //Vse neosvetljene pred prvo lučjo.
    //cout << count << " ";
    for (int i = 0; i < t2.size() - 1; i++)
    {
        count += t2[i + 1].first - t2[i].second; //Vse neosvetljene med lučmi.
    //    cout << count << " ";
    }
    if (M - t2[t2.size() - 1].second >= 0) count += M - t2[t2.size() - 1].second; //Vse neosvetljene za zadnjo lučjo.
    cout << count << "\n";
}
