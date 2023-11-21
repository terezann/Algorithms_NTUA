#include <algorithm>
#include <iostream>
using namespace std;

int array_transformation(int array[], int N, int K, int position) {
    //convert to ones.
    int transformed[N];
    for (int i = 0; i < N; i++) {
        if (array[i] >= position) {
            transformed[i] = 1;
        }
        else
            transformed[i] = -1;
    }


    //prefix sum
    int prefix[N];
    prefix[0] = transformed[0];
    for (int i = 1; i < N; i++) {
        prefix[i] = prefix[i - 1] + transformed[i];
    }

    //window search knowing that that the indices have a distance of at least K.
    int min = prefix[0];
    int maxmed =  prefix[K-1];

    for(int i=K; i<N; i++) {
        if (prefix[i-K] < min) min = prefix[i-K];
        if ((prefix[i] - min) > maxmed) maxmed = prefix[i] - min;
    }

    return maxmed;
}

int main() {
    int N, K;
    cin >> N >> K;
    int arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int l, r;
    l = *min_element(arr, arr+N);
    r = *max_element(arr, arr+N) + 1;
    int mid;

    
    while ((r - l) > 0) {
        //binary search
        mid = (l+r)/2;
        int res = array_transformation(arr, N, K, mid);
        if (res > 0) {
            l = mid + 1;
        }
        else
            r = mid;
    }
    cout << l-1 << endl;

    return 0;
}
