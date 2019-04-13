#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define rest 0
#define cafe 1
#define pub 2
#define max 5
#define min 2

typedef enum{no,yes} bool;
typedef enum{northindian,southindian,chinese,continental} ftype;
#define asgard 0
#define narnia 1
#define wallstreet 2
#define diagonalley 3
#define pinkcity 4
#define areas 5


#define south_indian 0
#define north_indian 1
#define continental 2
#define chinese 3

char address[5][20]={"asgard","narnia","wallstreet","diagonalley","pinkcity"};
int X[5]={1,4,3,2,6};
int Y[5]={4,5,3,1,3};


typedef struct item
{
    char name[20];
    float price;
    struct item *next;
}item;


typedef struct likes
{
    char name[20];
    int frequency;
    struct likes *next;
}likes;


typedef struct agent       //key
{
    char name[20];
    int id;
    char address[50];
    char phone[10];
    int add_code;
    float commission;
    bool isfree;
}agent;

typedef struct datan
{
    int count;
    struct datan *left,*right;
    agent arr[3];
}d_agent;


typedef struct bnode_agent
{
    int count;
    int keys[max-1];
    int leaf;
    union u
    {
        struct bnode_agent *next1[max];
        d_agent *next2[max];
    }u1;
}b_agent;






typedef struct spec{
    char name[20];
    struct spec *next;
}spec;


typedef struct outlet
{
    int id;
    int foodtype;
    char name[20];
    char address[20];
    int add_code;
    ftype type;
    int seats;
    item *menu;
    spec *facilities;
}outlet;

typedef struct don
{
    int count;
    struct don *left,*right;
    outlet arr[3];
}d_outlet;


typedef struct bnode
{
    int count;
    int keys[max-1];
    int leaf;
    union u2
    {
        struct bnode *next1[max];
        d_outlet *next2[max];
    }u1;
}b_outlet;


typedef struct order
{
    int uid;  //user id
    int oid;  //order id
    outlet *selected_outlet;
    agent *selected_agent;
    item *food;
    int totalprice;
    struct order *next;
}order;


typedef struct user_tag
{
    int id;
    char name[20];
    char address[20];
    char phone[10];
    int add_code;
    likes *favourites;
    order *history;
}user;

typedef struct datanode
{
    int count;
    struct datanode *left,*right;
    user arr[3];
}d_user;


typedef struct bnode_user
{
    int count;
    int keys[max-1];
    int leaf;
    union u1
    {
        struct bnode_user *next1[max];
        d_user *next2[max];
    }u1;
}b_user;




/*------------------------------------------------------*/



user *signed_user;
b_agent *agent_root;
b_user *user_root;
static int user_id=1;
static int agent_id=1;
static int order_id=1;
static int cat_id[3] = {1,1,1};
b_outlet *cat[3];
order *live_order;


/*------------------------------------------------------*/


void insert_agent(agent a,int val);
b_outlet* makenode_cat(int leaf);
void insert_user(user a,int val);
insert_outlet(outlet o,int val,int category);


void initialize_user(void);
void initialize_agents(void);
void initialize(void);
void addoutlet(int category_index,outlet *o,int food_category);
void traverse_outlet(b_outlet * outlet,int foodtype , int address);

void search_category(void);
void Sort_addresscodes(int arr[],int a);
void delivery(void);
int address_code(char[]);
order* assign_agent(order *o);
outlet* search_outlet(char name[]);
void initialize_agents(void);
void signup_user(void);
void signup_agent(void);
void signin_user(void);
void print_menu(outlet *o);
void cancel(void);
void place_order(void);
void db_outlet(int category,int food_type,char name[],char address[],int address_code,int seats,item *m,spec *s);

void owner_addoutlet(void);
void live_order_print(void);
void agents_area(void);
void agent_details(void);
item *make_item(char name[],float price);
void db(void);
spec* make_spec(char name[]);
likes* mergesort_frequency(likes* list);
likes* merge(likes* list1,likes* list2);
likes* divide(likes* list);
void add_item(void);

void file_agents(void);
void write_agents(void);
void file_user(void);
void write_user(void);
void writeoutlet(void);
void read_outlet(void);

void line()
{
    printf("\n--------------------------------\n");
}

/*------------------------------------------------------*/
/*------------------------------------------------------*/
/*------------------------------------------------------*/


