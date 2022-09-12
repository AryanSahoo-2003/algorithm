#include <bits/stdc++.h>
using namespace std;

struct job{
    int id;
    int arrival;
    int priority;
    int process;
    int ins;
};

bool job_arrival(job a,job b){
    return a.arrival < b.arrival;
}
int s=0;
int t=0;
void maxHeapify(job heap[],int i){
    int l=2*i;
    int r=2*i+1;
    int largest=i;
    if(l<=s&&heap[l].priority>heap[i].priority)
        largest=l;
    if(r<=s&&heap[r].priority>heap[largest].priority)
        largest=r;
    if(largest!=i){
        swap(heap[i],heap[largest]);
        maxHeapify(heap,largest);
        
    }
}
job heap_get_max(job heap[]){
    if(s>=1){
        job m=heap[1];
        heap[1]=heap[s];
        maxHeapify(heap,1);
        s--;
        return m;
    }else throw;
}
void heapIncreaseKey(job heap[],int i,int key){
    if(heap[i].priority<key){
        heap[i].priority=key;
        while(i>1&&heap[i/2].priority<heap[i].priority){
            swap(heap[i],heap[i/2]);
            i/=2;
        }
    }

}
void maxHeapInsert(job heap[],job next){
    s++;
    heap[s]=next;
    int key=next.priority;
    heap[s].priority=-1;
    heap[s].ins=t;
    heapIncreaseKey(heap,s,key);
}


int main(){
    int n;
    cout<<"N=";
    cin>>n;
    job jobs[n];
    job heap[n+1];
    
    for(int i=0;i<n;i++){
        cout<<"Enter ID: ";
        cin>>jobs[i].id;
        cout<<"Enter Arrival Time:";
        cin>>jobs[i].arrival;
        cout<<"Enter Processing Time: ";
        cin>>jobs[i].process;
        cout<<"Enter Priority:";
        cin>>jobs[i].priority;
    }
    sort(jobs,jobs+n,job_arrival);

    int cur=0,out=0;

    while(out<n){
        if(s>=1&&(cur>=n||jobs[cur].arrival>t)){
            job done=heap_get_max(heap);
            t+=done.process;
            cout<<"ID="<<done.id<<", insert time="<<done.ins<<", start time="<<t-done.process<<'\n';
            out++;
        }
        if(s==0&&cur<n)t=max(t,jobs[cur].arrival);
        if(jobs[cur].arrival<=t&&cur<n){
            maxHeapInsert(heap,jobs[cur]);
            cur++;
        }
        
    }

    return 0;
}