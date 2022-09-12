#include <bits/stdc++.h>
using namespace std;

struct S{
    int x;
    int y;
};

int count_digits(int n){ //count number of digits in number
    return floor(log10(n) + 1);
}

int remove_k_digits(int n, int k){
    while(k--){
        n/=10;
    }
    return n;
}


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int l, int r, int x){
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j <= r - 1; j++){
        if (arr[j] <= x){
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int get_median(int arr[], int n){ //get median from group of 5
    sort(arr, arr+n);
    return arr[n/2];
}

//FIND KTH MINIMUM USING GROUP OF 5, MEDIAN METHOD

int kth_min(int arr[], int l, int r,int k){
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; 
        int i, median[(n+4)/5]; 
        for (i=0; i<n/5; i++)
            median[i] = get_median(arr+l+i*5, 5);
        
        if (i*5 < n) {
            median[i] = get_median(arr+l+i*5, n%5);
            i++;
        }   
 
        int medOfMed = (i == 1)? median[i-1]:
        kth_min(median, 0, i-1, i/2);
 
        
        int pos = partition(arr, l, r, medOfMed);
 
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  
            return kth_min(arr, l, pos-1, k);
 
        return kth_min(arr, pos+1, r, k-pos+l-1);
    }
    return INT_MAX;
}

int main(){
    int n,m;
    cout<<"Enter value of n: ";
    cin>>n;
    cout<<"Enter value of m: ";
    cin>>m;

    int a[n];
    S opr[m];
    cout<<"Enter elements of A(separated by spaces): ";
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    int min_digits = count_digits(a[0]), max_y = 0, max_x = 0, min_x = n+1;
    for(int i=1;i<n;i++){
        min_digits = min(min_digits, count_digits(a[i]));
    }
    for(int i=0;i<m;i++){
        cout<<"Enter Opr[" <<i+1<< "].x and Opr[" <<i+1<< "].y :";
        cin>>opr[i].x>>opr[i].y;
        
        max_y = max(max_y, opr[i].y);
        min_x = min(min_x, opr[i].x);
        max_x = max(max_x, opr[i].x);
    }

    //CHECK CONSTRAINTS
    int c = 0;
    if(!(max_x <=n && min_x >=1)){
        cout<<"Value of opr.x does not satisfy condition."<<endl;
        c = 1;
    }
    if(max_y > min_digits){
        cout<<"Value of opr.y does not satisfy condition."<<endl;
        c = 1;
    }
    if(c == 1){
        return 0;
    }

    int output[m], a_temp[n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            a_temp[j] = remove_k_digits(a[j], opr[i].y); //GENERATE A_temp
        }
        int arr[n];
        for(int j=0;j<n;j++){
            arr[j] = a_temp[j];
        }
        int h = kth_min(arr, 0, n-1, opr[i].x);  //find value of kth_minimum of a_temp
        for(int j=0;j<n;j++){
            if(a_temp[j] == h){
                output[i] = j; //store index of kth minimum in output array
                break; 
            }
        }
    }

    cout<<"Output Array: ";
    for(int i=0;i<m;i++){
        cout<<output[i]<<" ";
    }

    return 0;
}