int main()
{
    int choice,user_menu=1,running=1;
    order *ptr;
    initialize();
    initialize_agents();
    initialize_user();
    file_agents();
    file_user();
    read_outlet();
    
    //  db();
    while (running!=0)
    {
        printf("\nENTER 1 FOR USER \n2 TO APPLY FOR AGENT\n3 TO ACCESS ADMIN CONTROL \n0 TO EXIT \n");
        scanf("%d",&choice);
        if(choice==1)
        {
            int t;
            printf("\nENTER 1 FOR SIGNUP AND 2 FOR SIGNIN\n");
            scanf("%d",&t);
            if(t==1)
            {
                signup_user();
            }
            else
            {
                signin_user();
            }
            
            if (signed_user)
            {
                user_menu=1;
                while (user_menu!=0)
                {
                    line();
                    printf("1-browse the food outlets\n2-place an order\n3-see your past orders\n4-see your favorite food items \n5-confirm order delivery\n6-cancel order\n7-see user details\n8-logout\n9-find restaurant by name\n0-exit user portal");
                    line();
                    scanf("%d",&user_menu);
                    switch (user_menu)
                    {
                        case 1:
                            search_category();
                            break;
                        case 2:
                            place_order();
                            break;
                        case 3:
                            ptr=signed_user->history;
                            while (ptr)
                            {
                                item *f;
                                f=ptr->food;
                                while (f)
                                {
                                    printf("item: %s\nprice: %f \n",f->name,f->price);
                                    f=f->next;
                                }
                                ptr=ptr->next;
                            }
                            break;
                        case 4:
                        {
                            signed_user->favourites = mergesort_frequency(signed_user->favourites);
                            likes* temp = signed_user->favourites;
                            line();
                            while(temp!=NULL)
                            {
                                printf("item: %s\n",temp->name);
                                temp = temp->next;
                            }
                            
                        }break;
                        case 5:
                        {
                            int c;
                            printf("\nHave you RECIEVED you order?[1/0]\n");
                            scanf("%d",&c);
                            if (c==1)
                            {
                                delivery();
                            }
                        }break;
                        case 6:
                        {
                            int c;
                            printf("\nDo you wish to CANCEL your order?[1/0]\n");
                            scanf("%d",&c);
                            if (c==1)
                            {
                                cancel();
                            }
                        }break;
                        case 7:
                        {
                            line();
                            printf("name: %s \nuserid: %d \naddress: %s\ncontact: %s",signed_user->name,signed_user->id,signed_user->address,signed_user->phone);
                        }
                            break;
                            
                        case 8:{
                            int c;
                            printf("\nAre you sure you wish to SIGN OUT?[1/0]\n");
                            scanf("%d",&c);
                            if (c==1)
                            {
                                signed_user=NULL;
                                user_menu=0;
                                line();
                                printf("you have signed out\n");
                            }else
                            {
                                printf("CONTINUE with another action \n");
                            }
                        }break;
                        case 9:
                        {
                            char out[20];
                            outlet *ptr;
                            item *menu_temp;
                            printf("enter OUTLET name\n");
                            scanf("%s",out);
                            ptr=search_outlet(out);////?????????
                            if (ptr) {
                                line();
                                printf("food outlet name: %s\nNumber of seats: %d\nAddress:  %s",ptr->name,ptr->seats,ptr->address);
                                line();
                                menu_temp = ptr->menu;
                                while(menu_temp!=NULL)
                                {
                                    printf("item name: %s\n price: %f",menu_temp->name,menu_temp->price);
                                    menu_temp = menu_temp->next;
                                }
                            }
                            
                        }break;
                        case 0:
                            user_menu=0;
                        default:
                            break;
                    }
                }
                
            }else
            {
                printf("please SIGN IN first\n");
            }
        }
        else if(choice==2)
        {
            signup_agent();
        }
        else if (choice==3)
        {
            int admin=1;
            {
                while (admin!=0)
                {
                    line();
                    printf("ENTER 1 TO ADD A RESTAURANT\n2 TO ADD ITEM IN A OUTLET\n3 SHOW ALL LIVE ORDERS\n4 SHOW AREA WISE AGENTS\n5 SHOW AGENT DETAILS \n0 EXIT ADMIN CONTROL\n");
                    line();
                    scanf("%d",&admin);
                    
                    switch (admin) {
                        case 1:
                            owner_addoutlet();
                            break;
                        case 2:
                            add_item();
                            break;
                        case 3:
                            live_order_print();
                            break;
                        case 4:
                            agents_area();
                            break;
                        case 5:
                            agent_details();
                            break;
                        case 0:  printf("\nEXITING admin control");
                            break;
                        default: printf("\nenter valid choice");
                            break;
                    }
                    
                }
            }
            
            
        }
        else
        {
            running=0;
        }
    }
    
    return 0;
}
/*------------------------------------------------------*/
/*------------------------------------------------------*/
/*------------------------------------------------------*/


