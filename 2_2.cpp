#include <bits/stdc++.h>
using namespace std;

set<string> s1;


bool check_palindrome(string s, int l, int r){
    
    if (l >= r){
        return 1;
    }
    if (s[l] != s[r]){
        return 0;
    }

    return check_palindrome(s, l + 1, r - 1);
}


void substring(string s, int j){
        if(j==s.size()){
            return;
        }
        string c = "";
        for (int i = j; i < s.size(); i++)
        {
            c += s[i];
            if (i > 1)
            {
                if (check_palindrome(c, 0, c.size() - 1) && c.size()>1)
                {
                    s1.insert(c);
                }
            }
        }
        substring(s,j+1);
}

int main(){
    int length;
    cout<<"Length of string: ";
    cin>>length;
    string s;
    cout<<"Enter the string: ";
    cin >> s;

    string c = "";
    substring(s, 0);
    int size = s1.size();
    cout<<"Number of Palindromic Substrings: "<<size<<endl;
    cout<<"List of substrings:"<<endl;
    for (auto i:s1){
        cout<<i<<" ";
    }
    return 0;
}