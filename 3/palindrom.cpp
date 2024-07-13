#include <bits/stdc++.h>
using namespace std;
struct Hash {
    long long m = 1e9 + 7;
    long long hash_value;
    Hash(const string& s, long long p) {
        long long hash_so_far = 0;
        long long p_pow = 1;
        const long long n = s.length();
        long long arr[n];
        for (long long i = 0; i < n; ++i) {
            hash_so_far = (hash_so_far + (s[i] - 'a' + 1) * p_pow) % m;
            arr[i] = hash_so_far;
            p_pow = (p_pow * p) % m;
        }
        hash_value = hash_so_far;
    }
    bool operator==(const Hash& other) {
        return (hash_value == other.hash_value);
    }
};
bool palindrome(string real, string reversed) {
    Hash one(real, 31);
    Hash ONE(reversed, 31);
    if(one.hash_value == ONE.hash_value)
        return true;
    return false;
}

void reverseStr(string& str){
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}
int main() {
    string s;
    cin >> s;
    int n = s.length();

    long long m = 1e9 + 7;

    long long base0 = 31;//31
    long long base1 = 37;//37
    long long base2 = 131;//131

    long long real_arr0[n];
    long long real_arr1[n];
    long long real_arr2[n];

    long long p_pow0 = 1;
    long long p_pow1 = 1;
    long long p_pow2 = 1;

    long long temp0 = 0;
    long long temp1 = 0;
    long long temp2 = 0;

    //string ss = s;
    //reverseStr(ss);

    long long sreal_arr0[n];
    long long sreal_arr1[n];
    long long sreal_arr2[n];

    long long stemp0 = 0;
    long long stemp1 = 0;
    long long stemp2 = 0;
    for (int i = 0; i < n; i++) {
        long long charCode = (int)s[i];
        //long long cc = (int) ss[n - 1 - i];

        temp0 = (temp0 + p_pow0 * charCode) % m;
        real_arr0[i] = temp0;
        p_pow0 = (p_pow0 * base0) % m;

        temp1 = (temp1 + p_pow1 * charCode) % m;
        real_arr1[i] = temp1;
        p_pow1 = (p_pow1 * base1) % m;

        temp2 = (temp2 + p_pow2 * charCode) % m;
        real_arr2[i] = temp2;
        p_pow2 = (p_pow2 * base2) % m;

        stemp0 = ((stemp0 * base0) % m + charCode) % m;
        sreal_arr0[i] = stemp0;

        stemp1 = (stemp1 * base1 + charCode) % m;
        sreal_arr1[i] = stemp1;

        stemp2 = (stemp2 * base2 + charCode) % m;
        sreal_arr2[i] = stemp2;
    }
    int arr[n];
    arr[0] = 1;
    int sum = 1;//
    for (int i = 1; i < n; i++) {
        //cout << real_arr0[i] << " " << sreal_arr0[i] << "\n" << real_arr1[i] << " " << sreal_arr1[i] << "\n" << real_arr2[i] << " " << sreal_arr2[i] << endl;
        if(real_arr0[i] == sreal_arr0[i] && real_arr1[i] == sreal_arr1[i] && real_arr2[i] == sreal_arr2[i]) {
            arr[i] = 1 + arr[((i + 1) / 2) - 1];
        } else {
            arr[i] = 0;
        }
        sum += arr[i];
        //cout << arr[i] << " ";
    }
    cout << sum;
    return 0;
}