b_outlet* makenode_cat(int leaf)
{
    b_outlet *root=(b_outlet*)malloc(sizeof(b_outlet));
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
            root->u1.next2[i]=(d_outlet*)malloc(sizeof(d_outlet));
        }
        for (i=0; i<max; i++)
        {
            
            (root->u1.next2[i])->count=0;
            int x;
            for(x=0;x<3;x++)
            {
               (root->u1.next2[i])->arr[x].menu = NULL;
               (root->u1.next2[i])->arr[x].facilities = NULL;
            }

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

void initialize()
{
    int i;
    for(i=0;i<3;i++)
    {
        cat[i] = makenode_cat(1);
        cat[i]->leaf=1;
        cat[i]->keys[0]=4;
        cat[i]->count=1;
    }
}
/*------------------------------------------------------*/

/*------------------------------------------------------*/


int distance(int first,int second)
{
    int d;
    d=(X[first]-X[second])*(X[first]-X[second])+(Y[first]-Y[second])*(Y[first]-Y[second]);
    return d;
}


/*------------------------------------------------------*/


void print_menu(outlet *o)
{
    item *ptr;
    ptr=o->menu;
    while (ptr)
    {
        printf("item name: %s\nprice: %f",ptr->name,ptr->price);
        ptr=ptr->next;
    }
}

/*------------------------------------------------------*/


void Sort_addresscodes(int arr[],int a)
{
    
    int i, key, j;
    for (i = 1; i < 5; i++)
    {
        key = arr[i];
        j = i-1;
        while (j >= 0 && distance(arr[j],a) >distance(key, a))
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
    
}


/*_________________________________________________*/



void db_outlet(int category,int food_type,char name[],char address[],int address_code,int seats,item *m,spec *s)
{
    outlet *o;
    o=(outlet*)malloc(sizeof(outlet));
    o->menu=NULL;
    o->facilities=NULL;
    strcpy(o->name,name);
    strcpy(o->address, address);
    o->add_code=address_code;
    o->seats=seats;
    m->next=o->menu;
    o->menu=m;
    s->next=o->facilities;
    o->facilities=s;
    o->next=cat[category].type[food_type];
    cat[category].type[food_type]=o;
    
}


/*------------------------------------------------------*/


void db()
{
    db_outlet(cafe, continental, "fuel_station", "asgard", asgard, 25, make_item("sandwich", 50), make_spec("wifi"));
    db_outlet(rest, chinese, "nankings", "wallstreet", wallstreet, 15, make_item("noodles", 100), make_spec("chopsticks"));
    db_outlet(pub,north_indian, "locals", "pinkcity", pinkcity, 30, make_item("fries",250), make_spec("dj"));/*change*/
    db_outlet(rest, south_indian, "veeraswami", "diagonalley", diagonalley, 45, make_item("idli", 20), make_spec("fun_area"));
    
}


/*------------------------------------------------------*/


void traverse_outlet(b_outlet * out,int foodtype , int address)
{
    
    b_outlet *ptr=out;
    d_outlet *p;
    outlet o;
    item *menu_temp;
    int i=0;
    
    while (ptr->leaf!=1)
    {
        ptr=ptr->u1.next1[0];
    }
    p=ptr->u1.next2[0];
    if (address==-1)
    {
        
        while (p)
        {
            if (p->count!=0)
            {
                for (int i=0; i<p->count; i++)
                {
                    o=p->arr[i];
                    if (foodtype==-1)
                    {
                        line();
                        
                        printf("Food outlet name: %s\nNumber of seats: %d\nAddress: %s\nAddress code:%d\n",o.name,o.seats,o.address,o.add_code);
                        line();
                        menu_temp = o.menu;
                        while(menu_temp!=NULL)
                        {
                            printf("\nitem name: %s\nprice: %f\n\n",menu_temp->name,menu_temp->price);
                            menu_temp = menu_temp->next;
                        }
                    }else
                    {
                        if (o.foodtype==foodtype)
                        {
                            
                            line();
                            
                            printf("Food outlet name: %s\nNumber of seats: %d\nAddress: %s\nAddress code:%d\n",o.name,o.seats,o.address,o.add_code);
                            line();
                            menu_temp = o.menu;
                            while(menu_temp!=NULL)
                            {
                                printf("\nitem name: %s\nprice: %f\n\n",menu_temp->name,menu_temp->price);
                                menu_temp = menu_temp->next;
                            }
                        }
                    }
                    
                    
                    
                }
            }
            p=p->right;
        }
        
    }
    else
    {
        int a[5]={0,1,2,3,4};
        Sort_addresscodes(a,signed_user->add_code);
        while (p)
        {
            if (p->count!=0)
            {
                for (int i=0; i<p->count; i++)
                {
                    o=p->arr[i];
                    if (o.add_code==a[0]||o.add_code==a[1]||o.add_code==a[2])
                    {
                        if (foodtype==-1)
                        {
                            line();
                            
                            printf("Food outlet name: %s\nNumber of seats: %d\nAddress: %s\nAddress code:%d\n",o.name,o.seats,o.address,o.add_code);
                            line();
                            menu_temp = o.menu;
                            while(menu_temp!=NULL)
                            {
                                printf("\nitem name: %s\nprice: %f\n\n",menu_temp->name,menu_temp->price);
                                menu_temp = menu_temp->next;
                            }
                        }else
                        {
                            if (o.foodtype==foodtype)
                            {
                                
                                line();
                                
                                printf("Food outlet name: %s\nNumber of seats: %d\nAddress: %s\nAddress code:%d\n",o.name,o.seats,o.address,o.add_code);
                                line();
                                menu_temp = o.menu;
                                while(menu_temp!=NULL)
                                {
                                    printf("\nitem name: %s\nprice: %f\n\n",menu_temp->name,menu_temp->price);
                                    menu_temp = menu_temp->next;
                                }
                            }
                        }
                    }
                }
            }
            p=p->right;
        }
        
        
    }
    
}
/*------------------------------------------------------*/


void search_category()                             ///////////////
{
    int t,index1,i,address=-1,j;
    outlet *ptr;
    b_outlet *select;
    line();
    printf("enter the CATEGORY of food outlet you wish to view \n1-restaurant  \n2-cafe \n3-pub  \n4-all?\n");
    scanf("%d",&t);
    
    index1=t-1;
    
    printf("what FOOD CATEGORY do you wish to view? \n 1-southindian  \n 2-northindian  \n3-chinese  \n4-continental \n-1-all \n");
    scanf("%d",&t);
    
    
    printf("\ndo you wish to see only NEARBY food outlets?[1/-1]\n");
    scanf("%d",&address);
    
    if (address!=(-1))
    {
        address = signed_user->add_code;
    }
    
    if(index1<3)
    {
        select=cat[index1];
        traverse_outlet(select, t, address);
       
    }
    else
    {
        
        for (i=0; i<3; i++)
        {
            select=cat[i];
            traverse_outlet(select, t, address);
            
        }
        
    }
    
}
/*------------------------------------------------------*/

void read_outlet()
{
    FILE *fp;
    outlet o;
    item *i;
    spec *s;
    float price;
    char name[20],address[20],in[20],f[20];
    int ad_code,seats,category,food_type,f2,f3;
    fp=fopen("/Users/shikhagupta/Desktop/hungryapp/hungryapp/outlet.txt", "r");
    if (fp==NULL) {
        printf("error opening\n");
        exit(1);
    }else
    {
        while ((fscanf(fp, "%d %d %d %d %s %s\n",&category,&food_type,&seats,&ad_code,name,address)!=EOF))
        {
            
            strcpy(o.name,name);
            o.add_code=ad_code;
            strcpy(o.address,address);
            o.seats=seats;
            o.foodtype=food_type;
            o.menu=NULL;
            o.facilities=NULL;
            f2=0;
            while (f2==0)
            {
                fscanf(fp, "%s %f\n",in,&price);
                
                if (strcmp(in, "menuover")==0)
                {
                    f2=1;
                }
                else
                {
                    i=(item*)malloc(sizeof(item));
                    strcpy(i->name,in);
                    i->price=price;
                    i->next=o.menu;
                    o.menu=i;
                }
            }
            f3=0;
            while (f3==0)
            {
                fscanf(fp, "%s\n",f);
                
                if (strcmp(f, "specover")==0)
                {
                    f3=1;
                }else
                {
                    s=(spec*)malloc(sizeof(spec));
                    strcpy(s->name,f);
                    s->next=o.facilities;
                    o.facilities=s;
                }
            }
            
            insert_outlet(o,o.id,category);
            
        }
        
    }
    fclose(fp);
}
/*------------------------------------------------------*/
void writeoutlet()
{
    outlet o;
    int i,j;
    FILE *fp;
    item *it;
    spec *s;
    b_outlet *ptr;
    d_outlet *p;
    fp=fopen("/Users/shikhagupta/Desktop/hungryapp/hungryapp/outlet.txt", "w");
    if (fp==NULL) {
        printf("error opening\n");
        exit(1);
    }else
    {
        for (i=0; i<3; i++)
        {
            
            ptr=cat[i];
            
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
                        fprintf(fp, "%d %d %d %d %s %s\n",i,o.foodtype,o.seats,o.add_code,o.name,o.address);
                        it=o.menu;
                        while (it)
                        {
                            fprintf(fp, "%s %f\n",it->name,it->price);
                            it=it->next;
                        }
                        fprintf(fp, "menuover 0\n");
                        s=o.facilities;
                        while (s)
                        {
                            fprintf(fp, "%s\n",s->name);
                            s=s->next;
                        }
                        fprintf(fp, "specover\n");
                    }
                }
                p=p->right;
            }
        }
        
    }
    fclose(fp);
    
}

