// 인접 행렬을 이용한 최단 경로 계산 프로그램

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0
#define NODES 7 /* 노드의수 */
#define INF 9999 /* 무한값(연결이없는경우) */

typedef struct stack{
    int top;
    int arr[NODES];
}STACK;

// # 코드 수정 (아래 도시 간 비용과 도시 이름을 본인 그래프에 맞게 수정)
/* 도시 간 비용*/
int cost[NODES][NODES]={
	{0, 7, INF, INF, 3, 10, INF },
	{7, 0, 4, 10, 2, 6, INF },
	{INF, 4, 0, 2, INF, INF, INF },
	{INF, 10, 2, 0, 11, 9, 4 },
	{3, 2, INF, 11, 0, INF, 5 },
	{10, 6, INF, 9, INF, 0, INF },
	{INF, INF, INF, 4, 5, INF, 0 }};
char* cities[NODES] = {"서울", "수원", "대전", "광주", "인천", "대구", "청주"}; /* 도시 이름 */
char* shortestPath[NODES]; /* 최단 경로 저장 배열(ex:서울->대전->광주) */

int distance[NODES];/* 시작 노드로부터의 최단 경로 거리 */
int path[NODES]; /* 경유 노드 */
int found[NODES]; /* 방문한 노드 표시 */


int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++)
		if( distance[i]< min && ! found[i] ){
			min = distance[i];
			minpos=i;
		}
	return minpos;
}

void shortest_path(int start, int cost[][NODES], int distance[], int n, int found[]) /* 시작노드 start */
{ 
	// #  코드 작성 (최단 경로 찾기 함수)
	int i, u, w; 
	for(i=0; i<n; i++){ /* 초기화*/ 
		distance[i] = cost[start][i]; 
		path[i] = start; 
		found[i] = FALSE;
		shortestPath[i]=(char*)malloc(sizeof(char)*NODES);
		strcpy(shortestPath[i],cities[start]);

	} 
	found[start] = TRUE; /* 시작노드방문표시*/ 
	distance[start] = 0; 
	for(i=0; i<n; i++){ 
		u = choose(distance, n, found); 
		found[u] = TRUE; 
		for(w=0;w<n; w++) 
			if(!found[w]) 
				if( distance[u]+cost[u][w] < distance[w] ) {
					distance[w] = distance[u]+cost[u][w]; 
					path[w] = u; /* 경유노드저장*/ 
				} 
	} 
}

// 스택 비어있는 상태 확인 함수
int stack_empty( STACK s)
{
    if( s.top == -1)
        return 1;
    return 0;
}

// 스택 삽입 함수
void push( STACK *s, int data)
{
    s->arr[++s->top] = data;
}

// 스택 삭제 함수
int pop( STACK *s)
{
    if( stack_empty( *s))
    {
        return;
    }
    
    //printf("%s", cities[s->arr[s->top]]);
    
    return s->arr[s->top--];
}



void help()
{
	printf("*********************\n");
	printf("l: 최단 경로 가져오기\n");
	printf("c: 최단 경로 계산하기\n");
	printf("i: 최단 경로 조회하기\n");
	printf("s: 최단 경로 저장하기\n");
	printf("q: 종료\n");
	printf("*********************\n");
}
 
void main()
{
	char command;
	int start, end = 0;
	STACK s_path; // 최소 경로 저장 스택
	int i,tmp=0,v;
	FILE *f;
	char line[255];
	char*fstart;
	char* fdistance;
	char* fshortest;
	do{
		help();
		command = getchar();
		fflush(stdin);

		switch(command){
		case 'l':
			f = fopen("shortest.txt", "r");
			if( f != NULL )
			{
				//char strTemp[255];
				//char *pStr;
				i=-1;
				while( !feof( f ) && i<NODES)
				{
					fgets( line, sizeof(line), f );
					if(strstr(line,"출발 도시")!=NULL){//첫째줄이라면
						strtok(line, ":");//return "출발 도시"
						fstart=(char*)malloc(sizeof(char)*NODES);
						strcpy(fstart,strtok(NULL,"\n"));//return "서울"
					}
					else{
						strtok(line,"\t");//도시 이름
						if(!strcmp(cities[i],fstart)) start=i; //이전에읽은 출발도시와 도시이름이 같다면 start변수에 int값으로 저장
						distance[i]=atoi(strtok(NULL,"\t"));//distance
						shortestPath[i]=(char*)malloc(sizeof(char)*NODES);
						strcpy(shortestPath[i],strtok(NULL,"\n"));//최단경로
					
					}

					i++;
				}
				fclose( f );
			}

			else
			{
				//에러 처리
			}
			
			break;
		case 'c':
			// # 코드 작성 (최단 경로 계산하기)
			//             (출발 도시를 새로 입력할 때마다 distance[NODES], path[NODES], shortestPath[NODES]를 갱신
			//               -> 이전에 계산한 것은 남지 않는다)
			// hint : 1. shortest_path 함수를 이용하여 path[NODES] 배열의 값들을 구함
			//        2. 최단 경로를 구하기 위해 path[NODES] 배열의 값들을 이용하여 출발 도시와 목적 도시 간의 경로 역추적
			//        3. 역추적이기 때문에 경로가 거꾸로 나옴 -> 스택에 넣고 꺼내면서 올바른 순서대로 나열하여 저장
			printf("출발 도시를 입력하세요.\n");
			printf("{ 서울(0), 수원(1), 대전(2), 광주(3), 인천(4), 대구(5), 청주(6)}\n:");
			scanf("%d",&start);
			fflush(stdin);
			shortest_path(start,cost,distance,NODES,found);
			for(i=0;i<NODES;i++){
				printf("%s:",cities[i]);
				printf("%d\n",distance[i]);
			
				
			}
			s_path.top=-1;//스택 초기화
			for(i=0;i<NODES;i++){
				tmp=i;
				while(path[tmp]!=start){
					v=path[tmp];
					push(&s_path,v);
					tmp=path[tmp];
				}
				while(!stack_empty(s_path)){
					v=pop(&s_path);
					strcat(shortestPath[i],"->");
					strcat(shortestPath[i],cities[v]);
				}
				if(start!=i){
					strcat(shortestPath[i],"->");
					strcat(shortestPath[i],cities[i]);
				}
			}
			break;
		case 'i':
			// # 코드 작성 (최단 경로 조회하기)
			// hint : shortestPath[NODES]에 저장된 최단 경로를 이용
			printf("목적 나라를 입력하세요.\n");
			printf("{ 서울(0), 수원(1), 대전(2), 광주(3), 인천(4), 대구(5), 청주(6)}\n:");
			scanf("%d",&end);
			fflush(stdin);
			printf("%s\n",shortestPath[end]);
		
			break;
		case 's':		
			f=fopen("shortest.txt","w");
			fprintf(f,"출발 도시 :%s\n",cities[start]);
			for(i=0;i<NODES;i++){
				fprintf(f,"%s\t%d\t%s\n",cities[i],distance[i],shortestPath[i]);
			}
			fclose(f);
			break;
		}

		
	} while(command != 'q');
}