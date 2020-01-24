#define mvnum  50000
#include<iostream>
#include<queue>
using namespace std;

queue<int>Q;     //结点数据类型为int的队列Q
bool visited[mvnum];    //标记数组，true表示图的顶点已访问，false表示图的顶点未访问

typedef struct ArcNode
{
	int adjvex;             //该边所指向的顶点位置
	struct ArcNode *nextarc;  //指向下一条边的指针
}ArcNode;    //边结点

typedef struct VNode
{
	int data;           //数值
	int depth;          //深度
	int father;         //父亲结点
	ArcNode *firstarc;  //指向第一条依附该顶点的指针
}VNode, AdjList[mvnum];  //图的顶点及邻接表 

typedef struct
{
	AdjList vertices;     //邻接表
	int vexnum, arcnum;   //图的顶点数和边数
}ALGraph;  

/*邻接表创建无向图*/void CreateUDG(ALGraph &G)
{
	int i, v1, v2;
	ArcNode *p1, *p2;
	cout << "请输入小村庄的个数:" << endl;
	cin >> G.vexnum;
	G.arcnum = G.vexnum - 1;   //边数比顶点数少1

	for (i = 0; i < G.vexnum; i++)
	{  
		//邻接表初始化
		G.vertices[i].data = i;         //顶点的数值为其编号 即 0~G.nexnum-1
		G.vertices[i].depth = 0;        //深度都置为0
		G.vertices[i].father = i;       //父亲结点都置为自身
		G.vertices[i].firstarc = NULL;  //第一个依附该点的指针为空
	}

	cout << "请依次输入相连的两个村庄编号("<<"编号从0到"<<G.arcnum<<"):" << endl;

	for (i = 0; i < G.arcnum; i++)
	{
		cin >> v1 >> v2;

		p1 = new ArcNode;
		p1->adjvex = v2;   //邻接点序号为v2
		p1->nextarc = G.vertices[v1].firstarc;
		G.vertices[v1].firstarc = p1;  //将p1结点插在v1边表的头部

		p2 = new ArcNode;
		p2->adjvex = v1;   //邻接点序号为v1
		p2->nextarc = G.vertices[v2].firstarc;
		G.vertices[v2].firstarc = p2;   //将p2结点插在v2边表的头部
	}

	for (i = 0; i < G.vexnum; i++)
		visited[i] = false;   //标记数组0~G.nexnum-1都置为false（未访问）
}

/*广度优先遍历处理该图*/void BFS(ALGraph &G)
{
	//求出图的各个顶点的深度和该点的父亲结点
	
	ArcNode *p;
	int v, u;
	v = 0;   //因为邻接表是从0号结点开始

	visited[v] = true;
	Q.push(v);  //v入队

	while (!Q.empty())  //若链队非空
	{
		u = Q.front();  //取队头元素置为u
		Q.pop();        //队头元素出队

		for (p = G.vertices[u].firstarc; p != NULL; p = p->nextarc)
		{  
			//依次检查u的所有邻接点，p为NULL时退出循环

			if (!visited[p->adjvex])  //当该邻接点未被访问
			{
				G.vertices[p->adjvex].father = u;    //它的父亲结点置为u
				G.vertices[p->adjvex].depth = G.vertices[u].depth + 1;  //它的深度比它父亲结点的深度多1
				
				visited[p->adjvex] = true;  //该点已被访问
				Q.push(p->adjvex);          //该邻接点入队
			}
		}
	}
}

/*求结点a和b的最近公共祖先*/int LCA(ALGraph &G, int a, int b)
{
	int i, m, n, temp;
	m = G.vertices[a].depth;  //m为a的深度
	n = G.vertices[b].depth;  //n为b的深度

	if (m > n)  //a比b深
	{
		temp = m - n;     //深度的差值
		for (i = 0; i < temp; i++)
			a = G.vertices[a].father;   //a往上跳到它的父亲节点，跳temp次
	}
	else    //b比a深
	{
		temp = n - m;    //深度的差值
		for (i = 0; i < temp; i++)
			b = G.vertices[b].father;   //b往上跳到它的父亲节点，跳temp次
	}

	//此时a和b深度相同
	while (a != b)
	{
		//a和b同时往上跳，直到它们相等，相等处的结点就是a和b的最近公共祖先
		a = G.vertices[a].father;
		b = G.vertices[b].father;
	}

	return a;   //此时a或b的值就是a，b结点的最近公共祖先
}

/*判断c是否在a到b的路径上*/void check(ALGraph &G, int a, int b, int c)
{
	int i, m, n;
	i = LCA(G, a, b);   //i为a，b的最近公共祖先
	m = LCA(G, a, c);   //m为a，c的最近公共祖先
	n = LCA(G, b, c);   //n为b，c的最近公共祖先

	//ab=x 表示a和b的最近公共祖先是x

	if (m == c)   //第一种：c只是a的祖先  ac=c,ab=bc
	{
		if (i == n)
		{
			cout << "Yes" << endl;
			return;  //跳出该函数
		}
	}
	if (n == c)   //第二种：c只是b的祖先  bc=c,ab=ac
	{
		if (i == m)
		{
			cout << "Yes" << endl;
			return;  //跳出该函数
		}
	}
	if (i == c)    //第三种：c是a，b的最近公共祖先  ab=bc=ac=c
	{
		if (m == c && n == c)
		{
			cout << "Yes" << endl;
			return;  //跳出该函数
		}
	}

	//上述情况均不满足，则输出No
	cout << "No" << endl;
}

int main()
{
	int a, b, c, i, m;
	ALGraph G;
	CreateUDG(G);
	BFS(G);
	cout << "测试次数:" << endl;
	cin >> m;
	cout << "请输入3个村子a,b,c" << endl;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		check(G, a, b, c);
	}
}