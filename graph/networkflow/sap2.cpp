#pragma comment(linker, "/STACK:32000000")
#define INF (1<<30)
#define N 2010
#define M 4000010
int head[N],gap[N],dis[N],cur[N],cnt;
int n,m,s,t;	struct edge{	int v,w,next;	}e[M];
void addedge(int u,int v,int w)
{	e[cnt].next=head[u]; e[cnt].v=v; e[cnt].w=w; head[u]=cnt++;
	e[cnt].next=head[v]; e[cnt].v=u; e[cnt].w=0; head[v]=cnt++;
}
int aug(int u,int m)
{	if(u==t) return m;	int flag=0,l=m,d;
	for(int i=cur[u];i!=-1;i=e[i].next)
	if(dis[e[i].v]+1==dis[u] && e[i].w>0)
	{		d=aug(e[i].v,min(e[i].w,l));
		e[i].w-=d;	e[i^1].w+=d;	l-=d;		if(! flag){		flag=1;	cur[u]=i;	}
		if(dis[s]>=n || l==0) return m-l;
	}
	if(! flag)
	{
		int mindis=n;
		for(int i=head[u];i!=-1;i=e[i].next)
		if(e[i].w>0 && dis[e[i].v]<mindis){	mindis=dis[e[i].v];		cur[u]=i;	}
		if(--gap[dis[u]]==0) dis[s]=n;		else ++gap[dis[u]=mindis+1];
	}
	return m-l;
}
int sap()
{	memset(gap,0,sizeof(gap));	memset(dis,0,sizeof(dis));
	gap[0]=n;	int ans=0;
	for(int i=1;i<=n;i++) cur[i]=head[i];
	while (dis[s]<n) ans+=aug(s,INF);
	return ans;
}
