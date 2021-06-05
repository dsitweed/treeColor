#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
//typedef element_t ELEMENTTYPE;
typedef struct queuenode_t
{
  ELEMENTTYPE element;
  struct node_t *next;
}QueueNode;
typedef struct queue_t
{
  QueueNode *front;
  QueueNode *rear;
}QueueType;

int isempty(const QueueType *p)
{ if(p->front == NULL) return 1;
  else return 0;
}
int full()
{
  printf("FULL\n");
  return 1;
}

//void displayNode(node *p);

node *makeNewNode(ELEMENTTYPE el)
{
  node *new;
  new = (node*) malloc(sizeof(node));
  new->next = NULL;
  new->element = el;
  return new;
}

void EnQueue(ELEMENTTYPE el,QueueType *p)
{
  node *new = makeNewNode(el);
  if (new == NULL)
    {
      full();
      return;
    }
  if (isempty(p))
    {
      p->front = new;
      p->rear = new;
      return ;
    }
  p->rear->next = new;
  p->rear = new;
}

ELEMENTTYPE DeQueue(QueueType *p)
{
  node *luunode;
  ELEMENTTYPE luudata;
  if(isempty(p) == 1)
    {
      printf("Stack rong\n");
    }
  else
    {
  luunode = p->front;
  luudata = luunode->element;
  p->front = luunode->next;
  free(luunode);
  return luudata;
    }
}

QueueType *khoitao()
{
  QueueType *p;
  p = (QueueType*) malloc (sizeof(QueueType));
  if(p == NULL) return NULL;
  p->front = NULL;
  p->rear = NULL;
  return p;
}

void stravelList(QueueType *p)
{
  node *run;
  if (isempty(p) == 1)
    {
      printf("Stack Empty\n");
      return;
    }
  for (run = p->front; run != NULL; run = run->next)
    {
      displayNode(run);
    }
}



