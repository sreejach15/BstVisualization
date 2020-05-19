#include<iostream.h>
#include<stdlib.h>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
void display();
struct node
{
    int info;
    struct node *left;
    struct node *right;
}*root;
struct gnode
{
   public: int x,y,inf;
    gnode* l,*r;

    void put(int e)
    {
        char b[50];
        inf=e;
        sprintf(b,"%d",e);
	if(e!=0)
        {
        setcolor(DARKGRAY);
        circle(x,y,20);
        setfillstyle(SOLID_FILL,DARKGRAY);
        floodfill(x,y,DARKGRAY);
        if((this->l!=NULL)||(this->r!=NULL))
        {
	   // if((this->l)->inf!=0)
	    line(x-20,y+20,((this->l)->x)+20,((this->l)->y)-20);
	   // if((this->r)->inf!=0)
	    line(x+20,y+20,((this->r)->x)-20,((this->r)->y)-20);
        }
        setcolor(WHITE);
        outtextxy(x,y,b);
        }
    }
};
class BST
{
    public:
	void insert(node *, node *);
	void display(node *, int);
    void del(int);
    void case_a(node *,node *);
    void case_b(node *,node *);
    void case_c(node *,node *);
    void find(int, node **, node **);
	BST()
	{
	    root = NULL;
	}
};
 void graph()
  {
  setbkcolor(CYAN);
  delay(500);
  setcolor(MAGENTA);
  setlinestyle(SOLID_LINE,SOLID_LINE,THICK_WIDTH);
  rectangle(80,80,560,400);
  setfillstyle(SOLID_FILL,MAGENTA);
  floodfill(80,80,MAGENTA);
  bar(80,80,560,400);
  delay(500);
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
  outtextxy(120,220,"BST VISUALIZATION");
  getch();
  clearviewport();
  }

void BST::insert(node *tree, node *newnode)
{
    if (root == NULL)
    {
	root = new node;
	root->info = newnode->info;
	root->left = NULL;
	root->right = NULL;
	return;
    }
    if (tree->info == newnode->info)
    {
	cout<<"Element already in the tree"<<endl;
	return;
    }
    if (tree->info > newnode->info)
    {
	if (tree->left != NULL)
	{
	    insert(tree->left, newnode);
	}
	else
	{
	    tree->left = newnode;
	    (tree->left)->left = NULL;
	    (tree->left)->right = NULL;
	    return;
	}
    }
    else
    {
	if (tree->right != NULL)
	{
	    insert(tree->right, newnode);
	}
	else
	{
	    tree->right = newnode;
	    (tree->right)->left = NULL;
	    (tree->right)->right = NULL;
	    return;
	}
    }
}

void BST::find(int item, node **par, node **loc)
{
    node *ptr, *ptrsave;
    if (root == NULL)
    {
        *loc = NULL;
        *par = NULL;
        return;
    }
    if (item == root->info)
    {
        *loc = root;
        *par = NULL;
        return;
    }
    if (item < root->info)
        ptr = root->left;
    else
        ptr = root->right;
    ptrsave = root;
    while (ptr != NULL)
    {
        if (item == ptr->info)
        {
            *loc = ptr;
            *par = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item < ptr->info)
            ptr = ptr->left;
	else
	    ptr = ptr->right;
    }
    *loc = NULL;
    *par = ptrsave;
}

void BST::del(int item)
{
    node *parent, *location;
    if (root == NULL)
    {
        cout<<"Tree empty"<<endl;
        return;
    }
    find(item, &parent, &location);
    if (location == NULL)
    {
        cout<<"Item not present in tree"<<endl;
        return;
    }
    if (location->left == NULL && location->right == NULL)
        case_a(parent, location);
    if (location->left != NULL && location->right == NULL)
        case_b(parent, location);
    if (location->left == NULL && location->right != NULL)
        case_b(parent, location);
    if (location->left != NULL && location->right != NULL)
        case_c(parent, location);
    free(location);
}

void BST::case_a(node *par, node *loc )
{
    if (par == NULL)
    {
        root = NULL;
    }
    else
    {
        if (loc == par->left)
            par->left = NULL;
        else
            par->right = NULL;
    }
}

void BST::case_b(node *par, node *loc)
{
    node *child;
    if (loc->left != NULL)
        child = loc->left;
    else
        child = loc->right;
    if (par == NULL)
    {
        root = child;
    }
    else
    {
        if (loc == par->left)
            par->left = child;
        else
            par->right = child;
    }
}

