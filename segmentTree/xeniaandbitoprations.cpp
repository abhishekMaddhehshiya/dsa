#include<bits/stdc++.h>
using namespace std;

class SegmentTree
{
    public: 
    vector<int> tree;
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void build(int node, int start, int end, vector<int> &arr, int flag)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid,arr,!flag);
        build(2 * node + 2, mid + 1, end,arr, !flag);
        if(!flag) tree[node] = tree[2 * node + 1]^ tree[2 * node + 2];
        else tree[node] = tree[2 * node + 1] | tree[2 * node + 2];
    }


    void update(int node, int start, int end, int i, int val, int flag)
    {
        if (start == end)
        {
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;
        if (i <= mid)
            update(2 * node + 1, start, mid, i, val,!flag);
        else
            update(2 * node + 2, mid + 1, end, i, val, !flag);
        if(!flag) tree[node] = tree[2 * node + 1]^ tree[2 * node + 2];
        else tree[node] = tree[2 * node + 1] | tree[2 * node + 2];
    }
};

int main(){
    int n,q;
    cin>>n>>q;
    
    int s = pow(2,n);
    vector<int> arr(s);
    for(int i =0; i < s; i++){
        cin>>arr[i];
    }
    SegmentTree sg(s);
    if(n % 2 == 0){
        sg.build(0,0 ,s-1, arr, 0);
    }
    else{
        sg.build(0,0,s-1,arr,1);
    }
    
    while(q--){
        int ind,val;
        cin>>ind>>val;
        ind--;
        
        arr[ind] = val;
        if(n % 2 == 0) sg.update(0, 0, s-1, ind, val, 0);
        else sg.update(0,0,s-1, ind, val, 1);
        cout<<sg.tree[0]<<endl;
    }
    
    
}