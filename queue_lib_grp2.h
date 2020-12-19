// Group No. 2
// Rahul Jain.    1912037
// Biley Roy.       1912045
// Ripunjoy Sarma.   1912078
// Anurag Saraswat. 1912079
// Darsh Kaushik.       1912080

// C library to perform queue operations 
// Warnings during compilation can be safely neglected

//---------------------------------------------------------------------------------
// Guidelines:

//Implementation of queue--> Circular Array Representation
//The library is generic and functions are made using void* 
//The library supports basic primitive data types --> int,char,float,double and string
//Remember to use (deref_int/deref_char/deref_string/deref_long/deref_float/deref_double) to access the elements 
//when storing/printing the returned values of the function.(For more info check out the header file)

//---------------------------------------------------------------------------------

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define INT 0
#define CHAR 1
#define STRING 2
#define LONG_INT 3
#define FLOAT 4
#define DOUBLE 5

//---------------------------------------------------------------------------------
// Functions to dereference generic void pointers to specific 
// pointers of the type specified by the user

int deref_int(void* x){
    return (*(int*)x);
}
char deref_char(void * x){
    return (*(char*)x);
}
char* deref_string(void* x){
    return ((char*)x);
}
long long int deref_long(void* x){
    return (*(long long int*)x);
}
float deref_float(void* x){
    return (*(float*)x);
}
double deref_double(void* x){
    return (*(double*)x);
}

//---------------------------------------------------------------------------------
//Functions for queues

// Struct for Queue 
struct Queue {
	int front, rear, size;
	int capacity;
	void* array[100000];
	int type;
};

// Function to create an instance of queue of the type specified by user
struct Queue* createQueue(int x)
{
	struct Queue* queue = (struct Queue*)malloc(
		sizeof(struct Queue));
	queue->capacity = 100000;
	queue->size = 0;
	queue->front =queue->rear = -1;
	queue->type=x;
	return queue;
}

// Function to return size of the queue
int queue_size(struct Queue* queue)
{
	return queue->size;
}

// Function to check for overflow
int isFull(struct Queue* queue)
{
	return (queue->size == queue->capacity);
}

// Function to check if queue is empty
int isEmpty(struct Queue* queue)
{
	return (queue->size == 0);
}

// Function to enqueue an element according to the type provided
void enqueue(struct Queue* queue, ...)
{
	if (isFull(queue)){
		printf("Overflow!!\n");
		return;
	}
		
	queue->rear =(queue->rear+1)%queue->capacity;

	void *temp=malloc(100);

	// initialize valist for the argument of unknown type
	va_list valist;
	va_start(valist, 1);

	if (queue->type==0)
	{
		int item_int = va_arg(valist, int);
		memcpy(temp, &item_int, 4);
	}
	else if (queue->type==1)
	{
		char item_char = va_arg(valist, int);
		memcpy(temp, &item_char, 1);
	}
	else if(queue->type==2)
	{
		char* item_str = va_arg(valist, char*);
		memcpy(temp, (void*)item_str, strlen((const char*)item_str)+1);
	}
	else if(queue->type==3){
        long long int item_int = va_arg(valist, long long int);
		memcpy(temp, &item_int, 100);
	}
	else if(queue->type==4){
        float item_int = va_arg(valist, double);
		memcpy(temp, &item_int, 8);
	}
    else if(queue->type==5){
        double item_int = va_arg(valist, double);
		memcpy(temp, &item_int, 100);
	}
	va_end(valist);
	queue->array[queue->rear] = temp;
	queue->size = queue->size + 1;
	if(queue->front==-1){
		queue->front=queue->rear;
	}

}

// Function to dequeue an element
void* dequeue(struct Queue* queue)
{
	if (isEmpty(queue)){
		printf("Underflow\n");
		return NULL;
	}
		
	void* item = queue->array[queue->front];
	if(queue->front==queue->rear){//only one element
		queue->front=queue->rear=-1;
		queue->size=0;
	}
	else{
		queue->front = (queue->front + 1)%queue->capacity;
		queue->size = queue->size - 1;
	}
	
	
	return item;

}