void BST::case_c(node *par, node *loc)
{
    node *ptr, *ptrsave, *suc, *parsuc;
    ptrsave = loc;
    ptr = loc->right;
    while (ptr->left != NULL)
    {
        ptrsave = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrsave;
    if (suc->left == NULL && suc->right == NULL)
        case_a(parsuc, suc);
    else
        case_b(parsuc, suc);
    if (par == NULL)
    {
        root = suc;
    }
    else
    {
        if (loc == par->left)
            par->left = suc;
        else
            par->right = suc;
    }
    suc->left = loc->left;
    suc->right = loc->right;
}

int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");

    struct gnode n[15];
    n[0].x=320;
    n[0].y=60;
    n[0].l=&n[1];
    n[0].r=&n[2];

    n[1].x=160;
    n[1].y=180;
    n[1].l=&n[3];
    n[1].r=&n[4];

    n[2].x=480;
    n[2].y=180;
    n[2].l=&n[5];
    n[2].r=&n[6];

    n[3].x=80;
    n[3].y=300;
    n[3].l=&n[7];
    n[3].r=&n[8];

    n[4].x=240;
    n[4].y=300;
    n[4].l=&n[9];
    n[4].r=&n[10];

    n[5].x=400;
    n[5].y=300;
    n[5].l=&n[11];
    n[5].r=&n[12];

    n[6].x=560;
    n[6].y=300;
    n[6].l=&n[13];
    n[6].r=&n[14];

    n[7].x=40;
    n[7].y=420;
    n[7].l=NULL;
    n[7].r=NULL;

    n[8].x=120;
    n[8].y=420;
    n[8].l=NULL;
    n[8].r=NULL;

    n[9].x=200;
    n[9].y=420;
    n[9].l=NULL;
    n[9].r=NULL;

    n[10].x=280;
    n[10].y=420;
    n[10].l=NULL;
    n[10].r=NULL;

    n[11].x=360;
    n[11].y=420;
    n[11].l=NULL;
    n[11].r=NULL;

    n[12].x=440;
    n[12].y=420;
    n[12].l=NULL;
    n[12].r=NULL;

    n[13].x=520;
    n[13].y=420;
    n[13].l=NULL;
    n[13].r=NULL;

    n[14].x=600;
    n[14].y=420;
    n[14].l=NULL;
    n[14].r=NULL;

    int choice,num,key;
    BST bst;
    graph();
    node *temp;
    while(1)
    {
    setbkcolor(DARKGRAY);
    cout<<"1.Insert an element"<<endl;
    cout<<"2.Display"<<endl;
    cout<<"3.Delete"<<endl;
    cout<<"4.Search"<<endl;
    cout<<"4.Quit"<<endl;

	cout<<"Enter your choice : ";
	cin>>choice;

	switch(choice)
	{
	case 1:
	    temp = new node;
	    cout<<"Enter the number to be inserted : ";
	    cin>>temp->info;
	    bst.insert(root, temp);
	break;

	case 2:
	    clearviewport();
	    setbkcolor(WHITE);
	    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
        settextjustify(CENTER_TEXT,TOP_TEXT);
        n[0].put(root->info);
        n[1].put((root->left)->info);
        n[2].put((root->right)->info);
        n[3].put(((root->left)->left)->info);
        n[4].put(((root->left)->right)->info);
        n[5].put(((root->right)->left)->info);
        n[6].put(((root->right)->right)->info);
        n[7].put((((root->left)->left)->left)->info);
        n[8].put((((root->left)->left)->right)->info);
        n[9].put((((root->left)->right)->left)->info);
        n[10].put((((root->left)->right)->right)->info);
        n[11].put((((root->right)->left)->left)->info);
        n[12].put((((root->right)->left)->right)->info);
        n[13].put((((root->right)->right)->left)->info);
        n[14].put((((root->right)->right)->right)->info);
        getch();
        cleardevice();
	    //display();
        break;
    case 3:
            if (root == NULL)
            {
                cout<<"Tree is empty, nothing to delete"<<endl;
                continue;
            }
            cout<<"Enter the number to be deleted : ";
            cin>>num;
            bst.del(num);
            break;
   case 4:
        cout<<"Enter the element to be searched"<<endl;
        cin>>key;
        for(int l=0;l<15;l++)
        {
            if(key==n[l]->inf)
            {
                display();
                delay(1000);
                setfillstyle(SOLID_FILL,RED);
                floodfill(n[l].x,n[l].y,DARKGRAY);

            }
            else
                cout<<"Element not present in the list"<<endl;
        }
	case 4:
        exit(0);

	default:
	cout<<"WRONG CHOICE"<<endl;}}
closegraph();
}

