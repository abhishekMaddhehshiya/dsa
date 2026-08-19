#include <bits/stdc++.h>
using namespace std;

class Segmentst
{
    vector<int> st, lazy;
    public: 
    Segmentst(int n){
        st.resize(4*n);
        lazy.resize(4*n);
    }
    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            st[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid,arr);
        build(2 * ind + 2, mid + 1, high,arr);
        st[ind] = st[2 * ind + 1] + st[2 * ind + 2];
    }
    

    int quary(int ind, int low, int high, int l, int r)
    {
        //update the previous remaining updates and propogates downwords
        if(lazy[ind] != 0){
            st[ind] += (high-low+1)* lazy[ind];

            if(high != low){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap -> low high l r or l r low high
        if (high < l || r < low)
        {
            return 0;
        }

        // complete overlap ->   l low high r
        if (l <= low && high <= r)
        {
            return st[ind];
        }

        // partial overlap ->
        int mid = (low + high) / 2;
        int left = quary(2 * ind + 1, low, mid, l, r);
        int right = quary(2 * ind + 2, mid + 1, high, l, r);
        return left+ right;
    }

    void update(int ind, int low, int high, int l, int r, int val)
    {
        //update the previous remaining updates and propogates downwords
        if(lazy[ind] != 0){
            st[ind] += (high-low+1)* lazy[ind];

            if(high != low){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap
        //l r low high or low high l r

        if (r < low || high < l)
        {
            return;
        }

        // Complete ovrelap
        //l low high r

        if(l <= low && high <= r){
            st[ind] += (high - low+1)*val;
            if(low != high){
                lazy[2*ind+1] += val;
                lazy[2*ind +2] += val;
            }
            return;
        }

        int mid = (low + high) / 2;
        
        update(2 * ind + 1, low, mid, l,r, val);
        
        update(2 * ind + 2, mid + 1, high, l,r, val);
        st[ind] = st[2 * ind + 1] +  st[2 * ind + 2];
    }
    
};

int main()
{
    int n = 7;
    vector<int> arr = {1,3,2,4,5,2,3};
    
    Segmentst sg(n);
    sg.build(0, 0, n - 1,arr);

    //ex-> arr = [1,3,2,4,5,2,3]
            //    0 1 2 3 4 5 6                            
    cout<< sg.quary(0,0,n-1, 2,4)<<endl; //11
    cout<< sg.quary(0,0,n-1, 3,5)<<endl; // 11
    cout<< sg.quary(0,0,n-1, 0,4)<<endl; // 15
    arr[2]+=7;
    arr[3] += 7;
    arr[4] += 7;
    //ex-> arr = [1,3,9,11,12,2,3]
    //            0 1 2  3  4 5 6    
    sg.update(0,0,n-1,2,4,7);
    cout<< sg.quary(0,0,n-1, 2,4)<<endl; // 32
    arr[4] +=2;
    arr[5] += 2;
    arr[6] += 2;
    //ex-> arr = [1,3,9,11,14,4,5]
    //            0 1 2  3  4 5 6    
    sg.update(0,0,n-1,4,6,2);
    cout<< sg.quary(0,0,n-1, 2,5)<<endl; // 38
    cout<< sg.quary(0,0,n-1, 1,4)<<endl; // 37
    cout<< sg.quary(0,0,n-1,3,4)<<endl; // 25
}