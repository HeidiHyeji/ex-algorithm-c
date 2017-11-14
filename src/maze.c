// 인접 리스트를 이용한 미로 찾기

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_VERTICES 13
int visited[MAX_VERTICES];
int parent[MAX_VERTICES];//정점 v 직전에 방문한 인접 정점의 번호를 저장
int TRUE = 1;
int FALSE = 0;
int startV;

typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의개수
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

// 그래프초기화
void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
	//	# 코드 작성 (정점 삽입)
	if(((g->n)+1)>MAX_VERTICES){
		fprintf(stderr,"그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산, v를 u의인접리스트에삽입한다.
void insert_edge(GraphType *g, int u, int v)
{
	//	# 코드 작성 (간선 삽입)
	GraphNode *node;
	if(u>=g->n || v>=g->n){
		fprintf(stderr,"그래프: 정점번호오류");
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
		parent[v]=NULL;//parent배열 초기화
		visited[v]=FALSE;//visited배열 초기화
	}

}
void printParent(int* parent,int start,int v){
	//parent를 역순으로 탐색해서 시작점부터 출력한다.
	if(parent[v]!=start) {
		printParent(parent,start,parent[v]);
	}
	printf("%d ",parent[v]);
}
//시작 정점 start에서 출발하여 목표 정점 goal을 찾을 때 까지만 탐색하고, 찾아진 해 경로상의 정점들만 순서대로 출력
void dfs_list_path(GraphType *g, int start, int goal)
{
	GraphNode *w;
	visited[start]=TRUE;
		
	for(w=g->adj_list[start];w;w=w->link){
		if(!visited[w->vertex]){
			if(start==goal) {printf("%d*",start);break;} //자기자신이 목적지면 리턴
			parent[w->vertex]=start; //parent배열에 이전의 정점 저장
			dfs_list_path(g,w->vertex,goal);
		}
		if(visited[goal]&&w->vertex==goal){ 
			printParent(parent,startV,w->vertex);//찾아진 해 경로상의 정점들만 순서대로 출력*/
			printf("%d*",w->vertex);
			break;//목표 정점 goal을 찾을 때 까지만 탐색
		}
		
	}
	
}

GraphType* makeMaze(GraphType *g){

	//	# 코드 작성 (초기화)
	//	힌트 : graph_init 함수 이용
	graph_init(g);


	//	# 코드 작성 (정점, 간선 삽입)
	//	힌트 : insert_vertex, insert_edge 함수 이용
	insert_vertex(g,0);//정점 삽입
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

	insert_edge(g,0,1);//간선 삽입
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
	printf("미로 찾기를 시작하시겠습니까?(y/n)\n");
	printf("*****************************\n");
}
 
void main()
{
	char command;
	int k = 0;
	int start,goal;
	

	// 미로 생성
	GraphType *g= (GraphType *)malloc(sizeof(GraphType));
	g = makeMaze(g);

	do{
		help();
		command = getchar();
		fflush(stdin);
		

		switch(command){

		case 'y':
			// # 코드 작성 (미로 찾기)
			//	힌트 : dfs_list 함수 이용
			printf("시작정점:");
			if(scanf("%d",&start)==0) break;
			startV=start;
			
			printf("목표정점:");
			if(scanf("%d",&goal)==0) break;
			fflush(stdin);
			dfs_list_path(g,start,goal);
			dfs_list_init();
			break;
		}
	} while(command != 'n');
}