#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<float>> arr;
    vector<bool> check;
    for (int i = 0; i < n; i++) {
        int r, a, b;
        cin >> r >> a >> b;
        arr.push_back({b, a, r});
        check.push_back(false);
    }
    sort(arr.begin(), arr.end());
    float result = 1000000000;
    float m = 0;
    bool done = false;
    for (int j = 1; j < n; j++) {
        int k = 0;
        m = 1000000000;
        while (k < n - j) {
            float b1 = arr[k][0];
            float a1 = arr[k][1];
            float r1 = arr[k][2];
            float b2 = arr[k + j][0];
            float a2 = arr[k + j][1];
            float r2 = arr[k + j][2];
            if (check[k]) {
                k += j;
                continue;
            }
            if (a1 <= a2) {
                k += 1;
                continue;
            }
            double distance = (b2 - b1) - sqrt(4 * r1 * r2);
            double t = (distance * 1.00) / (a1 - a2);
            if (t < m) {
                m = t;
            }
            if (r2 > r1) {
                check[k] = true;
                k += j;
                continue;
            }
            k += 1;
        }
        if (j == 1 && m == 1000000000) {
            cout << "Collision-Free System";
            done = true;
            break;
        } else if (m == 1000000000) {
            break;
        } else if (m < result) {
            result = m;
        }
    }
    if (!done) {
        cout << fixed << setprecision(2) << result << endl;
    }
    return 0;
}
