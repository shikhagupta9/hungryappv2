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


typedef struct bnode_agent        //node
{
    int count;
    agent keys[max-1];
    struct bnode_agent *next[max];
    bool leaf;
    struct bnode_agent *right;
    struct bnode_agent *left;
}b_agent;


typedef struct spec{
    char name[20];
    struct spec *next;
}spec;


typedef struct outlet
{
    char name[20];
    char address[20];
    int add_code;
    ftype type;
    int seats;
    item *menu;
    spec *facilities;
}outlet;

typedef struct bnode_outlet
{
    int count;
    outlet keys[max-1];
    struct bnode_outlet *next[max],*right,*left;
    bool leaf;
}b_outlet;

typedef struct order
{
    int uid;  //user id
    int oid;  //order id
    outlet *selected_outlet;
    agent *selected_agent;
    item *food;
    int totalprice;
}order;

typedef struct order_bnode
{
    int count;
    order keys[max-1];
    struct order_bnode *next[max],*right,*left;
    bool leaf;
}b_order;

typedef struct user_tag
{
    int id;
    char name[20];
    char address[20];
    char phone[10];
    int add_code;
    likes *favourites;
    b_order *history;
}user;

typedef struct user_bnode
{
    int count;
    user keys[max-1];
    struct user_bnode *next[max];
    struct user_bnode *right;
    struct user_bnode *left;
    bool leaf;
}b_user;



/*------------------------------------------------------*/



user *signed_user;
b_agent *agent_root;
b_user *user_root;
static int user_id=1;
static int agent_id=1;
static int order_id=1;
b_outlet *cat[3];
b_order  *live_order_root;


/*------------------------------------------------------*/


void initialize_user(void);
void initialize(void);
void addoutlet(int category_index,outlet *o,int food_category);
void traverse_outlet(b_outlet * outlet);

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
void initialize_agents(void);
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
    b_order *ptr;
    initialize_cat();
    initialize_agents();
    initialize_user();
    
        b_order *live_order_root;
        live_order_root = (b_order*)malloc(sizeof(b_order));
        live_order_root->count=0;
        live_order_root->leaf = yes;
        live_order_root->left = live_order_root->right = NULL;
        int i;
        for(i=0;i<max-1;i++)
        {
            live_order_root->keys[i].oid = 0;
        }
    
        for(i=0;i<max;i++)
        {
           live_order_root->next[i] = NULL;
        }
    
    
    
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
                            //trverse ptr (tree node)
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
                            ptr=search_outlet(out);
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

b_outlet* makenode_cat()
{
    b_outlet* temp;
    int i;
    temp = (b_outlet*)malloc(sizeof(b_outlet));
    temp->count=0;
    temp->leaf = yes;
    temp->left = temp->right = NULL;

    for(i=0;i<max;i++)
    {
        temp->next[i] = NULL;
    }
    return temp;
}

void initialize_cat()
{
    int i;
    for(i=0;i<3;i++)
    {
        cat[i] = NULL;
        cat[i] = makenode_cat();
    }
}


/*------------------------------------------------------*/


int distance(int first,int second)
{
    int d;
    d=(X[first]-X[second])*(X[first]-X[second])+(Y[first]-Y[second])*(Y[first]-Y[second]);
    return d;
}


/*------------------------------------------------------*/


void traverse_outlet(b_outlet * outlet)
{
    
    b_outlet *ptr;
    ptr=outlet;
    item *menu_temp;
    
    int i=0,j;
    
    if(ptr!=NULL)
    {
        for (i=0; i<ptr->count+1; i++)
        {
            if(ptr->next[i]!=NULL)
            {
                traverse_outlet(ptr->next[i]);
                if(i < ptr->count )
                {
                    printf(" %d ",ptr->keys[i]);
                }
            }
            else
            {
                for (j=0; j<ptr->count; j++)
                {
                    printf("Food outlet name: %s\nNumber of seats: %d\nAddress: %s\nAddress code:%d\n food type:%d\n",ptr->keys[i].name,ptr->keys[i].seats,ptr->keys[i].address,ptr->keys[i].add_code,ptr->keys[i].type);
            
                    line();
                    menu_temp = ptr->keys[i].menu;
                    while(menu_temp!=NULL)
                    {
                        printf("\nitem name: %s\nprice: %f\n\n",menu_temp->name,menu_temp->price);
                        menu_temp = menu_temp->next;
                    }
                }
                i = 100;
            }
        }
    }
}


