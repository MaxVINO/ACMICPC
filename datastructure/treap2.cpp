#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
#define INF 2000000000
#define N 500010
struct Node;
typedef pair<Node*,Node*> Pair;
Node *null,*root;
struct Node
{
    int sz,val,sum,ls,rs,ss,lzy1,lzy2;
    Node *lft,*rht;
    Node *newnode(int);
    Pair split(int);
    void same(int v)
    {
    	if(this==null) return;
        lzy2=val=v;
        sum=v*sz;
        ls=rs=ss=max(sum,v);
    }
    void rev()
    {
    	if(this==null) return;
    	lzy1^=1;
    	swap(lft,rht);
    	swap(ls,rs);
    }
    Node *pushup()
    {
        sz=lft->sz+1+rht->sz;
        sum=lft->sum+val+rht->sum;
 
        ls=max(lft->ls,lft->sum+val+max(0,rht->ls));
        rs=max(rht->rs,rht->sum+val+max(0,lft->rs));
 
        ss=max(0,lft->rs)+val+max(0,rht->ls);
        ss=max(ss,max(lft->ss,rht->ss));
 
        return this;
    }
    Node *pushdown()
    {
        if(lzy1)
        {
            lft->rev();
            rht->rev();
            lzy1=0;
        }
        if(lzy2!=-INF)
        {
            lft->same(lzy2);
            rht->same(lzy2);
            lzy2=-INF;
        }
        return this;
    }
};
bool random(int a,int b)
{
    return double(rand())/RAND_MAX<(double)a/(a+b);
}
Node *merge(Node *p,Node *q)
{
    if(p==null) return q;
    if(q==null) return p;
    if(random(p->sz,q->sz))
    {
        p->pushdown();
        p->rht=merge(p->rht,q);
        return p->pushup();
    }
    q->pushdown();
    q->lft=merge(p,q->lft);
    return q->pushup();
}
Pair Node::split(int need)
{
    if(this==null) return make_pair(null,null);
    pushdown();
    if(lft->sz>=need)
    {
        Pair ret=lft->split(need);
        lft=null;
        pushup();
        return make_pair(ret.first,merge(ret.second,this));
    }
    Pair ret=rht->split(need-(lft->sz+1));
    rht=null;
    pushup();
    return make_pair(merge(this,ret.first),ret.second);
}
Node data[N],*pool[N];
int top,cnt;
Node* newnode(int c)
{
    Node *x;
    if(top) x=pool[top--];
    else x=&data[cnt++];
    x->lft=x->rht=null;
    x->sz=1; x->lzy1=0; x->lzy2=-INF;
    x->val=x->sum=x->ls=x->rs=x->ss=c;
    return x;
}
void init()
{
	srand(time(0));
    cnt=1; top=0;
    null=&data[0];
    null->sz=null->sum=0;
    null->val=null->ls=null->rs=null->ss=-INF;
    null->lzy1=0;
    null->lzy2=-INF;
    null->lft=null->rht=null;
}
//---------------------------------------------------------
void erase(Node *rt)
{
    if(rt==null) return;
    erase(rt->lft);
    erase(rt->rht);
    pool[++top]=rt;
}
int n,m;
char ord[20];
int a,b,c;
int main ()
{
freopen("1.in","r",stdin);
freopen("1.out","w",stdout);
    init();
    root=null;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        int a;
        scanf("%d",&a);
        root=merge(root,newnode(a));
    }
    while (m--)
    {
        scanf("%s",ord);
        if(ord[0]=='I')
        {
            scanf("%d%d",&a,&n);
            Pair ret=root->split(a);
            for(int i=0;i<n;i++)
            {
                scanf("%d",&b);
                ret.first=merge(ret.first,newnode(b));
            }
            root=merge(ret.first,ret.second);
        }else if(ord[0]=='D')
        {
            scanf("%d%d",&a,&b);
            b=a+b-1;
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            erase(ret2.first);
            root=merge(ret1.first,ret2.second);
        }else if(ord[0]=='M' && ord[2]=='K')
        {
            scanf("%d%d%d",&a,&b,&c);
            b=b+a-1;
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            ret2.first->same(c);
            root=merge(ret1.first,merge(ret2.first,ret2.second));
        }else if(ord[0]=='R')
        {
            scanf("%d%d",&a,&b);
            b=b+a-1;
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            ret2.first->rev();
            root=merge(ret1.first,merge(ret2.first,ret2.second));
        }else if(ord[0]=='G')
        {
            scanf("%d%d",&a,&b);
            b=a+b-1;
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            printf("%d\n",ret2.first->sum);
            root=merge(ret1.first,merge(ret2.first,ret2.second));
        }
        else if(ord[0]=='M') printf("%d\n",root->ss);
    }
    return 0;
}
