#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

const int MAX = 1e6-1;
int root[MAX];
// const int nodes = 4, edges = 5;
pair <pair<int, int>, pair<int, int> > p[MAX];

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int parent(int a)  //find the parent of the given node
{
    while(root[a] != a) //
    {
        root[a] = root[root[a]];
        a = root[a];
    }
    return a;
}

void union_find(int a, int b)  //check if the given two vertices are in the same “union” or not
{
    int d = parent(a);
    int e = parent(b);
    root[d] = root[e];
}

vector<int> kruskal(int u, int v, int gain, int weight) { //prepei na dwsw oli ti lista.
    //kritirio taksinomisis h hdh taksinomimeni lista.
    weight = 0, gain = 0;
    int sum_p = 0, sum_w = 0;
    for(int i = 0 ; i < edges ; ++i) { //gia kathe grammi, gia kathe pragma tis listas diladi.
        u = p[i].second.first;
        v = p[i].second.second;
        gain = p[i].first.first;
        weight = p[i].first.second;
        if(parent(u) != parent(v)) //only select edge if it does not create a cycle (ie the two nodes forming it have different root nodes)
        {
            sum_p += gain;
            sum_w += weight;
            union_find(u, v);   //ένωσε τις 2 ακμές
        }
    }

    int gcd_pw = gcd(sum_p, sum_w);

    vector<int> res;
    res.push_back(sum_p);
    res.push_back(sum_w);
    res.push_back(gcd_pw);

    return res;
}

int main() {

    int u, v, p, w;
    int N, M;
    int diff = 0;
    int c = 1;
    cin >> N >> M;
    vector<vector<int>> listOfedges;

    for(int i=0; i<M; i++) { 
        vector<int> edge {u, v, p, w, diff};
        for (int j=0; j<4; j++) {
            int input;
            cin >> input;
            edge.push_back(input);
        }
        diff = p - c*w;
        edge.push_back(diff);
        
        listOfedges.push_back(edge);
    }

    int x, y;
    double weight, gain, maxRatio;
    for(int i = 0;i < MAX;++i)    //initialize the array groups
    {
        root[i] = i;
    }

    p[0] = make_pair(make_pair(1, 2), make_pair(1, 3));  // weight = 3, gain = 1
    p[1] = make_pair(make_pair(2, 3), make_pair(2, 2));  // weight = 2, gain = 2
    p[2] = make_pair(make_pair(3, 1), make_pair(3, 1));  // weight = 1, gain = 3
    // p[3] = make_pair(make_pair(21, 10), make_pair(0, 2)); // weight = 21, gain = 10
    // p[4] = make_pair(make_pair(22, 11), make_pair(1, 3)); // weight = 22, gain = 11

    // sort(p, p + edges, [](const auto &lhs, const auto &rhs) {
    //     return lhs.first.second / lhs.first.first > rhs.first.second / rhs.first.first;
    // });
    //
    //
    // maxRatio = kruskal();
    // cout << "Minimum cost is: "<< maxRatio << endl;

    vector<int> res = kruskal(u, v, p, w);
    cout << res << endl;
    return 0;
}
