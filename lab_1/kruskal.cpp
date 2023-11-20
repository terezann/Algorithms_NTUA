#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class DSU { 
    int* parent; 
    int* rank; 
  
public: 
    DSU(int n) 
    { 
        parent = new int[n]; 
        rank = new int[n]; 
  
        for (int i = 0; i < n; i++) { 
            parent[i] = -1; 
            rank[i] = 1; 
        } 
    } 
  
    // Find function 
    int find(int i) 
    { 
        if (parent[i] == -1) 
            return i; 
  
        return parent[i] = find(parent[i]); 
    } 
  
    // Union function 
    void unite(int x, int y) 
    { 
        int s1 = find(x); 
        int s2 = find(y); 
  
        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) { 
                parent[s1] = s2; 
            } 
            else if (rank[s1] > rank[s2]) { 
                parent[s2] = s1; 
            } 
            else { 
                parent[s2] = s1; 
                rank[s1] += 1; 
            } 
        } 
    } 
};

bool compareGain(const vector<int>& a, const vector<int>& b) {
    return a[2] > b[2]; //decreasing order
}

bool compareWeight(const vector<int>& a, const vector<int>& b) {
    return a[3] < b[3];
}

bool compareDiff(const vector<int>& a, const vector<int>& b) {
    return a[4] > b[4];
}

vector<int> kruskal(vector<vector<int>> lista, int N, int M, string str) { 
    DSU s(N);


    if (str == "compareGain") {
        sort(lista.begin(), lista.end(), compareGain);
    }

    if (str == "compareWeight") {
        sort(lista.begin(), lista.end(), compareWeight);
    }

    if (str == "compareDiff") {
        sort(lista.begin(), lista.end(), compareDiff);
    }
    

    int sum_p = 0, sum_w = 0;
    size_t length = lista.size();
    for(int i = 0 ; i < M ; ++i) { //gia kathe grammi, gia kathe pragma tis listas diladi.
        int u = lista[i][0];
        int v = lista[i][1];
        int gain = lista[i][2];
        int weight = lista[i][3];
        if(s.find(u) != s.find(v)) {
            sum_p += gain;
            sum_w += weight;
            s.unite(u, v);   //ένωσε τις 2 ακμές
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
    int N, M;
    int d = 0;
    int c = 1;
    cin >> N >> M;
    vector<vector<int>> listOfedges;
    
    for (int i=0; i<M; i++)  {
        vector<int> edge;
        // int source = 0;
        int source, destination, gain, weight;
        // int destination = 0;
        // int gain = 0;
        // int weight = 0;
        cin >> source >> destination >> gain >> weight;
        listOfedges.push_back({source, destination, gain, weight, d}); //diff = p-c*w
    }
    
    vector<int> res = kruskal(listOfedges, N, M, "compareGain");
    int max_gain = res[0];

    vector<int> res2 = kruskal(listOfedges, N, M, "compareWeight");
    int min_weight = res2[1];
    double c_max = (double)max_gain/min_weight;
    double c_min = 0;
    
    //binary search for c. ce[cmin, cmax]
    double l = c_min;
    double r = c_max;
    double mid = (l+r)/2;
    
    vector<int> greedy;



    while(r-l >= 0.01) {
        for (int i=0; i<M; i++) {
            listOfedges[i][4] = listOfedges[i][2]-(mid*listOfedges[i][3]);
        }
        greedy = kruskal(listOfedges, N, M, "compareDiff"); //greedy criterion, max diff.
        for (int i=0; i<M; i++) {
            listOfedges[i][4] = listOfedges[i][2]-(mid*listOfedges[i][3]);
        }
        int diff = greedy[0] - (mid * greedy[1]);
        if (diff >= 0) {
            l = mid;
        }
        else {
            r = mid;
        }
        mid = (l+r)/2;
    }
    cout << greedy[0]/greedy[2] << " " << greedy[1]/greedy[2] << endl;
    return 0;
}
