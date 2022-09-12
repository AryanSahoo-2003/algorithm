#include <bits/stdc++.h>
using namespace std;
int solve(int r[], int n, int p[]){
    int q = 0;
    if(r[n] >= 0){
        return r[n];
    }
    if(n==0){
        q=0;
    }
    else{
        q = -1;
        for(int i=1;i<=n;i++){
            q = max(q, p[i] + solve(r, n-i, p));
        }
    }
    r[n] = q;
    return q;
}
int find_cost(int r[], int n, int p[]){
    for(int i=0;i<=n;i++){
        r[i] = -1;
    }
    return solve(r, n, p);
}
int main(){
    int price[] = {0,1,5,8,9,10,17,17,20,24,30};
    int revenue[11];
    cout<<find_cost(revenue, 4, price);
}