void file_user()
{
    FILE *fp;
    user a;
    char uname[20];
    int uid,freq;
    char address[20];
    char contact[10];
    char fname[20];
    float price;
    int ad_code;
    int acount=0;
    int f1=0,f2=0,f3=0;
    item *i;
    order *o;
    likes *l;
    fp=fopen("/Users/shikhagupta/Desktop/hungryapp/hungryapp/user.txt", "r");
    if (fp==NULL) {
        printf("error opening\n");
        exit(1);
    }else
    {
        
        while ((fscanf(fp, "%d %d %s %s %s\n",&uid,&ad_code,uname,address,contact)!=EOF))
        {
            
            a.id=uid;
            a.add_code=ad_code;
            strcpy(a.name,uname);
            strcpy(a.address, address);
            strcpy(a.phone, contact);
            a.history=NULL;
            a.favourites=NULL;
            f2=0;
            while (f2==0)
            {
                o=(order*)malloc(sizeof(order));
                o->food=NULL;
                f1=0;
                while ((f1==0)&&(f2==0))
                {
                    fscanf(fp, "%s %f\n",fname,&price);
                    if (strcmp(fname,"nil")==0)
                    {
                        f1=1;
                    }else if (strcmp(fname, "endorder")==0)
                    {
                        f2=1;
                    }
                    else
                    {
                        i=(item*)malloc(sizeof(item));
                        strcpy(i->name,fname);
                        i->price=price;
                        i->next=o->food;
                        o->food=i;
                    }
                }
                if (o->food)
                {
                    o->next=a.history;
                    a.history=o;
                }
                
            }
            f3=0;
            while (f3==0)
            {
                fscanf(fp, "%s %d\n",fname,&freq);
                if(strcmp(fname,"endfreq")==0)
                {
                    f3=1;
                }
                else
                {
                    
                    l = (likes*)malloc(sizeof(likes));
                    l->frequency = freq;
                    strcpy(l->name,fname);
                    l->next = a.favourites;
                    a.favourites = l;
                }
            }
            insert_user(a,a.id);
            acount++;
        }
    }
    user_id=acount+1;
    fclose(fp);
}

void write_user()
{
    FILE *fp;
    user u;
    order *o;
    item *it;
    likes *l;
    int i;
    
    b_user *ptr;
    ptr=user_root;
    d_user *p;
    
    fp=fopen("/Users/shikhagupta/Desktop/hungryapp/hungryapp/user.txt", "w");
    if (fp==NULL) {
        printf("error opening\n");
        exit(1);
    }else
    {
        
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
                    u=p->arr[i];
                    
                    fprintf(fp, "%d %d %s %s %s\n",u.id,u.add_code,u.name,u.address,u.phone);
                    o = u.history;
                    while(o!=NULL)
                    {
                        it = o->food;
                        while(it!=NULL)
                        {
                            fprintf(fp,"%s %f\n",it->name,it->price);
                            it = it->next;
                        }
                        fprintf(fp, "nil %d\n",0);
                        o = o->next;
                    }
                    fprintf(fp, "endorder %d\n",0);
                    l=u.favourites;
                    while (l!=NULL)
                    {
                        fprintf(fp, "%s %d\n",l->name,l->frequency);
                        l=l->next;
                    }
                    fprintf(fp, "endfreq %d\n",0);
                }
            }
            p=p->right;
        }
        
    }
    fclose(fp);
}





void file_agents()
{
    FILE *fp;
    agent a;
    
    
    
    char aname[20];
    int aid;
    char address[20];
    char contact[10];
    float commission;
    int ad_code;
    int acount=0;
    fp=fopen("/Users/shikhagupta/Desktop/hungryapp/hungryapp/db.txt", "r");
    if (fp==NULL) {
        printf("error opening\n");
        exit(1);
    }else
    {
        while ((fscanf(fp, "%d %d %s %s %s %f\n",&aid,&ad_code,aname,address,contact,&commission)!=EOF))
        {
            
            
            a.id=aid;
            a.commission=commission;
            a.add_code=ad_code;
            strcpy(a.name, aname);
            strcpy(a.address, address);
            strcpy(a.phone, contact);
            acount++;
            insert_agent(a,aid);
        }
    }
    agent_id=acount+1;
    fclose(fp);
}


