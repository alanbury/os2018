#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define BUFFER_SIZE 10
typedef struct {
char type; // 0=fried chicken, 1=French fries
int amount; // pieces or weight
char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
while ((first + 1) % BUFFER_SIZE == last) {
// do nothing -- no free buffer item
}
memcpy(&buffer[first], i, sizeof(item));
first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
item *i = malloc(sizeof(item));
while (first == last) {
// do nothing -- nothing to consume
}
memcpy(i, &buffer[last], sizeof(item));
last = (last + 1) % BUFFER_SIZE;
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
	printf("produce item\n");
	a = malloc(sizeof(item));
	produce(a);
	printf("first: %d\n",first);
	printf("last: %d\n",last);
	
	printf("produce item\n");
	a = malloc(sizeof(item));
	produce(a);
	printf("first: %d\n",first);
	printf("last: %d\n",last);
		
	pthread_t tid;
 	pthread_create(
		&tid, 
		NULL, 
		threadProduce, 
		NULL);
		
	pthread_join(tid, NULL);
	
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
	
	
	return 0;
}
