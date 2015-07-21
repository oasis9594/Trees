//deleting a node from bst
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
struct bst{
    int n;
    //int left_weight, right_weight;
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
bst* delete_node(bst *parent, int val)
{
    if(parent==NULL)
        return parent;
    if(parent->n > val)
        parent->left=delete_node(parent->left, val);
    else if(parent->n < val)
        parent->right=delete_node(parent->right, val);
    else
    {
        if(parent->left==NULL)
        {
            bst *temp=parent->right;
            delete parent;
            return temp;
        }
        else if(parent->right==NULL)
        {
            bst *temp=parent->left;
            delete parent;
            return temp;
        }
        else
        {
            bst *temp=parent->right;
            while(temp->left!=NULL)
                temp=temp->left;
            parent->n=temp->n;
            parent->right=delete_node(parent->right, temp->n);
        }
    }
    return parent;
}
int main()
{
    bst *newnode, *root;
    bst *parent;
    int n;
    char ch;
    printf("Enter value of root: ");
    scanf("%d", &n);
    root=new bst;
    root=create_node(n);
    fflush(stdin);
    printf("Do u want to enter more elements?(y/n): ");
    scanf("%c", &ch);
    while(ch=='y'||ch=='Y')
    {
        printf("Enter new node: ");
        scanf("%d", &n);
        parent=root;
        newnode=new bst;
        newnode=create_node(n);
        while(1)
        {
            if(parent->n > newnode->n)
            {
                if(parent->left!=NULL)
                    parent=parent->left;
                else
                {
                    parent->left=newnode;
                    break;
                }

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
    ch='y';
    while(ch=='y'||ch=='Y')
    {
        printf("\nEnter a node to be deleted: ");
        scanf("%d", &n);
        root=delete_node(root, n);
        traverse(root);
        fflush(stdin);
        printf("\nDo u want to delete more elements?(y/n): ");
        cin>>ch;
    }
    delete root;delete newnode;
    return 0;
}