void write_agents()
{
    FILE *fp;
    agent a;
    int i;
    b_agent *ptr;
    ptr=agent_root;
    d_agent *p;
    fp=fopen("/Users/shikhagupta/Desktop/hungryapp/hungryapp/db.txt", "w");
    if (fp==NULL) {
        printf("error opening\n");
        exit(1);
    }else
    {
        
        
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
                    a=p->arr[i];
                    fprintf(fp, "%d %d %s %s %s %f\n",a.id,a.add_code,a.name,a.address,a.phone,a.commission);
                }
            }
            p=p->right;
        }
    fclose(fp);
    
}




/*------------------------------------------------------*/


/*------------------------------------------------------*/



item *make_item(char name[],float price)
{
    item *i;
    i=(item*)malloc(sizeof(item));
    strcpy(i->name,name);
    i->price=price;
    return i;
}

/*------------------------------------------------------*/


spec* make_spec(char name[])
{
    spec *s;
    s=(spec*)malloc(sizeof(spec));
    strcpy(s->name, name);
    return s;
}

/*------------------------------------------------------*/


void place_order()
{
    
    int choice,i,t;
    char name[50];
    
    order *new_order;
    new_order = (order*)malloc(sizeof(order));
    new_order->next=NULL;
    printf("If you want to see our OUTLETS enter 1 else 0\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        traverse_cat();    ////
    }
    
    printf("Enter the id of restaurant");
    scanf("%d",t);
    
    new_order->uid = signed_user->id;
    new_order->oid = order_id;
    order_id++;
    new_order->selected_outlet = search_outlet(t);        //change search outlet fun
    new_order->totalprice=0;
    printf("Do you wish to see MENU?[1/0]");
    scanf("%d",&choice);
    if(choice==1)
    {
        print_menu(new_order->selected_outlet);
    }
    item *new_menu,*nptr,*ptr;
    new_menu = NULL;
    
    printf("Enter the no. of items that you want to ORDER\n");
    scanf("%d",&choice);
    
    printf("Enter the names of item to ORDER\n");
    int found;
    
    for(i=0;i<choice;i++)
    {
        
        printf("enter item name \n");
        scanf("%s",name);
        ptr = (new_order->selected_outlet)->menu;
        found=0;
        while(ptr!=NULL && found==0)
        {
            if(strcmp(ptr->name,name)==0)
            {
                new_order->totalprice += ptr->price;
                found=1;
                nptr = (item*)malloc(sizeof(item));
                strcpy(nptr->name,ptr->name);
                nptr->price = ptr->price;
                nptr->next = new_menu;
                new_menu = nptr;
            }
            else
            {
                ptr = ptr->next;
            }
        }
        if (found==0)
        {
            printf("item NOT FOUND");
        }
        
        
    }
    
    
    new_order->food = new_menu;
    new_order = assign_agent(new_order);
    
}


/*_________________________________________________*/



order* assign_agent(order *o)
{
    
    int i,found=0;
    agent *selected_agent = NULL;
    d_agent * p=getptr_agent();
    while (p&&found==0)
    {
        if (p->count!=0)
        {
            for (int i=0; i<p->count&&found==0; i++)
            {
                if (p->arr[i].isfree==yes)
                {
                    found=1;
                    p->arr[i].isfree = no;
                    selected_agent = &(p->arr[i]);
                }
            }
        }
        p=p->right;
    }
    
    
   
    if (found==1)
    {
        o->selected_agent=selected_agent;
        o->next=live_order;
        live_order=o;
        printf("\nYOUR ORDER HAS BEEN PLACED SUCCESSFULLY !!! USE %d AS YOUR ORDER ID\n",o->oid);
    }
    else
    {
        free(o);
        o=NULL;
        printf("\n No free agents available ,please try later\n");
    }
    
    
    return o;
}


/*---------------------------------------*/


void print_outlet(void)
{
    char name[20];
    outlet *s;
    int t;
    spec *f;
    printf("Enter restaurant id\n");
    scanf("%d",t);
    s=search_outlet(t);
    if (s)
    {
        printf("Restaurant name: %s\nRestaurant address: %s\n",s->name,s->address);
        printf("Menu items are: \n");
        print_menu(s);
        f=s->facilities;
        while (f)
        {
            printf("Feature: %s\n",f->name);
            f=f->next;
        }
        printf("Number of seats: %d\n",s->seats);
    }else{
        line();
        printf("NO RESTAURANT FOUND ,PLEASE CHECK RESTAURANT NAME AND TRY AGAIN\n");
    }
}

/*------------------------------------------------------*/


void live_order_print()
{
    order *ptr;
    item *i;
    ptr=live_order;
    while (ptr)
    {
        printf("agent: %s\nrestaurant: %s",(ptr->selected_agent)->name,(ptr->selected_outlet)->name);
        printf("Items are: \n");
        i=ptr->food;
        while (i)
        {
            printf("Name: %s\nprice: %f",i->name,i->price);
            i=i->next;
        }
        printf("Total bill amount: %d\n",ptr->totalprice);
        ptr=ptr->next;
        
    }
}


/*------------------------------------------------------*/
d_outlet* getptr_outlet(int i)
{
   b_outlet* ptr = cat[i];
   while(ptr->leaf!=1)
   {
     ptr = ptr->u1.next1[0];
   }

   d_outlet *p;
   p = ptr->u1.next2[0];
   return p;   
}



outlet* search_outlet(int t)
{
    int i,j,found=0;
    d_outlet *ptr;
    outlet *search;

    for(j=0;j<3 && found==0 ;j++)
    {
       ptr = getptr_outlet(j);
       while(ptr!=NULL && found==0)
       {
          for(i=0;i<ptr->count && found==0;i++)
          {
             if(ptr->arr[i].id == t)
             { found=1; search = &(ptr->arr[i]);}
          }
          ptr = ptr->right;
       }

    }
    
    return search;
}



