#include <bits/stdc++.h>
using namespace std;
class Node {
    public:
    int openings, closings, full;
    Node(int openings=0, int closings=0, int full=0){
        this->openings = openings;
        this->closings = closings;
        this->full = full;
    }
};

class SegmentTree
{
    vector<Node > tree;
    public: 
    SegmentTree(int n){
        tree.resize(4*n);
    }

    Node merge(Node left, Node right){
        int matched = min(left.openings, right.closings);
        Node n;
        n.full = left.full + right.full + matched;
        n.openings = left.openings + right.openings - matched;
        n.closings = left.closings + right.closings - matched;
        return n;
    }

    void build(int node, int start, int end, const string &s)
    {
        if (start == end)
        {
            
            tree[node] =  Node(s[start] == '(', s[start] == ')', 0);
            return;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid,s);
        build(2 * node + 2, mid + 1, end,s);

        
        tree[node] = merge(tree[2*node+1],tree[2*node+2]);
    }

    Node quary(int node, int start, int end, int l, int r)
    {
        // no overlap . start end l r or l r start end
        if (end < l || r < start)
        {
            return  Node();
        }

        // complete overlap .   l start end r
        if (l <= start && end <= r)
        {
            return tree[node];
        }

        // partial overlap .
        int mid = (start + end) / 2;
        Node left = quary(2 * node + 1, start, mid, l, r);
        Node right = quary(2 * node + 2, mid + 1, end, l, r);
        return merge(left , right);
    }

    
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin>>s;
    int n = s.length();
    SegmentTree sg(n);
    sg.build(0,0,n-1, s);

    int q; 
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;

        Node ans = sg.quary(0,0,n-1, l-1,r-1);
        cout<<ans.full*2<<endl;
    }
}