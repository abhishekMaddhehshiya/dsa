#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    vector<int> tree;
    public: 
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void build(int node, int start, int end, vector<int> &arr)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid,arr);
        build(2 * node + 2, mid + 1, end,arr);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }

    int quary(int node, int start, int end, int l, int r)
    {
        // no overlap -> start end l r or l r start end
        if (end < l || r < start)
        {
            return INT_MAX;
        }

        // complete overlap ->   l start end r
        if (l <= start && end <= r)
        {
            return tree[node];
        }

        // partial overlap ->
        int mid = (start + end) / 2;
        int left = quary(2 * node + 1, start, mid, l, r);
        int right = quary(2 * node + 2, mid + 1, end, l, r);
        return min(left, right);
    }

    void update(int node, int start, int end, int i, int val)
    {
        if (start == end)
        {
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;
        if (i <= mid)
            update(2 * node + 1, start, mid, i, val);
        else
            update(2 * node + 2, mid + 1, end, i, val);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }
};

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i =0; i < n; i++){
        cin>>arr[i];
    }
    SegmentTree sg(n);
    sg.build(0, 0, n - 1,arr);

    //ex-> arr = [1,3,2,4,5,2,3]
            //    0 1 2 3 4 5 6                            
    cout<< sg.quary(0,0,n-1, 2,4)<<endl; //2
    cout<< sg.quary(0,0,n-1, 3,5)<<endl; // 2
    cout<< sg.quary(0,0,n-1, 0,4)<<endl; // 1
    arr[2] = 0;
    //ex-> arr = [1,3,0,4,5,2,3]
    //    0 1 2 3 4 5 6    
    sg.update(0,0,n-1,2,0);
    cout<< sg.quary(0,0,n-1, 2,4)<<endl; // 0
    arr[4] =2;
    //ex-> arr = [1,3,0,4,2,2,3]
    //    0 1 2 3 4 5 6    
    sg.update(0,0,n-1,4,2);
    cout<< sg.quary(0,0,n-1, 2,5)<<endl; //0
    cout<< sg.quary(0,0,n-1, 1,4)<<endl; // 0
    cout<< sg.quary(0,0,n-1,3,4)<<endl; // 2
}