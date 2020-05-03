/*
 *Lawrence Milne
 *1049930
 *March 26th 2020
 *Assignment 4
*/

/**dynamic Array api used to hold void*
  */
/*
struct List;
//stores data (a node to a list struct)
typedef struct Node_Struct{
  void* data;
  struct Node_Struct* next;
  struct Node_Struct* prev;
  struct List* parent;
}Node;

//a structure to hold a list
typedef struct List_Struct{
  Node* head;
  Node* tail;
  int length;
}List;
*/

#include "LinkedList.h"
#include <stdlib.h>
/**Creates a list struct and returns it must be freed with freeList
 *@param deleteFunction a function used to free nodes
 *@return List* the list that is created
 *@post must be freed with freeList
*/
List* createList(void (*deleteFunction)(void*)){
  List* list = malloc(sizeof(List));
  list->length = 0;
  list->head = NULL;
  list->tail = NULL;
  list->delete = deleteFunction;
  return list;
}

/**Creates a blank node shouldnt be done by user
  *@return a malloced node
  */
Node* createNode(List* parent){
  Node* node = malloc(sizeof(Node));
  node->parent = parent;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

/**gets the head of the current list if it fails or doesnt have a\
  *head returns NULL
 *@param list the list head is being retrived from
 *@return the head node*/
Node* getHead(List* list){
  Node* head = NULL;
  if(list){
    head = list->head;
  }
  return head;
}

/**gets the tail of a list
 *@param list the list tail will be retreived from
 *@return the tail of the list
*/
Node* getTail(List* list){

  return list->tail;
}

/**gets a node from index i returns NULL if its out of index
 *@param List the element is in
 *@param i index of the element
 *@return the node at index i
 *@post to delete this node use deleteNode and it will be removed from the list
 *@post does not need to be freed will be freed when list is freed
 */
Node* getNode(List* list,int i){
  Node* cur = NULL;
  if(list && i >=0 && i < list->length){
    cur = getHead(list);
    for(int j = 1; j < i && cur; j++){
      cur = getNextNode(cur);
    }
  }
  return cur;
}

/**gets the next from node cur.
 *@param cur the current node
 *@return the next node*/
Node* getNextNode(Node* cur){
  Node* next = NULL;
  if(cur){
    next = cur->next;
  }
  return next;
}

/**gets prev node from cur node
 *@param cur the current node
 *@return the node one behind cur in the list
 */
Node* getPrevNode(Node* cur){
  Node* prev = NULL;
  if(cur){
    prev = cur->prev;
  }
  return prev;

}

/**gets the data from a node
 *@param node the node data is stored in
 *@return the data inside of node
 *@post dont free to delete use deleteNode*/
void* getData(Node* node){
  void* data = NULL;
  if(node){
    data = node->data;
  }
  return data;
}

/**frees the list
 *@param list to be freed
  */
void freeList(List* list){
  if(list){
    //frees all the nodes in the list
    while(list->head != NULL) deleteNode(list->head);
    //frees list Struct
    free(list);
  }
}

/**deletes a node from a list
  @pre must have a parent (if parent doesnt exist nothing happens and node isnt deleted).
  @param node the node to be delted*/
void deleteNode(Node* node){
  Node* prev = getPrevNode(node);
  Node* next = getNextNode(node);
  List* parent = getParent(node);
  if(node && parent){
    //linked prev to next if it exists
    if(prev){
      prev->next = next;
    }else{ //must be head
      parent->head = next;
    }
    //linkes next to prev if it exists
    if(next){
      next->prev = prev;
    } else{
      //must be  the tail
      parent->tail = prev;
    }
    //frees node
    parent->delete(node->data);
    free(node);

    //list scrinks by one
    parent->length--;
    if(parent->length == 0){
      parent->head = NULL;
      parent->tail = NULL;
    }
  }
}

/**removes a node from a list without deleting
  *the data
  @param node the node to be removed
  @return returns the data from the data being removed
  */
void* removeNode(Node* node){
  Node* prev = getPrevNode(node);
  Node* next = getNextNode(node);
  List* parent = getParent(node);
  void* data = NULL;
  if(node && parent){
    //linked prev to next if it exists
    if(prev){
      prev->next = next;
    }else{ //must be head
      parent->head = next;
    }
    //linkes next to prev if it exists
    if(next){
      next->prev = prev;
    } else{
      //must be  the tail
      parent->tail = prev;
    }
    //frees node
    data = node->data;
    free(node);

    //list scrinks by one
    parent->length--;
    if(parent->length == 0){
      parent->head = NULL;
    }
  }
  return data;
}

/**inserts a value at the front
 *@param list the list being added to
 *@param data the data being added
 *@post if it fails list will be untouched*/
void insertFront(List* list, void* data){
  if(list){
    //list grows by one
    list->length++;

    //creates new node and set it to the new head
    Node* node = createNode(list);
    node->next = list->head;
    node->data = data;
    list->head = node;

    //checks if its the tail
    if(!node->next){
      list->tail = node;
    }
  }
}

/**inserts a value at the Back
 *@param list the list being added to
 *@param data the data being added
 *@post if it fails list will be untouched*/
void insertBack(List* list, void* data){
  if(list && getListLength(list) >= 0){
    //list grows by one
    list->length++;
    //list already has a head
    if(getListLength(list) != 1){
      Node* prev = list->tail;
      //creates new node and set it to the new head
      Node* node = createNode(list);
      node->prev = prev;
      prev->next = node;
      node->data = data;
      node->next = NULL;
      list->tail = node;

    } else{//new head
      Node* node = createNode(list);
      node->data = data;
      list->head = node;
      list->tail = node;
    }

  }
}

/**inserts into a sorted List
 *@param list the list data will be inserted into
 *@param data what will be inserted into the list
 *@param compar whats used to compar elements*/
void insertSorted(List* list,void* data,int(*compar)(void*,void*)){
    Node* cur = NULL;
    if(list){
        //added to the length
        list->length++;
        Node* new = createNode(list);
        new->data = data;
        cur = getHead(list);
        //checks if the list is empty
        if(!cur){
            list->head = new;
            return;
        }
        //finds the element less then it than inserts
        while(cur){
          if(compar(data,getData(cur)) < 0){
              //inserts here
              new->prev = getPrevNode(cur);
              if(!new->prev) list->head = new;
              else new->prev->next = new;
              new->next = cur;
              cur->prev = new;
              break;
          }
          //doesnt have a next node add it to the end
          if(!getNextNode(cur)){
              new->prev = cur;
              new->next = NULL;
              cur->next = new;
              list->tail = new;
              break;
          }
          //moves over one in the list
          cur = getNextNode(cur);
        }
    }

}

/**gets the length of the list
 *@param list length is being accessed from
 *@return int the length of the list*/
int getListLength(List* list){
  int length = 0;
  if(list){
    length = list->length;
  }
  return length;
}

/**gets the parent of a node
 *@param a node
 *@return the nodes parent*/
List* getParent(Node* node){
  List* parent = NULL;
  if(node){
    parent = node->parent;
  }
  return parent;
}

/**deletes the list without deleting any of the  data inside
 *@param List to be deleted.
*/
void deleteList(List* list){
  if(list){
    //removes all the nodes in the list without deleting data
    while(list->head != NULL) removeNode(list->head);
    //frees list Struct
    free(list);
  }
}
