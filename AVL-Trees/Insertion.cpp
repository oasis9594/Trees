//Insertion in an AVL tree
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
struct avl{
    int n;
    int height;
    avl *left, *right;
};
int max(int a, int b)
{
    return (a > b)? a : b;
}
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
    temp->n=val;
    temp->height=1;
    temp->left=NULL;
    temp->right=NULL;
    return (temp);
}
int height_diff(avl* node)
{
    if(node==NULL)
        return 0;
    else
        return get_height(node->left) - get_height(node->right);
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
    int b=height_diff(root);//checking difference in height of left and right subtree
    //There are 4 cases
    // Left Left Case
   /*ALTERNATE METHOD OF BELOW CODE
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
    }*/
    if(b>1&&height_diff(root->left)>=0)//left left case
        return right_rotate(root);
    if(b<-1&&height_diff(root->right)<=0)//right right case
        return left_rotate(root);
    if(b>1&&height_diff(root->left)<0)//left right case
    {
        root->left=left_rotate(root->left);
        return right_rotate(root);
    }
    if(b<-1&&height_diff(root->right)>0)//right left case
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
    root=new avl;
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
}
