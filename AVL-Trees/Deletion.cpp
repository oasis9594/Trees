//Program to delete from an avl tree
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>//for max
using namespace std;
struct avl{
    int n;
    int height;
    avl *left, *right;
};
int get_height(avl *node)
{
    if(node==NULL)
        return 0;
    else
        return node->height;
}
avl *create_node(int val)
{
    avl *temp;
    temp=new avl;
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
int height_diff(avl* node)
{
    if(node==NULL)
        return 0;
    else
        return get_height(node->left)-get_height(node->right);
}
avl *right_rotate(avl *y)
{
    avl *x=y->left;
    avl *temp=x->right;
    x->right=y;
    y->left=temp;
    //UPDATE HEIGHTS
    y->height=max(get_height(y->left), get_height(y->right))+1;//NOTE:WE HAVE TO UPDATE y BEFORE x AS NOW y IS CHILD OF x
    x->height=max(get_height(x->left), get_height(x->right))+1;
    return x;
}
avl *left_rotate(avl*y)
{
    avl *x=y->right;
    avl *temp=x->left;
    x->left=y;
    y->right=temp;
    //UPDATE HEIGHTS
    y->height=max(get_height(y->left), get_height(y->right))+1;//NOTE:WE HAVE TO UPDATE y BEFORE x AS NOW y IS CHILD OF x
    x->height=max(get_height(x->left), get_height(x->right))+1;
    return x;
}
avl *node_insert(avl*root, int ele)
{
    if(root==NULL)
        return (create_node(ele));
    if(root->n > ele)
        root->left=node_insert(root->left, ele);
    else
        root->right=node_insert(root->right, ele);

    root->height=max(get_height(root->left), get_height(root->right)) + 1;//update height
    int balance=height_diff(root);//checking difference in height of left and right subtree
    //There are 4 cases
    // Left Left Case
    if (balance > 1 && ele < root->left->n)
        return right_rotate(root);

    // Right Right Case
    if (balance < -1 && ele > root->right->n)
        return left_rotate(root);

    // Left Right Case
    if (balance > 1 && ele > root->left->n)
    {
        root->left =  left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Left Case
    if (balance < -1 && ele < root->right->n)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}
avl* delete_node(avl* root, int ele)
{
    if(root==NULL)
        return root;
    if(root->n > ele)
        root->left=delete_node(root->left, ele);
    else if(root->n < ele)
        root->right=delete_node(root->right, ele);
    else
    {
        //root has 0 or 1 child
        if(root->left==NULL)
        {
            avl* temp=root;
            root=root->right;
            delete temp;
        }
        else if(root->right==NULL)
        {
            avl* temp=root;
            root=root->right;
            delete temp;
        }
        //root has 2 child
        else
        {
            avl*temp=root->right;
            while(temp->left!=NULL)
                temp=temp->left;
            root->n=temp->n;
            root->right=delete_node(root->right, temp->n);
        }
    }
    //IF tree had only one element
    if(root==NULL)
        return NULL;
    //UPDATE HEIGHTS
    root->height=max(get_height(root->left), get_height(root->right))+1;
    //BALANCE THE TREE
    int b=height_diff(root);
    if(b>1&&height_diff(root->left)>=0)
        return right_rotate(root);
    if(b<-1&&height_diff(root->right)<=0)
        return left_rotate(root);
    if(b>1&&height_diff(root->left)<0)
    {
        root->left=left_rotate(root->left);
        return right_rotate(root);
    }
    if(b<-1&&height_diff(root->right)>0)
    {
        root->right=right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}
void traverse(avl *temp)
{
    if(temp==NULL)
    {
        return;
    }
    traverse(temp->left);
    printf("\nnode: %d \theight: %d", temp->n, temp->height);
    traverse(temp->right);
}
void preOrder(avl *root)
{
    if(root != NULL)
    {
        printf("%d-->", root->n);
        preOrder(root->left);
        preOrder(root->right);
    }
}
int main()
{
    avl *root;
    root=NULL;
    int n;
    char ch='y';
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
    printf("\nPREORDER TRAVERSAL\n\n");
    preOrder(root);
    ch='y';
    while(ch=='y'||ch=='Y')
    {
        printf("Enter node to be deleted: ");
        scanf("%d", &n);
        root=delete_node(root, n);
        printf("\nIN SORTED ORDER ELEMENTS AND THEIR WEIGHTS\n\n");
        traverse(root);
        printf("\nPREORDER TRAVERSAL\n\n");
        preOrder(root);
        fflush(stdin);
        printf("\nDo u want to delete more elements?(y/n): ");
        scanf("%c", &ch);
    }

}
