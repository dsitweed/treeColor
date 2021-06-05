//#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<graph.h>
#include "jrb.h"
#include "dllist.h"
#define max 100

typedef JRB Graph;
typedef struct
{
  int number;
  int color;
}DINH;
Graph createGraph();
void addEdge(Graph graph, int v1, int v2);// them 1 cap canh
int adjacent(Graph graph, int v1, int v2);//Cap canh co lien thong ko
int getAdjacentVertices(Graph graph, int vertex, int* output);// cac dinh noi voi vertex va nhung dinh do
void dropGraph(Graph graph);

void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));

void printVertex(int v)
{
     printf("%4d", v);
}

int main()
{
  FILE *a, *b;
  Graph g = createGraph();
  int soDinh,soCanh;
  int buffer1,buffer2;
  int chisoMangPhu;
  DINH mang[max];
  int fill[max];
  int output[max];
  char *color[] = {"red","blue","green","gray","yellow","orang","pink","brown","purple","navy","black","azure","bisque"};
  if ((a = fopen("dothi.txt","r")) == NULL)
    {
      printf("ERROR\n");
      return 1;
    }
  if ((b = fopen("dothi.dot","w")) == NULL)
    {
      printf("ERROR\n");
      return 1;
    }
  //dong thoi viet vao file .dot luon
  fprintf(b,"graph{");
  fscanf(a,"%d %d%*c",&soDinh,&soCanh);
  for (int i = 0;i < soCanh;i++)
    {
      fscanf(a,"%d %d%*c",&buffer1,&buffer2);
      fprintf(b,"%d -- %d\n",buffer1,buffer2);
      printf("%d -- %d\n",buffer1, buffer2);
      addEdge(g, buffer1,buffer2);
   }
  //bat dau tu 1
  for (int i = 0;i < soDinh;i++)
    {
      mang[i].number = i+1;
    }
  for (int i = 1;i < soDinh;i++)
    {
      buffer2 = mang[i].number;
      buffer1 = i;
      while ((buffer1 > 0) && (getAdjacentVertices(g,mang[i].number,output) > getAdjacentVertices(g,mang[buffer1-1].number,output)))
	{
	 
	  mang[buffer1].number = mang[buffer1 - 1].number;
	  buffer1--;
	}
      mang[buffer1].number = buffer2;
	}
  mang[0].color = 0;// Gan mau cho Node xuat phat
  for (int i = 1; i < soDinh;i++)// Chay cac node
    {
      mang[i].color = 0;// khoi tao cho not co mau nho nhat
      chisoMangPhu = 0;
      for (int j = 0;j <i;j++)
	{
	  if (adjacent(g,mang[i].number,mang[j].number) == 1)
	    {
	      fill[chisoMangPhu] = mang[j].color;
	      chisoMangPhu++;
	    } 
	}// tao 1 mang phu de sap xep cac mau da dung theo min ->  max
      for(int j = 0;j < chisoMangPhu;j++)
	{
	  // printf("%d - ",fill[j]);
	}
      // printf("\n");
      for (int j = 1;j < chisoMangPhu;j++)
	{
	  buffer2 = fill[j];
	  buffer1 = j;
	  while ((buffer1 > 0) && (fill[j] < fill[buffer1 - 1]) )
	    {
	      fill[buffer1] = fill[buffer1 - 1];
	      buffer1--;
	    }
	  fill[buffer1] = buffer2;
	}// sap xep cac mau da dung tu be den lon
      for (int j = 0;j < chisoMangPhu;j++)
	{
	  if (mang[i].color < fill[j]) break;
	  if (mang[i].color > fill[chisoMangPhu-1]) break;
	  if (mang[i].color >= fill[j]) mang[i].color = mang[i].color + 1;
	}// chen mau
      /* printf("%d - %d\n",i,mang[i].color); */
    }//end chay cac node

  for (int i = 0;i < soDinh;i++)
    {
      // printf("%-5d - %d  - %d\n",mang[i].number,getAdjacentVertices(g,mang[i].number,output),mang[i].color);
    }
  for (int i = 0;i < soDinh;i++)
    {
      fprintf(b,"%d [fillcolor=%s, style=filled];\n",mang[i].number,color[mang[i].color]);
    }
  fprintf(b,"}");
  fclose(a);
  fclose(b);
}

Graph createGraph()
{
   return make_jrb();
}

void addEdge(Graph graph, int v1, int v2)
{
     JRB node, tree;
     if (!adjacent(graph, v1, v2))
     {
        node = jrb_find_int(graph, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph, v1, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_i(1));
     }
     if (!adjacent(graph, v2, v1))
     {
        node = jrb_find_int(graph, v2);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph, v2, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v1, new_jval_i(1));   
     }
}

int adjacent(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph, v1);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
       return 0;
    else
       return 1;       
}

int getAdjacentVertices (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph);
}

void BFS(Graph graph, int start, int stop, void (*func)(int))
{
   int visited[1000] = {};
   int n, output[100], i, u, v;
   Dllist node, queue;
   
   queue = new_dllist();
   dll_append(queue, new_jval_i(start));

   while ( !dll_empty(queue) )
   {
      node = dll_first(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          if ( u == stop ) return;           
          n = getAdjacentVertices(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(queue, new_jval_i(v));
          }
      }
   }                            
}

void DFS(Graph graph, int start, int stop, void (*func)(int))
{
   int visited[1000] = {};
   int n, output[100], i, u, v;
   Dllist node, stack;
   
   stack = new_dllist();
   dll_append(stack, new_jval_i(start));

   while ( !dll_empty(stack) )
   {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          if ( u == stop ) return;           
          n = getAdjacentVertices(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(stack, new_jval_i(v));
          }
      }
   }                            
}
