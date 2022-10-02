#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define repl(i,n) for(int i = 0; i <= n ; i++)
const ll INF = 1e18;
int node,edge;

#define mx 100001
int arr[mx];
int tree[mx * 3];

void init(int node, int b, int e)
{
    if (b == e)
    {
        tree[node] = arr[b];//
        return;
    }
    int Left = node * 2;//2 4 8
    int Right = node * 2 + 1;//3 5 9
    int mid = (b + e) / 2;//4 2 1

    init(Left, b, mid);//(2,1,4) (4,1,2) (8,1,1)
    init(Right, mid + 1, e);
    tree[node] = tree[Left] + tree[Right];
}

int query(int node, int b, int e, int i, int j)//(1,1,7,3,7)
{
    if (i > e || j < b)//(3 > 7 || 7 < 1)
        return 0; //বাইরে চলে গিয়েছে

    if (b >= i && e <= j)
        return tree[node]; //রিলেভেন্ট সেগমেন্ট

    int Left = node * 2; //আরো ভাঙতে হবে   2
    int Right = node * 2 + 1;// 3
    int mid = (b + e) / 2;//4
    int p1 = query(Left, b, mid, i, j);//(2,1,4, 3,7)
    int p2 = query(Right, mid + 1, e, i, j);

    return p1 + p2; //বাম এবং ডান পাশের যোগফল
}

void update(int node, int b, int e, int i, int newvalue)
{
    if (i > e || i < b)
        return; //বাইরে চলে গিয়েছে
    if (b >= i && e <= i)   //রিলেভেন্ট সেগমেন্ট
    {
        tree[node] = newvalue; //নতুন মান বসিয়ে দিলাম
        return;
    }

    int Left = node * 2; //আরো ভাঙতে হবে
    int Right = node * 2 + 1;
    int mid = (b + e) / 2;
    update(Left, b, mid, i, newvalue);
    update(Right, mid + 1, e, i, newvalue);
    tree[node] = tree[Left] + tree[Right];
}

int main()
{
    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        cin>>arr[i];
    }

    init(1, 1, n);

    update(1, 1, n, 2, 0);
    cout << query(1, 1, n, 1, 3) << endl;

    update(1, 1, n, 2, 2);
    cout << query(1, 1, n, 2, 2) << endl;

    return 0;
}
