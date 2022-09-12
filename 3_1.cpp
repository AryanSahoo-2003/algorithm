#include <bits/stdc++.h>
using namespace std;

int partition(int arr[],int l,int r){
    int piv=arr[r];
    int i=l-1;
    for(int j=l;j<r;j++){
        if(arr[j]<=piv){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[r]);
    return i+1;
}

int rand_partition(int arr[],int l,int r){
    srand(time(0));
    swap(arr[l+rand()%(r-l)],arr[r]);
    return partition(arr,l,r);
}

// Randomised quick sort
void r_quicksort(int arr[],int l,int r){
    if(l<r){
        int piv=rand_partition(arr,l,r);
        r_quicksort(arr,l,piv-1);
        r_quicksort(arr,piv+1,r);

    }
}

int main(){
    int count[2001];
    int n;
    cout<<"Enter the size of the array: ";
    cin>>n;
    
    bool check_error=true; // there is no error
    if(n<2){
        cout<<"The size of array needs to be atleast 2.";
        check_error=false; // there is an error
    }
    else if(n>2000){
        cout<<"The size of array needs to be less than 2000.";
        check_error=false; // there is an error
    }

    for(int i=0;i<2001;i++)
            count[i]=0;
    int a[n];
    cout<<"Enter array elements(separated by spaces):"; // take input
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i]<-1000){
            cout<<"The elements need to be >= -1000\n";
            check_error=false;
        }else if(a[i]>1000){
            cout<<"The elements need to be <= 1000\n";
            check_error=false;
        }
        count[a[i]+1000]++;
        if(a[i]+1000<=2000&&count[a[i]+1000]>1){
            cout<<"The numbers need to be unique. "<<a[i]<<" is not unique, there are more than 1 occurences.\n";
            check_error=false;
        }
        if(i>2000)break;
    }

    if(!check_error) return 0; // there are error, don't do quicksort and end program

    r_quicksort(a,0,n-1); //randomised quicksort
    
    int mindiff=2001;
    vector<int>ans;

    for(int i=0;i<n-1;i++){ //calculate minimum difference
        if(a[i+1]-a[i]<mindiff){
            ans.clear();
            mindiff=a[i+1]-a[i];
            ans.push_back(i);
            ans.push_back(i+1);
        }
        else if(a[i+1]-a[i]==mindiff){
            ans.push_back(i);
            ans.push_back(i+1);
        }
    }
    cout<<"Minimum Difference: "<<mindiff<<'\n';
    cout<<"No of pairs with minimum difference: "<<(ans.size()/2)<<'\n';
    cout<<"OutArr: ";
    for(int i=0;i<ans.size();i++){
        cout<<a[ans[i]]<<' ';
    }
    return 0;
}