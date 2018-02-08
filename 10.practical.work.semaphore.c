#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include<semaphore.h>
#define BUFFER_SIZE 10
typedef struct {
char type; // 0=fried chicken, 1=French fries
int amount; // pieces or weight
char unit; // 0=piece, 1=gram
} item;
sem_t sem;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
while ((first + 1) % BUFFER_SIZE == last) {
// do nothing -- no free buffer item
}
sem_wait(&sem);
memcpy(&buffer[first], i, sizeof(item));
first = (first + 1) % BUFFER_SIZE;
sem_post(&sem);
}

item *consume() {
item *i = malloc(sizeof(item));
while (first == last) {
// do nothing -- nothing to consume
}
sem_wait(&sem);
memcpy(i, &buffer[last], sizeof(item));
last = (last + 1) % BUFFER_SIZE;
sem_post(&sem);
return i;
}

void *threadProduce(void *param) {
// do something in the background
	item *a;
	int i = 0;
	while(i<3){
	a = malloc(sizeof(item));
	produce(a);
	i++;
	}
}
void *threadConsume(void *param) {
// do something in the background
	int i = 0;
	while(i<2){
		consume();
		i++;
	}
}

int main(){
	item *a;
	
	sem_init(&sem, 0, 1);
	
	pthread_t tid;
 	pthread_create(
		&tid, 
		NULL, 
		threadProduce, 
		NULL);
		
	pthread_join(tid, NULL);
	
	printf("first: %d\n",first);
	printf("last: %d\n",last);
	pthread_create(
		&tid,
		NULL,
		threadConsume,
		NULL
	);
		
	printf("comsume item\n");
	consume();
	pthread_join(tid, NULL);
	
	printf("first: %d\n",first);
	printf("last: %d\n",last);
	
	sem_destroy(&sem);
	return 0;
}