b_user* makenode_user(int leaf)
{
    b_user *root=(b_user*)malloc(sizeof(b_user));
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
            root->u1.next2[i]=(d_user*)malloc(sizeof(d_user));
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


/*_________________________________________________*/


void initialize_user()
{
    user_root = NULL;
    user_root = makenode_user(1);
    user_root->leaf=1;
    user_root->keys[0]=4;
    user_root->count=1;
}

/*_________________________________________________*/



void delivery()
{
    int found=0,id;
    order *ptr,*prev,*old = NULL;
    int o_id;
    printf("enter the orderid\n");
    scanf("%d",&o_id);
    agent *tobefreed;
    ptr=live_order;
    prev=NULL;
    
    
    while (ptr!=NULL && found==0)
    {
        id=ptr->uid;
        if (id==signed_user->id && ptr->oid==o_id)
        {
            found=1;
            if(prev!=NULL)
            {
                prev->next = ptr->next;
            }
            else
            {
                live_order = ptr->next;
            }
            old=ptr;
            
        }
        else
        {
            prev=ptr;
            ptr=ptr->next;
        }
    }
    if (found==1)
    {
        old->next = signed_user->history;
        signed_user->history = old;
        
        tobefreed=old->selected_agent;
        tobefreed->commission += (0.1) * old->totalprice;
        
        item *menu_;
        likes *temp;
        menu_ = old->food;
        while(menu_!=NULL)
        {
            temp = signed_user->favourites;
            int flag=0;
            while(temp!=NULL && flag==0)
            {
                if(strcmp(temp->name,menu_->name)==0)
                {
                    temp->frequency +=1; flag=1;
                }
                else
                {
                    temp = temp->next;
                }
            }
            if(flag==0)
            {
                temp = (likes*)malloc(sizeof(likes));
                temp->frequency = 1;
                strcpy(temp->name,menu_->name);
                temp->next = signed_user->favourites;
                signed_user->favourites = temp;
            }
            menu_ = menu_->next;
        }
        tobefreed->isfree = yes;
        
    }
    else
    {
        printf("NO LIVE ORDER FROM THIS ID");
    }
    
}


/*------------------------------------------------------*/


void owner_addoutlet()
{
    outlet *new_outlet;
    item *new_item;
    spec *s;
    new_outlet=(outlet*)malloc(sizeof(outlet));
    new_outlet->menu=NULL;
    new_outlet->facilities=NULL;

    int outlet_type,food_category,c=1;
    line();

    printf("enter outlet type>\n1>restaurant\n2>cafe\n3>pub\n");
    scanf("%d",&outlet_type);
    outlet_type=outlet_type-1;

    printf("enter outlet type>\n1>south_indian\n2>nothindian\n3>continental\n4>chinese\n");
    scanf("%d",&food_category);
     
    new_outlet->ftype = food_category-1;
    printf("enter outlet name\n");
    scanf("%s",new_outlet->name);
    printf("enter outlet address\n");
    scanf("%s",new_outlet->address);
    new_outlet->add_code=address_code(new_outlet->address);
    printf("\n enter number of seats\n");
    scanf("%d",&new_outlet->seats);
    printf("do you wish to enter menu item?[1/0]\n");
    scanf("%d",&c);
    while (c==1)
    {
        new_item=(item*)malloc(sizeof(item));
        printf("enter item name\n");
        scanf("%s",new_item->name);
        printf("enter item price\n");
        scanf("%f",&new_item->price);
        new_item->next=new_outlet->menu;
        new_outlet->menu=new_item;
        printf("do you wish to enter MENU ITEM?[1/0]\n");
        scanf("%d",&c);
        
    }
    printf("do you wish to enter SPECIAL FEATURES?[1/0]\n");
    scanf("%d",&c);
    while (c==1)
    {
        s=(spec*)malloc(sizeof(spec));
        printf("enter feature name\n");
        scanf("%s",s->name);
        s->next=new_outlet->facilities;
        new_outlet->facilities=s;
        printf("do you wish to enter another special feature?[1/0]\n");
        scanf("%d",&c);
    }
    new_outlet->id = cat_id[food_category];
    cat_id[food_category]++;

    insert_outlet(new_outlet,outlet_type,new_outlet->id);                   ////////////////
    
}

/*------------------------------------------------------*/

/*--------------------------------------------------------*/
d_user* getptr_agent()
 {
	   b_agent* ptr = agent_root;
	   d_agent *p;
	   while(ptr->leaf!=1)
	   {
		   ptr = ptr->u1.next1[0];
	   }
	   
	    p = ptr->u1.next2[0];
	   return p;
 }



void agent_details()
{
  //agent details areawise
   
    d_user *ptr = getptr_agent();
    d_user *temp;
    int i,count=0;
   
    while(count<4)
    {
       ptr = temp;
       printf("agents assigned to area: %s are: ",address[count]);
           while (ptr)
           {

		     for(i=0;i<ptr->count;i++)
		     {
                          if(ptr->arr[i].add_code == count)
		          {  
                              printf("name: %s\n contact: %s\n address: %s\n",ptr->arr[i].name,ptr->arr[i].phone,ptr->arr[i].address);
		              line();
                          }
		     }
		    
                ptr = ptr->right;
           }
        count++;
    }    

}


/*_________________________________________________*/



void cancel()
{
    int id,found=0;
    order *ptr,*prev,*old = NULL;
    agent *tobefreed;
    int o_id;
    printf("enter your order id\n");
    scanf("%d",&o_id);
    
    ptr=live_order;
    prev=NULL;
    
    while (ptr!=NULL && found==0)
    {
        id=ptr->uid;
        if (id==signed_user->id && ptr->oid==o_id)
        {
            found=1;
            if(prev!=NULL)
            {
                prev->next = ptr->next;
            }
            else
            {
                live_order = ptr->next;
            }
            old=ptr;
            ptr = ptr->next;
        }
        else
        {
            prev=ptr;
            ptr=ptr->next;
        }
    }
    
    if (found==1)
    {
        
        tobefreed=old->selected_agent;
        tobefreed->isfree = yes;
        free(old);
        printf("YOUR ORDER HAS BEEN CANCELLED SUCCESSFULLY\n");
    }
    else
    {
        printf("NO LIVE ORDER FROM THIS ID");
    }
    
}


/*_________________________________________________*/


int address_code(char str[])
{
    char s;
    int a=-1;
    s=str[0];
    switch (s)
    {
        case 'a':
            a=0;
            break;
        case 'n':
            a=1;
            break;
        case 'w':
            a=2;
            break;
        case 'd':
            a=3;
            break;
        case 'p':
            a=4;
            break;
            
        default:
            break;
    }
    return a;
}


b_agent* makenode_agent(int leaf)
{
    b_agent *root=(b_agent*)malloc(sizeof(b_agent));
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
            root->u1.next2[i]=(d_agent*)malloc(sizeof(d_agent));
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



void initialize_agents()
{
    agent_root = NULL;
    agent_root = makenode_agent();
    agent_root->leaf=1;
    agent_root->keys[0]=4;
    agent_root->count=1;
}


/*_________________________________________________*/


void signup_agent()
{
    
    agent temp;
    
    printf("enter your name\n");
    scanf("%s",temp.name);
    
    printf("enter your address");
    int i;
    line();
    for (i=0; i<5; i++)
    {
        printf("\naddress code:%d.%s",i,address[i]);
    }
    line();
    scanf("%s",temp.address);
    
    temp.add_code = address_code(temp.address);
    printf("enter your contact\n");
    scanf("%s",temp.phone);
    
    temp.id = agent_id;
    agent_id++;
    temp.commission = 0;
    temp.isfree = yes;
    
    insert_agent(temp,temp.id);
}


/*_________________________________________________*/


void signup_user( )
{
    int i;
    user temp;
    
    printf("enter your NAME\n");
    scanf("%s",temp.name);
    
    printf("enter your ADDRESS\n");
    line();
    for (i=0; i<5; i++)
    {
        printf("\naddress code: %d. %s",i,address[i]);
    }
    line();
    scanf("%s",temp.address);
    temp.add_code = address_code(temp.address);
    
    printf("enter your CONTACT NO.\n");
    scanf("%s",temp.phone);
    
    temp->history = NULL;
    temp->favourites = NULL;
    
    temp.id = user_id;
    user_id++;
    
    insert_user(temp,temp.id);
    printf("YOU SIGNED UP SUCCESSFULLY !!! use %d as your FUTURE ID\n",temp.id);
}


/*_________________________________________________*/

void traverse_user()
 {

	    b_user *ptr = user_root;
	    d_user *p;
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
		        printf("name: %s and  id:  %d\n",p->arr[i].name,p->arr[i].id);
		    }
		}
		p=p->right;
	    }
 }