// Function to print the queue
void print_queue(struct Queue* queue){
	if(queue->type==0){
		for(int i=queue->front;i<(queue->front+queue->size);i++){
			printf("%d ",(*(int*)(queue->array[i%queue->capacity])));
		}
		printf("\n");
	}
	else if(queue->type==1){
		for(int i=queue->front;i<(queue->front+queue->size);i++){
			printf("%c ",(*(char*)(queue->array[i%queue->capacity])));
		}
		printf("\n");
	}
	else if(queue->type==2){
		for(int i=queue->front;i<(queue->front+queue->size);i++){
			printf("%s ",(queue->array[i%queue->capacity]));
		}
		printf("\n");
	}
	else if(queue->type==3){
		for(int i=queue->front;i<(queue->front+queue->size);i++){
			printf("%lld ",(*(long long int*)(queue->array[i%queue->capacity])));
		}
		printf("\n");
	}
	else if(queue->type==4){
		for(int i=queue->front;i<(queue->front+queue->size);i++){
			printf("%f ",(*(float*)(queue->array[i%queue->capacity])));
		}
		printf("\n");
	}
    else if(queue->type==5){
		for(int i=queue->front;i<(queue->front+queue->size);i++){
			printf("%lf ",(*(double*)(queue->array[i%queue->capacity])));
		}
		printf("\n");
	}


}

// Function to swap two queues
void swap_queue(struct Queue** q1, struct Queue** q2){
    struct Queue* temp=*q1;
    *q1=*q2;
    *q2=temp;
}

// Function to access the front element of the queue
void* front(struct Queue* queue)
{
	if (isEmpty(queue)){
		printf("Queue is Empty!\n");
		return NULL;
	}
	return queue->array[queue->front];
}

// Function to access rear of queue
void* rear(struct Queue* queue)
{
	if (isEmpty(queue))
		return NULL;
	return queue->array[queue->rear];
}

//---------------------------------------------------------------------------------
//Functions for stack using queues

// Struct for Stack which uses two queues for its operations 
struct Stack{
	struct Queue *q1;
	struct Queue *q2;
	int curr_size;
};

// Function to create an instance of stack of the type specified by user
struct Stack* createStack(int x){
    struct Stack* s=(struct Stack*)malloc(
		sizeof(struct Stack));
	s->q1=createQueue(x);
	s->q2=createQueue(x);
	s->curr_size=0;
    return s;
}

// Function to push an element in the stack
void push_stack(struct Stack* s, ...){
	if((s->q1)->size>=(s->q1)->capacity){
		printf("Stack Overflow!!\n");
		return;
	}
	s->curr_size++;
	va_list valist;
	va_start(valist, 1);
	if ((s->q1)->type==0)
	{
		int item_int = va_arg(valist, int);
		enqueue(s->q2,item_int);

	}
	else if ((s->q1)->type==1)
	{
		char item_char = va_arg(valist, int);
		enqueue(s->q2,item_char);

	}
	else if ((s->q1)->type==2)
	{
		char *item_str = va_arg(valist, char*);
		enqueue(s->q2,item_str);

	}
	else if ((s->q1)->type==3)
	{
		long long int item_int = va_arg(valist,long long int);
		enqueue(s->q2,item_int);

	}
	else if ((s->q1)->type==4)
	{
		float item_int = va_arg(valist, double);
		enqueue(s->q2,item_int);

	}
    else if ((s->q1)->type==5)
	{
		double item_int = va_arg(valist, double);
		enqueue(s->q2,item_int);

	}
    va_end(valist);
	while(!isEmpty(s->q1)){

        if ((s->q1)->type==0)
        {
            int x=deref_int(dequeue(s->q1));
            enqueue(s->q2,x);

        }
        else if ((s->q1)->type==1)
        {
            char x=deref_char(dequeue(s->q1));
            enqueue(s->q2,x);

        }
        else if ((s->q1)->type==2)
        {
            char* x=deref_string(dequeue(s->q1));
            enqueue(s->q2,x);

        }
        else if ((s->q1)->type==3)
        {
            long long int x=deref_long(dequeue(s->q1));
            enqueue(s->q2,x);

        }
        else if ((s->q1)->type==4)
        {
            float x=deref_float(dequeue(s->q1));
            enqueue(s->q2,x);

        }
        else if ((s->q1)->type==5)
        {
            double x=deref_double(dequeue(s->q1));
            enqueue(s->q2,x);

        }
        
	}

	struct Queue* q3=s->q1;
	s->q1=s->q2;
	s->q2=q3;
}

// Function to pop an element from the stack
void* pop_stack(struct Stack* s){
	if(isEmpty(s->q1)){
		printf("Stack is empty!!\n");
		return NULL;
	}
	void * x=dequeue(s->q1);
	s->curr_size--;
	return x;

}

// Function to access the top element of the stack
void* top(struct Stack* s){
	if(isEmpty(s->q1)){
		printf("Stack is Empty!\n");
		return NULL;
	}
	return front(s->q1);
}

// Function to print the stack
void print_stack(struct Stack* S)
{
	print_queue(S->q1);
}

// Function to return size of the stack
int stack_size(struct Stack* S)
{
	return (S->q1->size);
}

