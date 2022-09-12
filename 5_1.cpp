#include <bits/stdc++.h>
using namespace std;

bool flag = false; 

//define class "Node"
class Node{
    public:
    Node *left;
    Node *right;
    int height;
    int value;
};

//Function to create a new Node
Node* new_node(int value){ 
    Node* node = new Node();
    node->value = value; //store value of new element
    node->left = NULL; //left branch of new element will be NULL
    node->right = NULL; //right branch of new element will be NULL
    node->height = 1;

    return node;
}

//Function to get the height of a node
int get_height(Node *node){
    if(node == NULL){
        return 0;
    }
    else{
        return node->height; 
    }
}

//Function to perform Right Rotation on a node
Node *right_rotate(Node *r){
    Node *l = r->left;
    Node *temp = l->right;

    //Perform the rotation
    l->right = r;
    r->left = temp;

    //Update the heights of the changed branches
    r->height = 1 + max(get_height(r->left), get_height(r->right));
    l->height = 1 + max(get_height(l->left), get_height(l->right));

    return l; //return the new root
}

//Function to perform Left Rotation on a node
Node *left_rotate(Node *l){
    Node *r = l->right;
    Node *temp = r->left;

    //Perform the rotation
    r->left = l;
    l->right = temp;

    //Update the heights of the changed branches
    r->height = 1 + max(get_height(r->left), get_height(r->right));
    l->height = 1 + max(get_height(l->left), get_height(l->right));

    return r;   //return the new root
}

//Function to get the balance factor of a node
int get_BalanceFactor(Node *node){
    return get_height(node->left) - get_height(node->right); 
}

//Function to insert a node into AVL tree
Node* insert(Node *node, int value){
    if(node == NULL){
        cout<<"Node "<<value<<" inserted into tree."<<endl;
        return(new_node(value));
    }
    
    if(value == node->value){
        flag = true;   // New value can't be equal to a value which is already present in Tree
        cout<<"Duplicate element, hence discarded."<<endl;
        return node; 
    }

    else if(value < node->value){
        node->left = insert(node->left, value);   // Recursive call to go to left branch of current node
    }

    else if(value > node->value){
        node->right = insert(node->right, value); // Recursive call to go to right branch of current node
    }

    //Update height of current Node after Insertion
    node-> height = 1 + max(get_height(node->left), get_height(node->right));  

    int bf = get_BalanceFactor(node);   // Get the Balance Factor of the current node

    //Case when there is Left-Left imbalance
    if(bf> 1 && value < node->left->value){
        flag = true;
        cout<<"Left-Left Imbalance at "<<node->value<<".";
        cout<<" Balance Factor of "<<node->value<<" has become "<<bf<<".";
        cout<<" AVL Tree Property is restored after performing Right Rotation at "<<node->value<<endl;
        return right_rotate(node); // do right rotation
    }

    //Case when there is Right-Right imbalance
    if(bf< -1 && value > node->right->value){
        flag = true;
        cout<<"Right-Right Imbalance at "<<node->value<<".";
        cout<<" Balance Factor of "<<node->value<<" has become "<<bf<<".";
        cout<<" AVL Tree Property is restored after performing Left Rotation at "<<node->value<<endl;
        return left_rotate(node); //do left rotation
    }

    //Case when there is Left-Right imbalance
    if(bf> 1 && value > node->left->value){
        flag = true;
        cout<<"Left-Right Imbalance at "<<node->value<<".";
        cout<<" Balance Factor of "<<node->value<<" has become "<<bf<<".";
        cout<<" AVL Tree Property is restored after performing Left Rotation at "<<node->left->value;
        cout<<" and Right Rotation at "<<node->value<<endl;
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    //Case when there is Right-Left imbalance
    if(bf< -1 && value < node->right->value){
        flag = true;
        cout<<"Right-Left Imbalance at "<<node->value<<".";
        cout<<"Balance Factor of "<<node->value<<" has become "<<bf<<".";
        cout<<" AVL Tree Property is restored after performing Right Rotation at "<<node->left->value;
        cout<<" and Left Rotation at "<<node->value<<endl;
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    
    return node;
}

int main(){
    Node* root = NULL;  //Initialize tree
    int n, x;
    cout<<"Enter the number of queries(N): ";
    cin>>n;
    char temp; 

    for(int i=0;i<n;i++){
        cin>>temp>>x;   //Take Input
        
        /* Flag is used to check whether the AVL property is violated or not. If flag = true,
           AVL property got violated during insertion and necessary changes were made. */
        flag = false;  
        root = insert(root, x);     //Insert value into Tree
        if(flag == false){
            cout<<"No issue with AVL property."<<endl;
        }
    }

    return 0;
}