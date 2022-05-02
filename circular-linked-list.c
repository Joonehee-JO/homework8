/*
*  doubly circular linked list
*
*  Data Structures
*
*  Department of Computer Science
*  at Chungbuk National University
*
*/



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
int key;
struct Node* llink;
struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);      //초기화하는 함수
int freeList(listNode* h);         //할당된 메모리를 해제하는 함수
int insertLast(listNode* h, int key);   //노드를 연결리스트의 마지막에 삽입하는 함수
int deleteLast(listNode* h);         //연결리스트의 마지막노드를 삭제하는 함수
int insertFirst(listNode* h, int key);   //연결리스트의 처음에 노드를 삽입하는 함수
int deleteFirst(listNode* h);         //연결리스트의 첫노드를 삭제하는 함수
int invertList(listNode* h);         //연결리스트를 역순으로 배치하는 함수

int insertNode(listNode* h, int key);   //입력key값보다 큰 값을 노드 바로 앞에 삽입하는 함수
int deleteNode(listNode* h, int key);   //입력key값을 갖는 노드를 삭제하는 함수

void printList(listNode* h);         //연결리스트를 출력하는 함수



int main()
{
   char command;
   int key;
   listNode* headnode=NULL;

   printf("[----- [Cho Joon Hee] [2017038076] -----]\n");   

   do{
      printf("----------------------------------------------------------------\n");
      printf("                  Doubly Circular Linked List                   \n");
      printf("----------------------------------------------------------------\n");
      printf(" Initialize    = z           Print         = p \n");
      printf(" Insert Node   = i           Delete Node   = d \n");
      printf(" Insert Last   = n           Delete Last   = e\n");
      printf(" Insert First  = f           Delete First  = t\n");
      printf(" Invert List   = r           Quit          = q\n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");   //커맨드 입력
      scanf(" %c", &command);

      switch(command) {
      case 'z': case 'Z':
         initialize(&headnode);   //메모리 초기화
         break;
      case 'p': case 'P':
         printList(headnode);   //연결리스트 출력
         break;
      case 'i': case 'I':
         printf("Your Key = ");
         scanf("%d", &key);
         insertNode(headnode, key);   //노드 삽입
         break;
      case 'd': case 'D':
         printf("Your Key = ");
         scanf("%d", &key);
         deleteNode(headnode, key);   //입력 key값을 갖는 노드 삭제
         break;
      case 'n': case 'N':
         printf("Your Key = ");
         scanf("%d", &key);
         insertLast(headnode, key);   //리스트의 마지막에 삽입
         break;
      case 'e': case 'E':
         deleteLast(headnode);      //리스트의 마지막 노드 삭제
         break;
      case 'f': case 'F':
         printf("Your Key = ");
         scanf("%d", &key);
         insertFirst(headnode, key);   //리스트의 처음에 노드 삽입
         break;
      case 't': case 'T':
         deleteFirst(headnode);      //리스트의 첫노드 삭제
         break;
      case 'r': case 'R':
         invertList(headnode);      //리스트를 역순으로 배치
         break;
      case 'q': case 'Q':
         freeList(headnode);         //할당된 메모리 해제
         break;
      default:
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   }while(command != 'q' && command != 'Q');

   return 1;
}


int initialize(listNode** h) {   //초기화하는 함수

/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
   if(*h != NULL)
      freeList(*h);

   /* headNode에 대한 메모리를 할당하여 리턴 */
   *h = (listNode*)malloc(sizeof(listNode));
   (*h)->rlink = *h;   //rlink와 llink에 자기자신을 가리키도록함
   (*h)->llink = *h;
   (*h)->key = -9999;
   return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){   //링크드리스트 메모리해제하는 함수
   if(h->rlink == h)   //노드가 존재하지 않을 경우
   {
      free(h);      //할당받은 헤더노드 메모리 반납
      return 1;
   }

   listNode* p = h->rlink;   //현재노드를 가리킬 포인터
   listNode* prev = NULL;   //삭제하고자하는 노드를 가리킬 포인터

   while(p != h){      //연결리스트에 존재하는 노드를 돌면서
      prev = p;      //prev가 삭제하고자하는 노드를 가리키도록함
      p = p->rlink;   //p는 다음노드를 가리키도록함
      free(prev);      //prev가 가리키는 메모리 반납
   }
   free(h);      //마지막으로 헤더노드 메모리 반납

   return 0;
}



void printList(listNode* h) {   //연결리스트를 출력하는 함수
   int i = 0;      //리스트의 인덱스
   listNode* p;   //현재노드를 가리킬 포인터

   printf("\n---PRINT\n");

   if(h == NULL) {      //할당받은 메모리가 없을 경우
      printf("Nothing to print....\n");
      return;
   }

   p = h->rlink;   //p가 첫 노드를 가리키도록함

   while(p != NULL && p != h) {   //존재하는 노드를 돌면서
      printf("[ [%d]=%d ] ", i, p->key);   //출력
      p = p->rlink;
      i++;
   }
   printf("  items = %d\n", i);


   /* print addresses */
   printf("\n---checking addresses of links\n");
   printf("-------------------------------\n");
   printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

   i = 0;
   p = h->rlink;
   while(p != NULL && p != h) {   //각 노드가 갖고있는 주소값 출력
      printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
      p = p->rlink;
      i++;
   }

}



/**
 * list에 key에 대한 노드하나를 추가ㅊ
 */
int insertLast(listNode* h, int key) {   //key를 갖는 노드를 연결리스트 마지막에 삽입하는 함수
   if(h==NULL){   //헤더노드가 메모리를 할당받지 못했을 경우
      printf("the memory is not allocated\n");
      return 1;
   }

   listNode *temp = (listNode*)malloc(sizeof(listNode));   //삽입할 노드를 메모리할당받음
   temp->key = key, temp->rlink = NULL, temp->llink = NULL;   //삽입할 노드 필드값 설정

   if(h->rlink == h){      //연결리스트에 노드가 없을 경우
      h->llink = temp;   //헤더노드의 llink와 rrlink를 삽입할노드로 변경
      h->rlink = temp;   
      temp->rlink = h;   //삽입노드의 llink와 rlink를 헤더노드로 변경(연결리스트에 노드가 새로 추가됨)
      temp->llink = h;
      return 1;
   }

   //연결리스트에 노드가 존재할경우
   temp->llink = h->llink;   //삽입할노드의 llink를 헤더노드의 llink로 변경(기존마지막노드<-삽입노드)
   temp->rlink = h;      //삽입노드의 rlink 헤더노드로 변경(마지막 노드로 만들기위해서)
   h->llink->rlink = temp;   //기존마지막노드의 rlink 삽입노드로 변경
   h->llink =temp;         //헤더노드의 llink 삽입노드로 변경(마지막 노드가 됨)

   return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {   //마지막 노드를 삭제하는 함수
   if(h==NULL){      //할당받은 메모리가 없을 경우
      printf("the memory is not allocated\n");
      return 1;
   }
   if(h->rlink == h){   //연결리스트가 비어있을 경우
      printf("the linkedlist is empty\n");
      return 1;
   }

   listNode* lastnode = h->llink;   //lastnode는 삭제할노드, 삭제할 노드인 마지막 노드를 가리키도록함
   lastnode->llink->rlink = h;      //마지막노드의 이전노드에 rlink를 헤더노드로 변경한다.(마지막노드는 삭제해야하기에)
   h->llink = lastnode -> llink;   //헤더노드의 llink를 마지막노드의 llink로 바꾼다.(마지막 노드가 됨)

   free(lastnode);               //전부 변경 후 마지막 노드 삭제

   return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {   //연결리스트의 처음에 새 노드를 삽입하는 함수
   listNode *temp = (listNode*)malloc(sizeof(listNode));      //삽입할 노드
   temp->key = key, temp->llink = NULL, temp->rlink = NULL;   //필드값 할당

   if(h == NULL){      //만일 메모리를 할당받지않았다면
      printf("the memory is not allocated\n");
      return 1;
   }

   if(h->rlink == h){   //연결리스트가 비어있다면
      temp->rlink = h;   //삽입노드의 rlink를 헤더노드로 변경
      temp->llink = h;   //삽입노드의 llink를 헤더노드로 변경
      h->rlink = temp;   //헤더노드의 rlink와 llink를 삽입노드로 변경
      h->llink = temp;
      return 1;
   }
   //연결리스트에 노드들이 존재한다면
   temp->llink = h;      //삽입노드의 llink 헤더노드로 변경(삽입노드가 첫노드가 되기위한 작업)
   temp->rlink = h->rlink;   //삽입노드의 rlink 기존 첫노드로 변경
   h->rlink->llink = temp;   //기존 첫노드의 llink 삽입노드로 변경(삽입노드가 첫번째 노드가 되기위함)
   h->rlink = temp;      //헤더노드의 rlink 삽입노드로 변경(삽입노드가 첫번째 노드가 됨)

   return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {   //연결리스트의 첫노드를 삭제하는 함수
   if(h == NULL){      //헤더노드가 메모리를 할당받지 못했을 경우
      printf("the memory is not allocated\n");
      return 1;
   }
   if(h->rlink == h){   //연결리스트가 비어있을 경우
      printf("the linkedlist is empty\n");
      return 1;
   }

   listNode *first = h->rlink;   //삭제할 노드(첫번째노드)할당

   first->rlink->llink = h;   //첫노드(삭제할노드)의 다음노드의 llink를 헤더노드로 변경(다음노드가 첫번째 노드가됨)
   h->rlink = first->rlink;   //헤더노드의 rlink 첫노드의 다음노드로 변경(첫 노드는 삭제되기에)

   free(first);            //기존 첫번째 노드 삭제

   return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {   //연결리스트를 역순으로 배치하는 함수
   if(h == NULL){   //할당된 메모리가 없을 경우
      printf("the memory is not allocated\n");
      return 1;
   }
   if(h->rlink == h){   //연결리스트가 비어있을 경우
      printf("the linkedlist is empty\n");
      return 1;
   }

   listNode *node = h->rlink;      //node가 첫번째 노드를 가리키도록함
   listNode *trail = h;         //마지막 노드를 가리킬 포인터
   listNode *middle = h;         //중간 노드를 가리킬 포인터

   h->llink = h->rlink;         //역순으로 배치 전 헤더노드의 llink rlink로 변경(기존 첫노드를 가리킬 것이기에)
   while(node != h){            //리스트를 돌면서
      trail = middle;            //trail은 middle을 가리키도록함
      middle = node;            //middle은 node를 가리키도록함
      node = node->rlink;         //node는 다음 노드를 가리키도록함(trail-middle-node순)
      middle->rlink = trail;      //middle의 rlink가 trail을 가리키도록함
      middle->llink = node;      //middle의 llink또한 node를 가리키도록함(역순으로 배치하는 과정)
   }
   h->rlink = middle;   //역순으로 배치후 헤더노드의 rlink가 마지막노드(middle)을 가리키도록함
   

   return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {   //입력한 key값보다 큰 값을 갖는 노드 바로 앞에 삽입하는 함수
   if(h == NULL){   //메모리를 할당받지 못했을 경우
      printf("the memory is not allocated\n");
      return 1;
   }

   listNode *temp = (listNode*)malloc(sizeof(listNode));      //삽입할 노드
   temp->key = key, temp->llink = NULL, temp->rlink = NULL;   //필드값 할당
   listNode *node = h->rlink;      //현재 노드를 가리킬 포인터
   listNode *previous = NULL;      //이전 노드를 가리킬 포인터
   int count = 0;               //노드가 첫번째인지 확인하기 위한 변수

   if(h->rlink == h){      //리스트에 노드가 존재하지 않을 경우
      h->rlink = temp;   //삽입노드를 첫번째 노드로 만듦
      h->llink = temp;
      temp->llink = h;
      temp->rlink = h;
      return 1;
   }

   for(; node!=h; previous=node, node = node->rlink){   //연결리스트에 노드들이 존재한다면 key값 비교
      if(node->key >= key){            //입력한 key값보다 큰 값을 찾은 경우
         if(count == 0){               //만일 해당노드가 첫번째 노드였다면
            temp->llink = h;         //temp의 llink를 헤더노드로 변경
            temp->rlink = h->rlink;      //temp의 rlink를 h의 rlink로 변경(기존 첫번째 노드)
            h->rlink->llink = temp;      //기존 첫번째 노드의 llink를 삽입노드로 변경(첫번째 노드로 만드는 작업)
            h->rlink = temp;         //마지막으로 헤더노드의 rlink를 삽입노드로 변경하여 삽입노드를 첫번째 노드로 만듦
            return 1;
         }
         else{                     //해당노드가 첫번째 노드가 아닐 경우
            temp->rlink = node;         //삽입노드의 rlink를 찾은노드로 변경(찾은노드 앞에 삽입하기 위함)
            temp->llink = previous;      //삽입노드의 llink를 이전노드로 변경(현재 previous<-temp->node)
            previous->rlink = temp;      //이전노드의 rlink를 삽입노드로 변경(previous<->temp->node)
            node->llink = temp;         //찾은노드의 llink를 삽입노드로 변경(최종 previous<->temp<->node)
            return 1;
         }
      }
      count++;
   }

   //key값이 제일 큰경우
   insertLast(h, key);   //입력key값보다 큰 값을 갖는 노드를 찾지 못하여 리스트의 맨마지막에 삽입
   return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {   //연결리스트에서 key값을 갖는 노드를 삭제하는 함수
   if(h == NULL){   //할당된 메모리가 없을 경우
      printf("the memory is not allocated\n");
      return 1;
   }
   if(h->rlink == h){   //연결리스트가 비어있을 경우
      printf("the linkedlist is empty\n");
      return 1;
   }

   listNode *node = h->rlink;   //현재 노드를 가리킬 포인터
   listNode *previous = NULL;   //이전 노드를 가리킬 포인터
   int count = 0;            //찾은 노드가 첫번째노드인지 판단할 변수

   for(; node != h; previous = node, node = node->rlink){   //노드가 존재할경우 연결리스트를 돌면서 key값 비교
      if(key == node->key){   //같은 값을 갖는 노드를 찾았을 경우
		if(count == 0){      //해당노드가 첫번째 노드인 경우
			deleteFirst(h);   //첫번째 노드를 삭제하는 함수 호출
			return 1;
		}
		else if(node->rlink == h){   //마지막 노드인 경우
			deleteLast(h);         //마지막노드를 삭제하는 함수 호출
			return 1;
		}
		else{            //찾은 노드가 첫번째나 마지막이 아닐 경우
			previous->rlink = node->rlink;   //이전노드의 rlink를 찾은노드의 rlink로 변경(찾은노드를 삭제하기에)
			node->rlink->llink = previous;   //찾은노드의 다음노드의 llink를 이전노드로 변경
			free(node);                  //찾은노드 삭제
			return 1;
		}
      }
      count++;
   }

   printf("Nothing to find\n");   //입력값을 갖는 노드를 찾지 못했을 경우
   return 0;
}