d_user* getptr_user()
{
   b_user* ptr = user_root;
   d_user *p;
   while(ptr->leaf!=1)
   {
           ptr = ptr->u1.next1[0];
   }
   
    p = ptr->u1.next2[0];
   return p;
}


void signin_user()
{
    int t,found=0;
    printf("enter your USER ID\n");
    scanf("%d",&t);
    
    d_user *p = getptr_user();
	      while(p&&found==0)
	      {
		 if (p->count!=0)
		 {
		     for (int i=0; i<p->count&&found==0; i++)
		     {
		         if (p->arr[i].id==t)
		         {
		            found=1;
			    signed_user = &(p->arr[i]);
		         }
		     }
		 }
		 p=p->right;
	      }
	    
 
	    if(found==0)
	    {
		printf("NO USER FOUND WITH GIVEN ID !!!\n PLEASE SIGN UP FIRST\n");
	    }
	    else
	    {
		printf("WELCOME!! %s\n",signed_user.name);
	    }
    
}


/*---------------------------------------------------------*/


likes* divide(likes* list)
{
    likes* slow,*fast,*ptr;
    slow = list;
    fast = list->next->next;
    while(fast!=NULL)
    {
        fast = fast->next;
        slow = slow->next;
        if(fast!=NULL)
        {
            fast = fast->next;
        }
    }
    ptr = slow->next;
    slow->next=NULL;
    return ptr;
}


/*----------------------------------------------------------*/


likes* merge(likes* list1,likes* list2)
{
    likes* head,*tail,*ptr1,*ptr2;
    if(list1==NULL)
    {
        head=list2;
    }
    else
    {
        
        if(list2==NULL)
        {
            head=list1;
        }
        else
        {
            if(list1->frequency>list2->frequency)
            {
                head=list1;
                ptr1 = head->next;
                ptr2 = list2;
            }
            else
            {
                head = list2;
                ptr2 = head->next;
                ptr1 = list1;
            }
            tail=head;
            while(ptr1!=NULL && ptr2!=NULL)
            {
                if(ptr1->frequency>= ptr2->frequency)
                {
                    tail = tail->next = ptr1;
                    ptr1 = ptr1->next;
                }
                else
                {
                    tail = tail->next  = ptr2;
                    ptr2 = ptr2->next;
                }
            }
            if(ptr1!=NULL)
            {
                tail->next = ptr1;
            }
            else
            {
                tail->next = ptr2;
            }
            
        }
    }
    return head;
    
}


/*-------------------------------------------------------*/


likes* mergesort_frequency(likes* list)
{
    likes* head,*ptr;
    head = list;
    if(list!=NULL && list->next!=NULL)
    {
        ptr = divide(list);
        list = mergesort_frequency(list);
        ptr = mergesort_frequency(ptr);
        head = merge(list,ptr);
    }
    return head;
}

