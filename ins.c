#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 5
#define min 2

typedef struct datanode
{
    int count;
    struct datanode *left,*right;
    int arr[3];
}data;


typedef struct bnode
{
    int count;
    int keys[max-1];
    int leaf;
    union u
    {
        struct bnode *next1[max];
        data *next2[max];
    }u1;
}bnode;



bnode* makenode(int leaf);

bnode* insert(bnode *root,int val);

void traverse(bnode *root);

int insertSorted(int arr[], int n, int key, int capacity)
{
    // Cannot insert more elements if n is already
    // more than or equal to capcity
    if (n >= capacity)
        return n;
    
    int i;
    for (i=n-1; ( i >= 0  && arr[i] > key); i--)
        arr[i+1] = arr[i];
    
    arr[i+1] = key;
    
    return (n+1);
}



int main()
{
    int n,i;
    bnode *root;
    root=NULL;
    root=makenode(1);
    root->leaf=1;
    root->keys[0]=3;
    root->count=1;
    
    printf("enter the no. of values that you want to insert");
    scanf("%d",&n);
    
    
    for(i=1;i<=n;i++)
    {
        // printf("enter value");
        //scanf("%d",&x);
        root = insert(root,i);
    }
    traverse(root);
    return 0;
}

void traverse(bnode *root)
{
    bnode *ptr;
    ptr=root;
    data *p;
    while (ptr->leaf!=1)
    {
        ptr=ptr->u1.next1[0];
    }
    p=ptr->u1.next2[0];
    while (p)
    {
        if (p->count!=0)
        {
            for (int i=0; i<p->count; i++)
            {
                printf("  %d  ",p->arr[i]);
            }
        }
        p=p->right;
    }
    
}

bnode* makenode(int leaf)
{
    bnode *root=(bnode*)malloc(sizeof(bnode));
    int i;
    root->count=0;
    if(leaf==0)
    {
        for (i=0; i<max; i++)
        {
            root->u1.next1[i]=NULL;
        }
    }
    else
    {
        for (i=0; i<max; i++)
        {
            root->u1.next2[i]=(data*)malloc(sizeof(data));
        }
        for (i=0; i<max; i++)
        {
            
            (root->u1.next2[i])->count=0;
            if(i<max-1)
            { root->u1.next2[i]->right = root->u1.next2[i+1]; }
        }
        root->u1.next2[max-1]->right = NULL;
    }
    for (i=0; i<max-1; i++)
    {
        root->keys[i]=-1;
    }
    return root;
}


//makenode(0);

