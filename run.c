#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#include "run.h"
#include "util.h"
#define bf 512
int base_f=0;
void *base=0;
p_meta temp_base;
p_meta find_meta(p_meta *last, size_t size) {
  p_meta index = base;
  p_meta result = base;

  switch(fit_flag){
    case FIRST_FIT:
    {
      //FIRST FIT CODE
	while(index->next!=0)
	{
		if(index->free==0&&size<=index->size) 
		result = index;
		else if(index->free==0)
		index =index->next;
		else index=index->next;
	//	else if(!index->next)  result =index;
	/*index= index->next;*/ last=index->next;
}}
    break;

    case BEST_FIT:
    {
//BEST_FIT CODE
}
    break;

    case WORST_FIT:
    {
      //WORST_FIT CODE
    }
    break;

  
  return result;
}
}
void *m_malloc(size_t size) {

//int tem1=size+META_SIZE;
//int tem2;
p_meta p;

if(size%4!=0)
{
size=size/4;
size=(size+1)*4;
}
p=sbrk(size+META_SIZE);

if(base_f==0)
{p->next=NULL;
p->prev=NULL;
base=p;}
else
{p_meta temp_prev; 
temp_prev=temp_base;
temp_prev->next=p;
p->prev=temp_base;
p->next=NULL;}

p->free=0;
p->size=size;

temp_base=p;
base_f=1;

return p->data;}


void m_free(void *ptr) {
if (ptr==NULL) return;
p_meta find;

ptr= ptr-META_SIZE;
find = ptr;
find->free=1;

if(find->prev!=NULL&&find->next!=NULL){
if((find->free==1)&&(find->prev->free==1)){
find->prev->size=find->prev->size+find->size+28;
find->prev->next=find->next;
if(find->next!=NULL)
find->next->prev=find->prev;
}
else if((find->free==1)&&(find->next->free==1))
{
find->size=find->size+find->next->size+28;
if(find->next->next!=NULL)
{
find->next=find->next->next;
find->next->prev=find;
}
}
}


else if(find->next!=NULL){
if((find->free==1)&&(find->next->free==1))
{find->size=find->size+find->next->size+28;
if(find->next->next!=NULL){
find->next=find->next->next;
find->next->prev=find;
}
else
{find->next->prev=NULL;
find->next=NULL;
}
}
}
else if(find->prev!=NULL)
{if((find->free==1)&&(find->prev->free==1)){
find->prev->next=NULL;
find->prev=NULL;
}
else
{
find->prev->next=NULL;
find->prev=NULL;
}
}
}

void* m_realloc(void* ptr, size_t size)
{
p_meta pre2 =ptr-META_SIZE;
if(size>=pre2->size)
{
if(pre2->next&&pre2->next->free&&pre2->size+pre2->next->size+META_SIZE>=size)
{
pre2->size=pre2->next->size+pre2->size+META_SIZE;
pre2->next=pre2->next->next;
pre2->next->prev=pre2;
}
}}



