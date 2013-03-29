#define N 60
#define M 2510
#define SET(a,b) memset(a,b,sizeof(a))
#define INF 0x5fffffff
int cx[N],cy[M],sx[N],sy[M],lx[N],ly[M];
int nx,ny,g[N][M];
bool dfs(int u)
{
	sx[u]=1;
	for(int v=1;v<=ny;v++)
		if(g[u][v]==lx[u]+ly[v] && ! sy[v])
		{
			sy[v]=1;
			if(!cy[v] || dfs(cy[v]))	{	cx[u]=v;	cy[v]=u;		return 1;		}
		}
	return 0;
}
void KM()
{	int i,j,u,minn,ans=0;
	SET(cx,0); SET(cy,0); SET(lx,0); SET(ly,0);
	for(i=1;i<=nx;i++)	for(j=1;j<=ny;j++)		if(lx[i]<g[i][j]) lx[i]=g[i][j];
	for(u=1;u<=nx;u++)
	if(! cx[u])
	{
		SET(sx,0); SET(sy,0);
		while (! dfs(u))
		{
			minn=INF;
			for(i=1;i<=nx;i++)	if(sx[i])
			for(j=1;j<=ny;j++)
				if(! sy[j] && lx[i]+ly[j]-g[i][j]<minn) minn=lx[i]+ly[j]-g[i][j];
			for(i=1;i<=nx;i++)		if(sx[i]) { lx[i]-=minn; sx[i]=0; } 
			for(i=1;i<=ny;i++)		if(sy[i]) { ly[i]+=minn; sy[i]=0; }
		}
	}
	for(i=1;i<=nx;i++)	ans+=g[i][cx[i]];
}
int main()
{
	int n,i,j;
	while (scanf("%d",&n)!=EOF)
	{	nx=ny=n;	 for(i=1;i<=n;i++)	for(j=1;j<=n;j++)	scanf("%d",&g[i][j]);	KM();	}
	return 0;
}