/*------------------------------------------------------*/


void search_category()
{
    int t,index1,i,address=-1,j;
    outlet *ptr;
    category select;
    line();
    printf("enter the CATEGORY of food outlet you wish to view \n1-restaurant  \n2-cafe \n3-pub  \n4-all?\n");
    scanf("%d",&t);
    
    index1=t-1;
    
    printf("what FOOD CATEGORY do you wish to view? \n 1-southindian  \n 2-northindian  \n3-chinese  \n4-continental \n5-all \n");
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
        
        if(t<=4)
        {
            ptr=select.type[t-1];
            traverse_outlet(ptr,address);
        }
        else
        {
            for(i=0;i<4;i++)
            {
                ptr=select.type[i];
                traverse_outlet(ptr,address);
            }
        }
    }
    else
    {
        
        for (i=0; i<3; i++)
        {
            select=cat[i];
            if(t<=4)
            {
                ptr=select.type[t-1];
                traverse_outlet(ptr,address);
            }
            else
            {
                for(j=0;j<4;j++)
                {
                    ptr=select.type[j];
                    traverse_outlet(ptr,address);
                }
            }
            
        }
        
    }
    
}

/*-------------------------------------------*/


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
    
    int choice,i;
    char name[50];
    
    order *new_order;
    new_order = (order*)malloc(sizeof(order));
    new_order->next=NULL;
    printf("If you want to see our OUTLETS enter 1 else 0\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        search_category();
    }
    
    printf("Enter the NAME of restaurant");
    scanf("%s",name);
    new_order->uid = signed_user->id;
    new_order->oid = order_id;
    order_id++;
    new_order->selected_outlet = search_outlet(name);
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
    
    int a[5]={0,1,2,3,4};
    int i,found=0;
    agent *selected_agent = NULL;
    
    Sort_addresscodes(a,(o->selected_outlet)->add_code);
    
    for (i=0; i<5&&found==0; i++)
    {
        if (free_agents[i]!=NULL)
        {
            selected_agent=free_agents[i];
            found=1;
            free_agents[i]=selected_agent->next;
            selected_agent->next=alloc_agents;
            alloc_agents=selected_agent;
            
        }
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
    spec *f;
    printf("Enter restaurant name\n");
    scanf("%s",name);
    s=search_outlet(name);
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


outlet* search_outlet(char name[])
{
    int t,j,found=0;
    outlet *search = NULL,*ptr;
    category select;
    
    for(t=0;t<3 && found==0;t++)
    {
        
        select = cat[t];
        for(j=0;j<4 && found==0;j++)
        {
            
            ptr = select.type[j];
            while(ptr!=NULL && found==0)
            {
                if(strcmp(ptr->name,name)==0)
                {
                    search = ptr;
                    found=1;
                }
                else
                {
                    ptr = ptr->next;
                }
            }
            
        }
        
    }
    
    return search;
}


b_user* makenode_user()
{
    b_user *temp;
    temp = (b_user*)malloc(sizeof(b_user));
    temp->count=0;
    temp->leaf = yes;
    temp->left = temp->right = NULL;
    for(i=0;i<max-1;i++)
    {
        temp->keys[i].id = 0;
    }
    for(i=0;i<max;i++)
    {
        temp->next[i] = NULL;
    }
    return temp;
}


/*_________________________________________________*/


void initialize_user()
{
    user_root = NULL;
    user_root = makenode_user();
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
        tobefreed->add_code = signed_user->add_code;
        strcpy(tobefreed->address, signed_user->address);
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
        agent *al,*pr;
        pr=alloc_agents;
        al=alloc_agents;
        int fl=0;
        if (alloc_agents==tobefreed)
        {
            alloc_agents=alloc_agents->next;
        }else
        {
            al=al->next;
            while (al!=NULL && fl==0)
            {
                if (al==tobefreed)
                {
                    fl=1;
                    pr->next=al->next;
                }else
                {
                    pr=al;
                    al=al->next;
                }
            }
        }
        
        tobefreed->next=free_agents[signed_user->add_code];
        free_agents[signed_user->add_code]=tobefreed;
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
    food_category=food_category-1;
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
    addoutlet(outlet_type, new_outlet, food_category);
    
}

/*------------------------------------------------------*/


void agents_area()
{
    agent *a;
    int i;
    for (i=0; i<areas; i++)
    {
        a=free_agents[i];
        if (a) {
            line();
            printf("area: %s\n",address[i]);
        }
        
        while (a)
        {
            line();
            printf("name: %s \ncontact: %s\n id: %d\n",a->name,a->phone,a->id);
            a=a->next;
        }
    }
}


/*--------------------------------------------------------*/


void agent_details()
{
   
    agent *a;
    int i;
    for (i=0; i<areas; i++)
    {
        a=free_agents[i];
        while (a)
        {
            line();
            printf("name: %s \ncontact: %s \naddress: %s\n",a->name,a->phone,address[a->add_code]);
            a=a->next;
        }
    }
    a=alloc_agents;
    while (a)
    {
        line();
        printf("name: %s\n contact: %s\n address: %s\n",a->name,a->phone,address[a->add_code]);
        a=a->next;
    }
}


/*_________________________________________________*/



void addoutlet(int category_index,outlet *o,int food_category)
{
    o->next=cat[category_index].type[food_category];
    cat[category_index].type[food_category]=o;
}


void add_item()
{
    int choice;
    char name[20];
    outlet *o;
    item *it;
    printf("If you want to browse OUTLETS enter 1 else 0\n");
    scanf("%d",&choice);
    line();
    if(choice==1)
    {
        search_category();
    }
    line();
    printf("Enter the NAME of restaurant\n");
    scanf("%s",name);
    o = search_outlet(name);
    if(o!=NULL)
    {
        
        int count=1;
        while(count)
        {
            it = (item*)malloc(sizeof(item));
            printf("enter the name and price of item to ADD\n");
            scanf("%s %f",it->name,&it->price);
            it->next = o->menu;
            o->menu = it;
            printf("IF you want to add more items press 1 else 0\n");
            scanf("%d",&count);
        }
        
    }
    else
    {
        printf("Oops! no such outlet is there\n");
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
        
        agent *al,*pr;
        pr=alloc_agents;
        al=alloc_agents;
        int fl=0;
        if (alloc_agents==tobefreed)
        {
            alloc_agents=alloc_agents->next;
        }else
        {
            al=al->next;
            while (al!=NULL && fl==0)
            {
                if (al==tobefreed)
                {
                    fl=1;
                    pr->next=al->next;
                }else
                {
                    pr=al;
                    al=al->next;
                }
            }
        }
        
        tobefreed->next=free_agents[signed_user->add_code];
        tobefreed->add_code = signed_user->add_code;
        free_agents[signed_user->add_code]=tobefreed;
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

b_agent* makenode_agent()
{
    b_agent *temp;
    temp = (b_agent*)malloc(sizeof(b_agent));
    temp->count=0;
    temp->leaf = yes;
    temp->left = temp->right = NULL;
    for(i=0;i<max-1;i++)
    {
        temp->keys[i].id = 0;
    }
    for(i=0;i<max;i++)
    {
        temp->next[i] = NULL;
    }
    return temp;
}


void initialize_agents()
{
    agent_root = NULL;
    agent_root = makenode_agent();
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
    
    insert_agent(temp);
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
    
    insert_user(temp);
    printf("YOU SIGNED UP SUCCESSFULLY !!! use %d as your FUTURE ID\n",temp.id);
}


/*_________________________________________________*/

int traverse(int val)
{
    int flag=0,flag1,i;
    b_user *search  = user_root;
    
    while(search!=NULL && flag==0)
    {
        flag1=0;
        for(i=0;i<search->count && flag1==0;i++)
        {
            if(val==search->keys[i].id)
            {
                flag1 = 1;
                flag = 1;
                signed_user = &(search->keys[i]);
            }
            else
            {
                if(val < search->keys[i].id)
                {
                    search = search->next[i];
                    flag1=1;
                }
            }
        }
        if(flag1==0)
        {
            search = search->next[i];
        }
    }
    
    return flag;
}

void signin_user()
{
    int t,flag=0;
    printf("enter your USER ID\n");
    scanf("%d",&t);
    
    flag = traverse(t);
    
    if(flag==0)
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





