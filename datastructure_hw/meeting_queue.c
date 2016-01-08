#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 200

typedef struct { //ť �� ���� ����
	char client[MAX_QUEUE_SIZE][MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char *message){ //�����޼��� ����
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//�Լ� �����
void init(QueueType *);
int is_empty(QueueType *);
int is_full(QueueType *);
void enqueue(QueueType *, char *);
char * dequeue(QueueType *);
void matching(QueueType *, QueueType *, char *);

void init(QueueType *q) { //front�� rear�� �ʱ�ȭ�Ѵ�.
	q->front = q->rear= 0;
}
int is_empty(QueueType *q) { //ť�� ����� ��
	return(q->front == q->rear);
}
int is_full(QueueType *q) { //ť�� ��ȭ������ ��
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}
void enqueue (QueueType *q, char * client) { //ť�� ����
	if(is_full(q)) {
		error("����ο��� �����Դϴ�."); 
	}
	q->rear = (q->rear+1)%MAX_QUEUE_SIZE;
	strcpy(q->client[q->rear], client);
}
char * dequeue(QueueType *q) { //ť���� �ҷ���
	if(is_empty(q)) {
		error("��⿭�� �ƹ��� �����ϴ�."); 
	}
	q->front = (q->front+1) % MAX_QUEUE_SIZE;
	return q->client[q->front];
}
void matching(QueueType * queue, QueueType * couple, char * client) { //��Ī �ý���
	if(is_empty(couple)) {
		printf("���� ����ڰ� �����ϴ�. ��ٷ� �ּ���.\n");
		enqueue(queue, client);
	}
	else {
		printf("Ŀ���� ź���Ͽ����ϴ�! %s�� %s \n", client, dequeue(couple));
	}
}

int main(void)
{
	char scanner[100]; //����� �Է� �޾ƿ��� ����
	char sex; //���� �Ǻ� ����

	//ť ����
	QueueType Male;
	QueueType Female;
	//ť �ʱ�ȭ
	init(&Male);
	init(&Female);

	printf("���� �ּ� ���α׷��Դϴ�.\n");

	while(1)
	{
		printf("���̸� : ");
		scanf("%s", scanner);

		while(1) {
			printf("������ �Է��ϼ���(f or m) : ");
			fflush(stdin);
			scanf("%c", &sex);

			if (sex=='f'){ //�Է¹��� ������ ������ ���
				matching(&Female, &Male, scanner);
				break;
			}
			else if (sex=='m'){ //�Է¹��� ������ ������ ���
				matching(&Male, &Female, scanner);
				break;
			}
			else{
				printf("�ùٸ��� ���� �Է��Դϴ�.");
			}
		}
	}
	return 0;
}