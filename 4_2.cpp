#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node(int d){
        data = d;
        left = NULL;
        right = NULL;
    }
        
    Node* insert(Node* root, int data) {
        if(root == NULL){
            return new Node(data);
        }
     else{
            Node* cur;
            if(data <= root->data) {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else {
                cur = insert(root->right, data);
                root->right = cur;
            }
        return root;
     }
    }
    //Searching function
    Node* search(Node* root, int key) {
            if(root == NULL || root->data == key)
                return root;

            // Key is greater than root's data
            if(root->data < key)
                return search(root->right,key);

            // Key is smaller than root's data
            return search(root->left,key);
         }
    
    void preorder(Node* root){
        if(root == NULL)
            return;
        
        //First read the data of child
        cout << root->data << " ";
        //Then recur on left subtree 
        preorder(root->left);
        //Then Recur on the right subtree
        preorder(root->right);
    }

    
    Node* deletenode(Node* root, int k){ 
        // Base case 
        if (root == NULL) 
            return root; 
        //If root->data is greater than k then we delete the root's subtree
        if(root->data > k){ 
            root->left = deletenode(root->left, k); 
            return root; 
        } 
        else if(root->data < k){ 
            root->right = deletenode(root->right, k); 
            return root; 
        } 
        // If one of the children is empty 
        if (root->left == NULL) { 
            Node* temp = root->right;
            delete root; 
            return temp; 
        } 
        else if (root->right == NULL) { 
            Node* temp = root->left; 
            delete root; 
            return temp; 
        } 
        else {
            Node* Parent = root;
            // Find successor of the node
            Node *succ = root->right; 
            while (succ->left != NULL) { 
                Parent = succ; 
                succ = succ->left; 
            } 

            if (Parent != root) 
                Parent->left = succ->right; 
            else
                Parent->right = succ->right; 

            // Copy Successor Data  
            root->data = succ->data; 

            // Delete Successor and return root 
            delete succ;          
            return root; 
        } 
    } 
};

int main(){
    Node Tree(0);
    Node* root = NULL;
    int n, k;
    cout<<"Enter value of n: ";
    cin>>n;
    cout<<"Enter value of k: ";
    cin>>k;

    int a[n], b[k], c=0;

    cout<<"enter A(separated by spaces): ";
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    cout<<"enter B(separated by spaces): ";
    for(int i=0;i<k;i++){
        cin>>b[i];
    }
    for(int i=0;i<n;i++){
        Node* find_element = Tree.search(root,a[i]);
        if(find_element == NULL){
            root = Tree.insert(root, a[i]);
        }
        else{
            cout<<"Insertion warning: "<<a[i]<<" already there in tree"<<endl;
            c=1;
        }
    }

    if(c==0){
        cout<<"Insertion warning: None"<<endl;
    }

    cout<<"Pre-Order: ";
    Tree.preorder(root);
    cout<<endl;

    for(int i=0;i<k;i++){
        Node* find_element = Tree.search(root,b[i]);
        if(find_element = NULL){
            Node* deleteelement = Tree.deletenode(root, b[i]);
            cout<<"Preorder after deleting "<<b[i]<<":";
            Tree.preorder(root);
            cout<<endl;
        }
        else{
            cout<<b[i]<<"not found in tree"<<endl;
        }
    }
    return 0;
}


