// ���� ����� �̿��� �ִ� ��� ��� ���α׷�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0
#define NODES 7 /* ����Ǽ� */
#define INF 9999 /* ���Ѱ�(�����̾��°��) */

typedef struct stack{
    int top;
    int arr[NODES];
}STACK;

// # �ڵ� ���� (�Ʒ� ���� �� ���� ���� �̸��� ���� �׷����� �°� ����)
/* ���� �� ���*/
int cost[NODES][NODES]={
	{0, 7, INF, INF, 3, 10, INF },
	{7, 0, 4, 10, 2, 6, INF },
	{INF, 4, 0, 2, INF, INF, INF },
	{INF, 10, 2, 0, 11, 9, 4 },
	{3, 2, INF, 11, 0, INF, 5 },
	{10, 6, INF, 9, INF, 0, INF },
	{INF, INF, INF, 4, 5, INF, 0 }};
char* cities[NODES] = {"����", "����", "����", "����", "��õ", "�뱸", "û��"}; /* ���� �̸� */
char* shortestPath[NODES]; /* �ִ� ��� ���� �迭(ex:����->����->����) */

int distance[NODES];/* ���� ���κ����� �ִ� ��� �Ÿ� */
int path[NODES]; /* ���� ��� */
int found[NODES]; /* �湮�� ��� ǥ�� */


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

void shortest_path(int start, int cost[][NODES], int distance[], int n, int found[]) /* ���۳�� start */
{ 
	// #  �ڵ� �ۼ� (�ִ� ��� ã�� �Լ�)
	int i, u, w; 
	for(i=0; i<n; i++){ /* �ʱ�ȭ*/ 
		distance[i] = cost[start][i]; 
		path[i] = start; 
		found[i] = FALSE;
		shortestPath[i]=(char*)malloc(sizeof(char)*NODES);
		strcpy(shortestPath[i],cities[start]);

	} 
	found[start] = TRUE; /* ���۳��湮ǥ��*/ 
	distance[start] = 0; 
	for(i=0; i<n; i++){ 
		u = choose(distance, n, found); 
		found[u] = TRUE; 
		for(w=0;w<n; w++) 
			if(!found[w]) 
				if( distance[u]+cost[u][w] < distance[w] ) {
					distance[w] = distance[u]+cost[u][w]; 
					path[w] = u; /* �����������*/ 
				} 
	} 
}

// ���� ����ִ� ���� Ȯ�� �Լ�
int stack_empty( STACK s)
{
    if( s.top == -1)
        return 1;
    return 0;
}

// ���� ���� �Լ�
void push( STACK *s, int data)
{
    s->arr[++s->top] = data;
}

// ���� ���� �Լ�
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
	printf("l: �ִ� ��� ��������\n");
	printf("c: �ִ� ��� ����ϱ�\n");
	printf("i: �ִ� ��� ��ȸ�ϱ�\n");
	printf("s: �ִ� ��� �����ϱ�\n");
	printf("q: ����\n");
	printf("*********************\n");
}
 
void main()
{
	char command;
	int start, end = 0;
	STACK s_path; // �ּ� ��� ���� ����
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
					if(strstr(line,"��� ����")!=NULL){//ù°���̶��
						strtok(line, ":");//return "��� ����"
						fstart=(char*)malloc(sizeof(char)*NODES);
						strcpy(fstart,strtok(NULL,"\n"));//return "����"
					}
					else{
						strtok(line,"\t");//���� �̸�
						if(!strcmp(cities[i],fstart)) start=i; //���������� ��ߵ��ÿ� �����̸��� ���ٸ� start������ int������ ����
						distance[i]=atoi(strtok(NULL,"\t"));//distance
						shortestPath[i]=(char*)malloc(sizeof(char)*NODES);
						strcpy(shortestPath[i],strtok(NULL,"\n"));//�ִܰ��
					
					}

					i++;
				}
				fclose( f );
			}

			else
			{
				//���� ó��
			}
			
			break;
		case 'c':
			// # �ڵ� �ۼ� (�ִ� ��� ����ϱ�)
			//             (��� ���ø� ���� �Է��� ������ distance[NODES], path[NODES], shortestPath[NODES]�� ����
			//               -> ������ ����� ���� ���� �ʴ´�)
			// hint : 1. shortest_path �Լ��� �̿��Ͽ� path[NODES] �迭�� ������ ����
			//        2. �ִ� ��θ� ���ϱ� ���� path[NODES] �迭�� ������ �̿��Ͽ� ��� ���ÿ� ���� ���� ���� ��� ������
			//        3. �������̱� ������ ��ΰ� �Ųٷ� ���� -> ���ÿ� �ְ� �����鼭 �ùٸ� ������� �����Ͽ� ����
			printf("��� ���ø� �Է��ϼ���.\n");
			printf("{ ����(0), ����(1), ����(2), ����(3), ��õ(4), �뱸(5), û��(6)}\n:");
			scanf("%d",&start);
			fflush(stdin);
			shortest_path(start,cost,distance,NODES,found);
			for(i=0;i<NODES;i++){
				printf("%s:",cities[i]);
				printf("%d\n",distance[i]);
			
				
			}
			s_path.top=-1;//���� �ʱ�ȭ
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
			// # �ڵ� �ۼ� (�ִ� ��� ��ȸ�ϱ�)
			// hint : shortestPath[NODES]�� ����� �ִ� ��θ� �̿�
			printf("���� ���� �Է��ϼ���.\n");
			printf("{ ����(0), ����(1), ����(2), ����(3), ��õ(4), �뱸(5), û��(6)}\n:");
			scanf("%d",&end);
			fflush(stdin);
			printf("%s\n",shortestPath[end]);
		
			break;
		case 's':		
			f=fopen("shortest.txt","w");
			fprintf(f,"��� ���� :%s\n",cities[start]);
			for(i=0;i<NODES;i++){
				fprintf(f,"%s\t%d\t%s\n",cities[i],distance[i],shortestPath[i]);
			}
			fclose(f);
			break;
		}

		
	} while(command != 'q');
}