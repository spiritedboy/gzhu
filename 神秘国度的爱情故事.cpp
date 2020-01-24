#define mvnum  50000
#include<iostream>
#include<queue>
using namespace std;

queue<int>Q;     //�����������Ϊint�Ķ���Q
bool visited[mvnum];    //������飬true��ʾͼ�Ķ����ѷ��ʣ�false��ʾͼ�Ķ���δ����

typedef struct ArcNode
{
	int adjvex;             //�ñ���ָ��Ķ���λ��
	struct ArcNode *nextarc;  //ָ����һ���ߵ�ָ��
}ArcNode;    //�߽��

typedef struct VNode
{
	int data;           //��ֵ
	int depth;          //���
	int father;         //���׽��
	ArcNode *firstarc;  //ָ���һ�������ö����ָ��
}VNode, AdjList[mvnum];  //ͼ�Ķ��㼰�ڽӱ� 

typedef struct
{
	AdjList vertices;     //�ڽӱ�
	int vexnum, arcnum;   //ͼ�Ķ������ͱ���
}ALGraph;  

/*�ڽӱ�������ͼ*/void CreateUDG(ALGraph &G)
{
	int i, v1, v2;
	ArcNode *p1, *p2;
	cout << "������С��ׯ�ĸ���:" << endl;
	cin >> G.vexnum;
	G.arcnum = G.vexnum - 1;   //�����ȶ�������1

	for (i = 0; i < G.vexnum; i++)
	{  
		//�ڽӱ��ʼ��
		G.vertices[i].data = i;         //�������ֵΪ���� �� 0~G.nexnum-1
		G.vertices[i].depth = 0;        //��ȶ���Ϊ0
		G.vertices[i].father = i;       //���׽�㶼��Ϊ����
		G.vertices[i].firstarc = NULL;  //��һ�������õ��ָ��Ϊ��
	}

	cout << "����������������������ׯ���("<<"��Ŵ�0��"<<G.arcnum<<"):" << endl;

	for (i = 0; i < G.arcnum; i++)
	{
		cin >> v1 >> v2;

		p1 = new ArcNode;
		p1->adjvex = v2;   //�ڽӵ����Ϊv2
		p1->nextarc = G.vertices[v1].firstarc;
		G.vertices[v1].firstarc = p1;  //��p1������v1�߱��ͷ��

		p2 = new ArcNode;
		p2->adjvex = v1;   //�ڽӵ����Ϊv1
		p2->nextarc = G.vertices[v2].firstarc;
		G.vertices[v2].firstarc = p2;   //��p2������v2�߱��ͷ��
	}

	for (i = 0; i < G.vexnum; i++)
		visited[i] = false;   //�������0~G.nexnum-1����Ϊfalse��δ���ʣ�
}

/*������ȱ��������ͼ*/void BFS(ALGraph &G)
{
	//���ͼ�ĸ����������Ⱥ͸õ�ĸ��׽��
	
	ArcNode *p;
	int v, u;
	v = 0;   //��Ϊ�ڽӱ��Ǵ�0�Ž�㿪ʼ

	visited[v] = true;
	Q.push(v);  //v���

	while (!Q.empty())  //�����ӷǿ�
	{
		u = Q.front();  //ȡ��ͷԪ����Ϊu
		Q.pop();        //��ͷԪ�س���

		for (p = G.vertices[u].firstarc; p != NULL; p = p->nextarc)
		{  
			//���μ��u�������ڽӵ㣬pΪNULLʱ�˳�ѭ��

			if (!visited[p->adjvex])  //�����ڽӵ�δ������
			{
				G.vertices[p->adjvex].father = u;    //���ĸ��׽����Ϊu
				G.vertices[p->adjvex].depth = G.vertices[u].depth + 1;  //������ȱ������׽�����ȶ�1
				
				visited[p->adjvex] = true;  //�õ��ѱ�����
				Q.push(p->adjvex);          //���ڽӵ����
			}
		}
	}
}

/*����a��b�������������*/int LCA(ALGraph &G, int a, int b)
{
	int i, m, n, temp;
	m = G.vertices[a].depth;  //mΪa�����
	n = G.vertices[b].depth;  //nΪb�����

	if (m > n)  //a��b��
	{
		temp = m - n;     //��ȵĲ�ֵ
		for (i = 0; i < temp; i++)
			a = G.vertices[a].father;   //a�����������ĸ��׽ڵ㣬��temp��
	}
	else    //b��a��
	{
		temp = n - m;    //��ȵĲ�ֵ
		for (i = 0; i < temp; i++)
			b = G.vertices[b].father;   //b�����������ĸ��׽ڵ㣬��temp��
	}

	//��ʱa��b�����ͬ
	while (a != b)
	{
		//a��bͬʱ��������ֱ��������ȣ���ȴ��Ľ�����a��b�������������
		a = G.vertices[a].father;
		b = G.vertices[b].father;
	}

	return a;   //��ʱa��b��ֵ����a��b���������������
}

/*�ж�c�Ƿ���a��b��·����*/void check(ALGraph &G, int a, int b, int c)
{
	int i, m, n;
	i = LCA(G, a, b);   //iΪa��b�������������
	m = LCA(G, a, c);   //mΪa��c�������������
	n = LCA(G, b, c);   //nΪb��c�������������

	//ab=x ��ʾa��b���������������x

	if (m == c)   //��һ�֣�cֻ��a������  ac=c,ab=bc
	{
		if (i == n)
		{
			cout << "Yes" << endl;
			return;  //�����ú���
		}
	}
	if (n == c)   //�ڶ��֣�cֻ��b������  bc=c,ab=ac
	{
		if (i == m)
		{
			cout << "Yes" << endl;
			return;  //�����ú���
		}
	}
	if (i == c)    //�����֣�c��a��b�������������  ab=bc=ac=c
	{
		if (m == c && n == c)
		{
			cout << "Yes" << endl;
			return;  //�����ú���
		}
	}

	//��������������㣬�����No
	cout << "No" << endl;
}

int main()
{
	int a, b, c, i, m;
	ALGraph G;
	CreateUDG(G);
	BFS(G);
	cout << "���Դ���:" << endl;
	cin >> m;
	cout << "������3������a,b,c" << endl;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		check(G, a, b, c);
	}
}