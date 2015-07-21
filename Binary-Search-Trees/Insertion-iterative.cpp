//THIS PROGRAM MAKES A BST AND INSERTS ELEMENTS INTO IT PROVIDED BY USER AND THEN PRINTS THE RESULT IN SORTED ORDER
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
struct bst{
    int n;
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
    temp->n=val;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
void traverse(bst *temp)
{
    if(temp==NULL)
    {
        return;
    }
    traverse(temp->left);
    printf("%d-->", temp->n);
    traverse(temp->right);
}
int main()
{
    bst *newnode, *root;
    bst *parent;
    int n;
    char ch;
    printf("Enter value of root: ");
    scanf("%d", &n);
    root=create_node(n);
    fflush(stdin);
    printf("Do u want to enter more elements?(y/n): ");
    scanf("%c", &ch);
    while(ch=='y'||ch=='Y')
    {
        printf("Enter new node: ");
        scanf("%d", &n);
        parent=root;
        newnode=create_node(n);
        while(1)
        {
            if(parent->n > newnode->n)
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
        fflush(stdin);
        printf("Do u want to enter more elements?(y/n): ");
        scanf("%c", &ch);
    }
    printf("IN SORTED ORDER\n");
    traverse(root);
}