bnode* insert(bnode *root,int val)
{
    bnode *ptr,*temp,*child;
    int done=0;
    ptr = root;
    int pos = 0,i,flag=0,t,median,index_median,j;
    
    while(ptr != NULL && done == 0)
    {//1
        for(i=0;i<ptr->count && flag==0;i++)
        {
            if(val<ptr->keys[i])
            {
                flag=1;
                pos=i;
            }
        }
        if(flag==0)
        {
            pos = ptr->count;
        }
        //to find pos
        
        if(ptr->leaf==1)
        {//2
            done=1;
            if((ptr->u1.next2[pos])->count < 3)
            {
                (ptr->u1.next2[pos])->count=insertSorted((ptr->u1.next2[pos])->arr, (ptr->u1.next2[pos])->count, val, 3);
                
            }
            else
            {
                if(ptr->count!=max-1)
                {
                    int temp[4];
                    for(i=0;i<(ptr->u1.next2[pos])->count;i++)
                    {
                        temp[i] = (ptr->u1.next2[pos])->arr[i];
                    }
                    insertSorted(temp,3,val,4);
                    for(i=ptr->count;i>pos;i--)
                    {
                        ptr->keys[i] = ptr->keys[i-1];
                    }
                    ptr->keys[i] = temp[2];
                    
                    for(i=ptr->count+1;i>pos+1;i--)
                    {
                        ptr->u1.next2[i] = ptr->u1.next2[i-1];
                    }
                    ptr->count++;
                    ptr->u1.next2[i]->count=2;
                    
                    ptr->u1.next2[i]->arr[0] = temp[2];
                    ptr->u1.next2[i]->arr[1] = temp[3];
                    
                    ptr->u1.next2[pos]->count=2;
                    
                    ptr->u1.next2[pos]->arr[0] = temp[0];
                    ptr->u1.next2[pos]->arr[1] = temp[1];
                }
                else
                {
                    if(pos == (max-1)/2)
                    {
                        median = val;
                        index_median = pos;
                    }
                    else
                    {
                        if(pos > (max-1)/2)
                        {
                            index_median = (max-1)/2;
                            median = ptr->keys[index_median];
                        }
                        else
                        {
                            index_median = (max-1)/2-1;
                            median = ptr->keys[index_median];
                        }
                    }
                    
                    bnode *nptr,*sibling;
                    nptr = makenode(0);
                    sibling = makenode(1);
                    
                    nptr->count=1;
                    nptr->keys[0]=median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    nptr->leaf=0;
                    sibling->leaf=1;
                    root = nptr;
                    int t[max],j;
                    for(i=0;i<ptr->count;i++)
                    {
                        t[i] = ptr->keys[i];
                    }
                    insertSorted(t,ptr->count,val,max);
                    for(i=0;i<index_median;i++)
                    {
                        ptr->keys[i] = t[i];
                    }
                    ptr->count = sibling->count = i;
                    i++;
                    for(j=0;j<sibling->count;j++)
                    {
                        sibling->keys[j] = t[i];
                        i++;
                    }
                    for(j=0;j<sibling->count;j++)
                    {
                        *(sibling->u1.next2[j]) = *(ptr->u1.next2[index_median+1+j]);
                        ptr->u1.next2[index_median+1+j]->count=0;
                    }
                    //so we have splitted parent node
                    ptr->u1.next2[max-1]->right = sibling->u1.next2[0];
                    if(val>median)
                    {
                        ptr = sibling;
                        
                    }
                    done=0;
                    
                }
                
            }//leaf wala case
        }//2
        else
        {
            //ptr is an internal node
            if((ptr->u1.next1[pos])->count < max-1)
            {
                ptr = ptr->u1.next1[pos];
            }
            else
            {
                if(ptr->count == max-1)
                {
                    //splitting of parent node
                    index_median = (max-1)/2;
                    median = ptr->keys[index_median];
                    bnode *nptr,*sibling;
                    
                    sibling = makenode(0);
                    nptr = makenode(0);
                    sibling->leaf=0;
                    nptr->leaf=0;
                    nptr->count=1;
                    nptr->keys[0] = median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    root = nptr;
                    
                    sibling->count = (max-1)/2 -1;
                    for(i=0;i<sibling->count;i++)
                    {
                        sibling->keys[i] = ptr->keys[i+index_median+1];
                    }
                    
                    for(i=0;i<=sibling->count;i++)
                    {
                        sibling->u1.next1[i] = ptr->u1.next1[index_median+1+i];
                    }
                    
                    ptr->count = (max-1)/2;
                    
                    if(val>median)
                    {
                        ptr = sibling;
                    }
                    flag=0;
                    for(i=0;i<ptr->count && flag==0;i++)
                    {
                        if(val<ptr->keys[i])
                        {
                            flag=1;
                            pos=i;
                        }
                    }
                    if(flag==0)
                    {
                        pos = ptr->count;
                    }
                    
                    
                    
                    
                    nptr = ptr->u1.next1[pos];      //child
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    if(nptr->leaf==1)
                    {
                        bnode *sibling;
                        sibling = makenode(1);
                        sibling->count = (max-1)/2 - 1;
                        
                        index_median = (max-1)/2;
                        median = nptr->keys[index_median];
                        
                        
                        for(i=0;i<sibling->count;i++)
                        {
                            sibling->keys[i] = nptr->keys[index_median+1+i];
                        }
                        
                        for(i=0;i<=sibling->count;i++)
                        {
                            sibling->u1.next2[i] = nptr->u1.next2[index_median+1+i];
                            nptr->u1.next2[index_median+1+i]->count = 0;
                        }
                        
                        nptr->count = (max-1)/2;
                        nptr->u1.next2[max-1]->right = sibling->u1.next2[0];
                        
                        for(i=ptr->count;i>pos;i--)
                        {
                            ptr->keys[i] = ptr->keys[i-1];
                        }
                        ptr->keys[i] = median;
                        
                        for(i=ptr->count+1;i>pos+1;i--)
                        {
                            ptr->u1.next1[i] = ptr->u1.next1[i-1];
                        }
                        ptr->u1.next1[i] = sibling;
                        
                        
                        if(val>median)
                        {
                            ptr = sibling;
                        }
                        
                        flag=0;
                        
                        for(i=0;i<ptr->count && flag==0;i++)
                        {
                            if(val<ptr->keys[i])
                            {
                                flag=1;
                                pos=i;
                            }
                        }
                        if(flag==0)
                        {
                            pos = ptr->count;
                        }
                        
                        sibling->leaf=1;
                        
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    else
                    {
                        //ptr is parent
                        //nptr is child
                        bnode *sibling;
                        sibling = makenode(0);
                        
                        sibling->count = (max-1)/2 - 1;
                        sibling->leaf = 0;
                        index_median = (max-1)/2;
                        median = nptr->keys[index_median];
                        for(i=ptr->count;i>pos;i--)
                        {
                            ptr->keys[i] = ptr->keys[i-1];
                        }
                        ptr->keys[i] = median;
                        
                        for(i=ptr->count+1;i>pos+1;i--)
                        {
                            ptr->u1.next1[i] = ptr->u1.next1[i-1];
                        }
                        ptr->u1.next1[i] = sibling;
                        
                        for(i=0;i<sibling->count;i++)
                        {
                            sibling->keys[i] = nptr->keys[index_median+1+i];
                        }
                        for(i=0;i<=sibling->count;i++)
                        {
                            sibling->u1.next1[i] = nptr->u1.next1[index_median+i+1];
                        }
                        nptr->count = (max-1/2);
                        ptr->count ++;
                        if(val>median)
                        { ptr = sibling; }
                        
                    }
                    
                }
            }
        }//2
        
        
        
        
        
        
    }//1
    return root;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

