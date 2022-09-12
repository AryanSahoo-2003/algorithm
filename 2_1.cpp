#include <bits/stdc++.h>
using namespace std;

int is_ans = 0, totalcost;
vector<vector<int>> ans; //using set to remove duplicates from recursion a

void print_vector(vector<int> n){
    for(auto i: n){
        cout<<i<<" ";
    }
    cout<<endl;
}
void Sum(vector<int>& candidates, int target, vector<vector<int> >& ans, vector<int>& r, int i)
    {
        
        if(target == 0)
        {
            ans.push_back(r);
            return;
        }
        
        while(i <  candidates.size() && target - candidates[i] >= 0)
        {
            r.push_back(candidates[i]);
            Sum(candidates,target - candidates[i],ans,r,i);
            ++i;
            r.pop_back();
        }
}

int main(){
    int n, totalcost;
    cout<<"Number of items in the sack: ";
    cin>>n;
    cout<<"Enter total cost: ";
    cin>>totalcost;

    vector<int> arr;
    cout<<"Cost of each item(separated by spaces): "<< endl;
    for (int i = 0; i < n; i++){
        int temp;
        cin>>temp;
        arr.push_back(temp);
    }
    sort(arr.begin(), arr.end());
    vector<int> a;
    a.clear();
    Sum(arr, 80, ans, a, 0);

    cout<<"a: "<< endl;

    for(auto it: ans){
        print_vector(it);
    }

    return 0;
}