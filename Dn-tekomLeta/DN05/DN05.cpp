#include <bits/stdc++.h>
using namespace std;

struct Node {
    int importance;
    int index;   // original index (1-based)
};

Node combine(const Node &a, const Node &b) {
    return (a.importance > b.importance ? a : b);
}

int main(){
    int n;
    cin >> n;

    vector<string> words(n);
    vector<int> importance(n);
    for(int i = 0; i < n; i++){
        cin >> words[i] >> importance[i];
    }

    // sortiramo leksikografsko, ohranjam iste indekse
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){
        return words[a] < words[b];
    });

    int SZ = 1;
    while(SZ < n) SZ <<= 1;

    vector<Node> segtree(2*SZ, Node{ -1, 0 });

    for(int i = 0; i < n; i++){
        int orig = order[i];
        segtree[SZ + i] = Node{ importance[orig], orig+1 };
    }

    for(int i = SZ - 1; i > 0; i--){
        segtree[i] = combine(segtree[2*i], segtree[2*i + 1]);
    }

    auto query = [&](int l, int r){
        Node res{ -1, 0 };
        l += SZ; r += SZ;
        while(l <= r){
            if(l & 1) res = combine(res, segtree[l++]);
            if(!(r & 1)) res = combine(res, segtree[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    };

    int Q;
    cin >> Q;

    vector<int> answers;
    answers.reserve(Q);

    while(Q--){
        string prefix;
        cin >> prefix;

        // najnižji možni niz >= prefix
        auto itL = lower_bound(order.begin(), order.end(), prefix,
            [&](int idx, const string& val){
                return words[idx] < val;
            }
        );

        // končni niz prefixa
        string next = prefix;
        next.push_back('{'); // znak za 'z' + 1 v ASCII

        // prvi indeks >= next
        auto itR = lower_bound(order.begin(), order.end(), next,
            [&](int idx, const string& val){
                return words[idx] < val;
            }
        );

        if(itL == itR){
            answers.push_back(0);
            continue;
        }

        int L = itL - order.begin();
        int R = itR - order.begin() - 1;

        Node best = query(L, R);
        answers.push_back(best.index);
    }

    for(int x : answers) cout << x << "\n";
    return 0;
}
