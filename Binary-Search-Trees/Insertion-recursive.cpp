//Prints height of each subtree
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
struct bst{
    int n;
    int height;
    bst *left, *right;
};
int get_height(bst *node)
{
    if(node==NULL)
        return 0;
    else
        return node->height;
}
bst *create_node(int val)
{
    bst *temp;
    temp=new bst;
    if(temp==NULL)
    {
        return NULL;
    }
    temp->n=val;
    temp->height=1;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
bst* node_insert(bst*root, int ele)//recursive implementation for insertion and we also have to backtrack to update heights
{
    if(root==NULL)
        return create_node(ele);
    if(root->n > ele)
        root->left=node_insert(root->left, ele);
    else
        root->right=node_insert(root->right, ele);
    root->height=max(get_height(root->left), get_height(root->right))+1;//update height
    return root;
}
void traverse(bst *temp)
{
    if(temp==NULL)
    {
        return;
    }
    traverse(temp->left);
    printf("\nnode: %d \theight: %d", temp->n, temp->height);
    traverse(temp->right);
}
int main()
{
    bst *newnode, *root;
    bst *parent;
    int n;
    char ch;
    root=new bst;
    root=NULL;
    fflush(stdin);
    ch='y';
    while(ch=='y'||ch=='Y')
    {
        printf("Enter new node: ");
        scanf("%d", &n);
        root=node_insert(root, n);
        fflush(stdin);
        printf("\nDo u want to enter more elements?(y/n): ");
        scanf("%c", &ch);
    }
    printf("\nIN SORTED ORDER ELEMENTS AND THEIR WEIGHTS\n\n");
    traverse(root);
}
