#include<bits/stdc++.h>
using namespace std;


    int findKthDigit(long long k) {

        // Block 0 contains 1...9
        if (k <= 9) {
            return k + '0' - '0';
        }

        k -= 9;

        long long b = 1;

        while (true) {
            long long first = 10 * b;
            long long digits = to_string(first).size();

            long long blockLen = 10LL * digits;

            if (k > blockLen) {
                k -= blockLen;
                b++;
                continue;
            }

            long long pos = k - 1;

            long long idx = pos / digits;

            long long digitIdx = pos % digits;

            long long number;

            if (b % 2 == 0) {
                number = 10 * b + idx;
            } else {
                number = 10 * b + 9 - idx;
            }

            string s = to_string(number);
            return s[digitIdx] - '0';
        }
    }
int main(){
    long long k;
    cin>>k;
    cout<<findKthDigit(k);
}