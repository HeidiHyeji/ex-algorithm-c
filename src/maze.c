// ���� ����Ʈ�� �̿��� �̷� ã��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_VERTICES 13
int visited[MAX_VERTICES];
int parent[MAX_VERTICES];//���� v ������ �湮�� ���� ������ ��ȣ�� ����
int TRUE = 1;
int FALSE = 0;
int startV;

typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n; // �����ǰ���
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

// �׷����ʱ�ȭ
void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}

// ���� ���� ����
void insert_vertex(GraphType *g, int v)
{
	//	# �ڵ� �ۼ� (���� ����)
	if(((g->n)+1)>MAX_VERTICES){
		fprintf(stderr,"�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����, v�� u����������Ʈ�������Ѵ�.
void insert_edge(GraphType *g, int u, int v)
{
	//	# �ڵ� �ۼ� (���� ����)
	GraphNode *node;
	if(u>=g->n || v>=g->n){
		fprintf(stderr,"�׷���: ������ȣ����");
		return;
	}
	node=(GraphNode *)malloc(sizeof(GraphNode));
	node->vertex =v;
	node->link = g->adj_list[u];
	g->adj_list[u]=node;
}
void dfs_list_init(){
	int v;
	for(v=0;v<MAX_VERTICES;v++){
		parent[v]=NULL;//parent�迭 �ʱ�ȭ
		visited[v]=FALSE;//visited�迭 �ʱ�ȭ
	}

}
void printParent(int* parent,int start,int v){
	//parent�� �������� Ž���ؼ� ���������� ����Ѵ�.
	if(parent[v]!=start) {
		printParent(parent,start,parent[v]);
	}
	printf("%d ",parent[v]);
}
//���� ���� start���� ����Ͽ� ��ǥ ���� goal�� ã�� �� ������ Ž���ϰ�, ã���� �� ��λ��� �����鸸 ������� ���
void dfs_list_path(GraphType *g, int start, int goal)
{
	GraphNode *w;
	visited[start]=TRUE;
		
	for(w=g->adj_list[start];w;w=w->link){
		if(!visited[w->vertex]){
			if(start==goal) {printf("%d*",start);break;} //�ڱ��ڽ��� �������� ����
			parent[w->vertex]=start; //parent�迭�� ������ ���� ����
			dfs_list_path(g,w->vertex,goal);
		}
		if(visited[goal]&&w->vertex==goal){ 
			printParent(parent,startV,w->vertex);//ã���� �� ��λ��� �����鸸 ������� ���*/
			printf("%d*",w->vertex);
			break;//��ǥ ���� goal�� ã�� �� ������ Ž��
		}
		
	}
	
}

GraphType* makeMaze(GraphType *g){

	//	# �ڵ� �ۼ� (�ʱ�ȭ)
	//	��Ʈ : graph_init �Լ� �̿�
	graph_init(g);


	//	# �ڵ� �ۼ� (����, ���� ����)
	//	��Ʈ : insert_vertex, insert_edge �Լ� �̿�
	insert_vertex(g,0);//���� ����
	insert_vertex(g,1);
	insert_vertex(g,2);
	insert_vertex(g,3);
	insert_vertex(g,4);
	insert_vertex(g,5);
	insert_vertex(g,6);
	insert_vertex(g,7);
	insert_vertex(g,8);
	insert_vertex(g,9);
	insert_vertex(g,10);
	insert_vertex(g,11);
	insert_vertex(g,12);

	insert_edge(g,0,1);//���� ����
	insert_edge(g,0,6);
	insert_edge(g,1,2);
	insert_edge(g,2,3);
	insert_edge(g,3,4);
	insert_edge(g,2,5);
	insert_edge(g,6,7);
	insert_edge(g,7,8);
	insert_edge(g,8,9);
	insert_edge(g,9,10);
	insert_edge(g,10,11);
	insert_edge(g,11,12);


	return g;
}

void help()
{
	printf("\n*****************************\n");
	printf("�̷� ã�⸦ �����Ͻðڽ��ϱ�?(y/n)\n");
	printf("*****************************\n");
}
 
void main()
{
	char command;
	int k = 0;
	int start,goal;
	

	// �̷� ����
	GraphType *g= (GraphType *)malloc(sizeof(GraphType));
	g = makeMaze(g);

	do{
		help();
		command = getchar();
		fflush(stdin);
		

		switch(command){

		case 'y':
			// # �ڵ� �ۼ� (�̷� ã��)
			//	��Ʈ : dfs_list �Լ� �̿�
			printf("��������:");
			if(scanf("%d",&start)==0) break;
			startV=start;
			
			printf("��ǥ����:");
			if(scanf("%d",&goal)==0) break;
			fflush(stdin);
			dfs_list_path(g,start,goal);
			dfs_list_init();
			break;
		}
	} while(command != 'n');
}