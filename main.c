#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 5

typedef struct bnode
{
    int count;
    int keys[max-1];
    struct bnode *next[max];
}bnode;



bnode* makenode(void);

bnode* insert(bnode *root,int val);

void traverse(bnode *root);


int main()
{
    int n,i,x;
    bnode *root;
    root=NULL;
    root=makenode();
    
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

bnode* makenode(void)
{
    bnode *root=(bnode*)malloc(sizeof(bnode));
    int i;
    root->count=0;
    for (i=0; i<max; i++)
    {
        root->next[i]=NULL;
    }
    for (i=0; i<max-1; i++)
    {
        root->keys[i]=-1;
    }
    return root;
}

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
        
        if(ptr->next[pos]==NULL)
        {
            done=1;
           if(ptr->count != (max-1))
           {
               t=ptr->count;
               for(i=t;i>pos;i--)
               {
                   ptr->keys[i] = ptr->keys[i-1];
               }
               ptr->keys[pos] = val;
               ptr->count += 1;
            
           }
           else
           {
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

