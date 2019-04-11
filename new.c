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
    int n,i,x;
    bnode *root;
    root=NULL;
    root=makenode(0);
    
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
    int i=0,j;
    
    if(ptr!=NULL)
    {
        for (i=0; i<ptr->count+1; i++)
        {
            if(ptr->next[i]!=NULL)
            {
                traverse(ptr->next[i]);
                if(i < ptr->count )
                {
                    printf(" %d ",ptr->keys[i]);
                }
            }
            else
            {
                for (j=0; j<ptr->count; j++)
                {
                    printf(" %d  ",ptr->keys[j]);
                }
                i = 100;
            }
        }
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
            (root->u1.next2[i])->count=0;
        }
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
    int pos,i,flag=0,t,median,index_median,j;
    
    while(ptr != NULL && done == 0)
    {
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
        {
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
                    
                    for(j=0;j<sibling->count;j++)
                    {
                        sibling->keys[j] = t[i];
                        i++;
                    }
                    for(j=0;j<=sibling->count;j++)
                    {
                        sibling->u1.next2[i] = ptr->u1.next2[index_median+1+i];
                    }
                    //so we have splitted parent node
                    
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
                    ptr->u1.next2[i]->count=2;
                    
                    ptr->u1.next2[i]->arr[0] = temp[2];
                    ptr->u1.next2[i]->arr[1] = temp[3];
                    
                    ptr->u1.next2[pos]->count=2;
                    
                    ptr->u1.next2[pos]->arr[0] = temp[0];
                    ptr->u1.next2[pos]->arr[1] = temp[1];
                  ////////////////////////////////
                
                    
                    
                    
                    
                    
                }
                
            }//leaf wala case
            
        else
        {
            
        }
    }
                
                //median
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
                //
                
                int all_val[max]; j=0;
                for(i=0;i<ptr->count;i++)
                {
                    if(i==pos){ j++;}
                    all_val[j] = ptr->keys[i];
                    j++;
                }
                all_val[pos] = val;
                //to split
                
                ptr->count=1;
                ptr->keys[0] = median;
                
                temp    =  makenode();
                temp->count  =  (max-1)/2;
                for(i=0;i<temp->count;i++)
                {
                    temp->keys[i] = all_val[i];
                }
                ptr->next[0] = temp;
                
                temp   = makenode();
                temp->count=(max-1)/2;
                i++;
                for(j=0;j<temp->count;j++)
                {
                    temp->keys[j] = all_val[i];
                    i++;
                }
                ptr->next[1] = temp;
                
            }
            
        }
        else
        {
            
            
            child = ptr->next[pos];
            if(child->count == max-1)
            {
                //////////////////////////////
                if(ptr==root && ptr->count == max-1)
                {
                    index_median = (max-1)/2;
                    median = ptr->keys[index_median];
                    
                    temp = makenode();
                    temp->count = (max-1)/2 -1;
                    
                    for(j=0;j<temp->count;j++)
                    {
                        temp->keys[j] = ptr->keys[index_median+1+j];
                    }
                    
                    for(i=0;i<=temp->count;i++)
                    {
                        temp->next[i] = child->next[index_median+1+i];
                    }
                    
                    ptr->count = (max-1)/2;
                    bnode *nptr;
                    nptr = makenode();
                    nptr->count=1;
                    nptr->keys[0] = median;
                    nptr->next[0] = ptr;
                    nptr->next[1] = temp;
                    root = nptr;
                    if(val>median)
                    {
                        ptr = temp;
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
                    
                    child = ptr->next[pos];
                }
                
                //////////////////////////////////////////////////
                
                
                index_median = (max-1)/2;
                median = child->keys[index_median];
                //
                for(i=ptr->count;i>pos;i++)
                {
                    ptr->keys[i] = ptr->keys[i-1];
                }
                ptr->keys[pos] = median;
                ptr->count +=1;
                
                temp = makenode();
                temp->count = (max-1)/2 -1;
                
                for(j=0;j<temp->count;j++)
                {
                    temp->keys[j] = child->keys[index_median+1+j];
                }
                for(i=0;i<=temp->count;i++)
                {
                    temp->next[i] = child->next[index_median+1+i];
                }
                //shifting to insert child
                for(i=ptr->count;i>pos+1;i++)
                {
                    ptr->next[i] = ptr->next[i-1];
                }
                
                ptr->next[pos+1] = temp;
                child->count = (max-1)/2;
                if(val>median)
                {
                    child=temp;
                }
                
                
            }
            
            ptr = child;
            
        }
        
    }
    return root;
    
    
}


