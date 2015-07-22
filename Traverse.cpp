//Traversing the binary search created tree in preorder, postorder and inorder
#include<iostream>
#include<cstdio>
struct bst{
    int key;
    bst *left, *right;
};
bst *create_node(int val)
{
    bst *temp;
    temp=new bst;
    if(temp==NULL)
    {
        return NULL;
    }
    temp->key=val;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
void inorder(bst *root)//traverses in inorder
{
    if(root==NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d-->", root->key);
    inorder(root->right);
}
void preorder(bst *root)//traverses in preorder
{
    if(root != NULL)
    {
        printf("%d-->", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(bst *root)//traverses in postorder
{
    if(root==NULL)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d-->", root->key);
}
//Simple bst insertion
void insert_node(bst **root, int n)
{
    if(*root==NULL)
    {
        *root=create_node(n);
        return;
    }
    bst*parent,*newnode;
    parent=*root;
    newnode=create_node(n);
    while(1)
    {
        if(parent->key > newnode->key)
        {
            if(parent->left!=NULL)
                parent=parent->left;
            else
            {parent->left=newnode;break;}
        }
        else
        {
            if(parent->right!=NULL)
                parent=parent->right;
            else
            {parent->right=newnode;break;}
        }
    }
    return ;
}
int main()
{
    bst*root;
    root=NULL;
    insert_node(&root, 16);
    insert_node(&root, 13);
    insert_node(&root, 30);
    insert_node(&root, 18);
    insert_node(&root, 15);
    insert_node(&root, 1);
    insert_node(&root, 20);
    insert_node(&root, 40);
    printf("\n\nInorder Traversal\n\n");
    inorder(root);
    printf("\n\nPreorder Traversal\n\n");
    preorder(root);
    printf("\n\nPostorder Traversal\n\n");
    postorder(root);
    return 0;
}
