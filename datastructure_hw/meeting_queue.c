#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 200

typedef struct { //큐 및 변수 선언
	char client[MAX_QUEUE_SIZE][MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char *message){ //에러메세지 송출
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//함수 선언부
void init(QueueType *);
int is_empty(QueueType *);
int is_full(QueueType *);
void enqueue(QueueType *, char *);
char * dequeue(QueueType *);
void matching(QueueType *, QueueType *, char *);

void init(QueueType *q) { //front와 rear을 초기화한다.
	q->front = q->rear= 0;
}
int is_empty(QueueType *q) { //큐가 비었을 때
	return(q->front == q->rear);
}
int is_full(QueueType *q) { //큐가 포화상태일 때
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}
void enqueue (QueueType *q, char * client) { //큐에 삽입
	if(is_full(q)) {
		error("대기인원이 만원입니다."); 
	}
	q->rear = (q->rear+1)%MAX_QUEUE_SIZE;
	strcpy(q->client[q->rear], client);
}
char * dequeue(QueueType *q) { //큐에서 불러냄
	if(is_empty(q)) {
		error("대기열에 아무도 없습니다."); 
	}
	q->front = (q->front+1) % MAX_QUEUE_SIZE;
	return q->client[q->front];
}
void matching(QueueType * queue, QueueType * couple, char * client) { //매칭 시스템
	if(is_empty(couple)) {
		printf("아직 대상자가 없습니다. 기다려 주세요.\n");
		enqueue(queue, client);
	}
	else {
		printf("커플이 탄생하였습니다! %s과 %s \n", client, dequeue(couple));
	}
}

int main(void)
{
	char scanner[100]; //사용자 입력 받아오는 변수
	char sex; //성별 판별 변수

	//큐 선언
	QueueType Male;
	QueueType Female;
	//큐 초기화
	init(&Male);
	init(&Female);

	printf("미팅 주선 프로그램입니다.\n");

	while(1)
	{
		printf("고객이름 : ");
		scanf("%s", scanner);

		while(1) {
			printf("성별을 입력하세요(f or m) : ");
			fflush(stdin);
			scanf("%c", &sex);

			if (sex=='f'){ //입력받은 성별이 여성일 경우
				matching(&Female, &Male, scanner);
				break;
			}
			else if (sex=='m'){ //입력받은 성별이 남성일 경우
				matching(&Male, &Female, scanner);
				break;
			}
			else{
				printf("올바르지 않은 입력입니다.");
			}
		}
	}
	return 0;
}