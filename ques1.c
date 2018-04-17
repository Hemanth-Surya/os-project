#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
int num_seat=3;
int sleep_max=5;
sem_t sem_stu;
sem_t sem_TA;
pthread_mutex_t mutex;
int chair[3];
int count = 0;
int next_seat = 0;
int next_teach = 0;
void rand_sleep(void);
void* stu_programming(void* stu_id);
void* TA_teaching();
int main()
{
pthread_t *students;
pthread_t TA;
int* student_ids;
int student_num;
int i;
printf("How many students? ");
scanf("%d", &student_num);
students = (pthread_t*)malloc(sizeof(pthread_t) * student_num);
student_ids = (int*)malloc(sizeof(int) * student_num);
//memset(student_ids, 0, student_num);
sem_init(&sem_stu,0,0);
sem_init(&sem_TA,0,1);
srand(time(NULL));
pthread_mutex_init(&mutex,NULL);
pthread_create(&TA,NULL,TA_teaching,NULL);
for(i=0; i<student_num; i++)
{
	student_ids[i] = i+1;
	pthread_create(&students[i], NULL, stu_programming, (void*) &student_ids[i]);
}
pthread_join(TA, NULL);
for(i=0; i<student_num;i++)
{
	pthread_join(students[i],NULL);
}
return 0;
}
void* stu_programming(void* stu_id)
{
	int id = *(int*)stu_id;
    printf("[stu] student %d is programming\n",id);
	while(1)
	{
		rand_sleep();
		pthread_mutex_lock(&mutex);
		if(count < num_seat)
		{
			chair[next_seat] = id;
			count++;
			printf("	[stu] student %d is waiting\n",id);
			printf("waiting students : [1] %d [2] %d [3] %d\n",chair[0],chair[1],chair[2]);
			next_seat = (next_seat+1) % num_seat;
			pthread_mutex_unlock(&mutex);
			sem_post(&sem_stu);
			sem_wait(&sem_TA);
		}
		else
		{
			pthread_mutex_unlock(&mutex);
			printf("[stu] no more chairs. student %d is programming\n",id);
		}
	}
}
void* TA_teaching()
{
	while(1)
	{
		sem_wait(&sem_stu);
		pthread_mutex_lock(&mutex);
		printf("		[TA] TA is teaching student %d\n",chair[next_teach]);
		chair[next_teach]=0;
		count--;
		printf("waiting students : [1] %d [2] %d [3] %d\n",chair[0],chair[1],chair[2]);
		next_teach = (next_teach + 1) % num_seat;
		rand_sleep();
		printf("		[TA] teaching finish.\n");
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_TA);
	}
}
void rand_sleep(void){
	int time = rand() % sleep_max + 1;
	sleep(time);
}