b_outlet* makenode_cat(int leaf)
{
    b_outlet *root=(b_outlet*)malloc(sizeof(b_outlet));
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
                root->u1.next2[i]=(d_outlet*)malloc(sizeof(d_outlet));
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
    

//////////////////////////////////////////////////////////////////////////////////////////////////////
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




int insertSorted1(user arr[], int n, user key, int capacity)
{
    // Cannot insert more elements if n is already
    // more than or equal to capcity
    if (n >= capacity)
        return n;
    
    int i;
    for (i=n-1; ( i >= 0  && arr[i].id > key.id); i--)
        arr[i+1] = arr[i];
    
    arr[i+1] = key;
    
    return (n+1);
}




void insert_user(user *pval,int val)
{
    b_user *ptr,*temp,*child;
    int done=0;
    ptr = user_root;
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
                (ptr->u1.next2[pos])->count=insertSortedq1((ptr->u1.next2[pos])->arr, (ptr->u1.next2[pos])->count,pval, 3);
                
            }
            else
            {
                if(ptr->count!=max-1)
                {
                    user temp[4];
                    for(i=0;i<(ptr->u1.next2[pos])->count;i++)
                    {
                        temp[i] = (ptr->u1.next2[pos])->arr[i];
                    }
                    insertSorted1(temp,3,pval,4);
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
                    
                    b_user *nptr,*sibling;
                    nptr = makenode_user(0);
                    sibling = makenode_user(1);
                    
                    nptr->count=1;
                    nptr->keys[0]=median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    nptr->leaf=0;
                    sibling->leaf=1;
                    user_root = nptr;
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
                    b_user *nptr,*sibling;
                    
                    sibling = makenode_user(0);
                    nptr = makenode_user(0);
                    sibling->leaf=0;
                    nptr->leaf=0;
                    nptr->count=1;
                    nptr->keys[0] = median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    user_root = nptr;
                    
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
                        b_user *sibling;
                        sibling = makenode_user(1);
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
                        b_user *sibling;
                        sibling = makenode_user(0);
                        
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
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int insertSorted2(agent arr[], int n, agent key, int capacity)
{
    // Cannot insert more elements if n is already
    // more than or equal to capcity
    if (n >= capacity)
        return n;
    
    int i;
    for (i=n-1; ( i >= 0  && arr[i].id > key.id); i--)
        arr[i+1] = arr[i];
    
    arr[i+1] = key;
    
    return (n+1);
}




void insert_agent(agent *pval,int val)
{
    b_agent *ptr,*temp,*child;
    int done=0;
    ptr = agent_root;
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
                (ptr->u1.next2[pos])->count=insertSorted2((ptr->u1.next2[pos])->arr, (ptr->u1.next2[pos])->count,pval, 3);
                
            }
            else
            {
                if(ptr->count!=max-1)
                {
                    agent temp[4];
                    for(i=0;i<(ptr->u1.next2[pos])->count;i++)
                    {
                        temp[i] = (ptr->u1.next2[pos])->arr[i];
                    }
                    insertSorted2(temp,3,pval,4);
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
                    
                    b_agent *nptr,*sibling;
                    nptr = makenode_agent(0);
                    sibling = makenode_agent(1);
                    
                    nptr->count=1;
                    nptr->keys[0]=median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    nptr->leaf=0;
                    sibling->leaf=1;
                    agent_root = nptr;
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
                    b_agent *nptr,*sibling;
                    
                    sibling = makenode_agent(0);
                    nptr = makenode_agent(0);
                    sibling->leaf=0;
                    nptr->leaf=0;
                    nptr->count=1;
                    nptr->keys[0] = median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    agent_root = nptr;
                    
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
                        b_agent *sibling;
                        sibling = makenode_agent(1);
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
                        b_agent *sibling;
                        sibling = makenode_agent(0);
                        
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
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int insertSorted3(outlet arr[], int n, agent outlet, int capacity)
{
    // Cannot insert more elements if n is already
    // more than or equal to capcity
    if (n >= capacity)
        return n;
    
    int i;
    for (i=n-1; ( i >= 0  && arr[i].id > key.id); i--)
        arr[i+1] = arr[i];
    
    arr[i+1] = key;
    
    return (n+1);
}


void insert_outlet(outlet *pval,int val,int food_type)
{
    b_outlet *ptr,*temp,*child;
    int done=0;
    ptr = cat[food_type];
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
            
                (ptr->u1.next2[pos])->count=insertSorted3((ptr->u1.next2[pos])->arr, (ptr->u1.next2[pos])->count,pval, 3);
                
            }
            else
            {
                if(ptr->count!=max-1)
                {
                    outlet temp[4];
                    for(i=0;i<(ptr->u1.next2[pos])->count;i++)
                    {
                        temp[i] = (ptr->u1.next2[pos])->arr[i];
                    }
                    insertSorted3(temp,3,pval,4);
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
                    
                    b_outlet *nptr,*sibling;
                    nptr = makenode_cat(0);
                    sibling = makenode_cat(1);
                    
                    nptr->count=1;
                    nptr->keys[0]=median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    nptr->leaf=0;
                    sibling->leaf=1;
                    cat[food_type] = nptr;
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
                    b_outlet *nptr,*sibling;
                    
                    sibling = makenode_cat(0);
                    nptr = makenode_cat(0);
                    sibling->leaf=0;
                    nptr->leaf=0;
                    nptr->count=1;
                    nptr->keys[0] = median;
                    nptr->u1.next1[0] = ptr;
                    nptr->u1.next1[1] = sibling;
                    cat[food_type] = nptr;
                    
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
                        b_outlet *sibling;
                        sibling = makenode_cat(1);
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
                        b_outlet *sibling;
                        sibling = makenode_cat(0);
                        
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
    
}


