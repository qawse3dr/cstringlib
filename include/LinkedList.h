/*
 *Lawrence Milne
 *1049930
 *March 26th 2020
 *Assignment 4
*/

/**dynamic Array api used to hold void*
  */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
struct List_Struct;
//stores data (a node to a list struct)
typedef struct Node_Struct{
  void* data;
  struct Node_Struct* next;
  struct Node_Struct* prev;
  struct List_Struct* parent;
}Node;

//a structure to hold a list
typedef struct List_Struct{
  Node* head;
  Node* tail;
  int length;
  void (*delete)(void*);
}List;


/**Creates a list struct and returns it must be freed with freeList
 *@param deleteFunction a function used to free nodes
 *@return List* the list that is created
 *@post must be freed with freeList
*/
List* createList(void (*deleteFunction)(void*));

/**Creates a blank node shouldnt be done by user
  *@parent the nodes parent NULL if it doens't have one
  *@return a malloced node
  */
Node* createNode(List* parent);

/**gets the head of the current list if it fails or doesnt have a\
  *head returns NULL
 *@param list the list head is being retrived from
 *@return the head node*/
Node* getHead(List* list);

/**gets the tail of a list
 *@param list the list tail will be retreived from
 *@return the tail of the list
*/
Node* getTail(List* list);


/**gets a node from index i returns NULL if its out of index
 *@param List the element is in
 *@param i index of the element
 *@return the node at index i
 *@post to delete this node use deleteNode and it will be removed from the list
 *@post does not need to be freed will be freed when list is freed
 */
Node* getNode(List* list,int i);

/**gets the next from node cur.
 *@param cur the current node
 *@return the next node*/
Node* getNextNode(Node* cur);

/**gets prev node from cur node
 *@param cur the current node
 *@return the node one behind cur in the list
 */
Node* getPrevNode(Node* cur);

/**gets the data from a node
 *@param node the node data is stored in
 *@return the data inside of node
 *@post dont free to delete use deleteNode*/
void* getData(Node* node);

/**frees the list
 *@param list to be freed
  */
void freeList(List* list);

/**deletes a node from a list
  @pre must have a parent
  @param node the node to be delted*/
void deleteNode(Node* node);

/**removes a node from a list without deleting
  *the data
  @param node the node to be removed
  @return returns the data from the data being removed
  */
void* removeNode(Node* node);

/**inserts a value at the front
 *@param list the list being added to
 *@param data the data being added
 *@post if it fails list will be untouched*/
void insertFront(List* list, void* data);

/**inserts a value at the Back
 *@param list the list being added to
 *@param data the data being added
 *@post if it fails list will be untouched*/
void insertBack(List* list, void* data);

/**inserts into a sorted List
 *@param list the list data will be inserted into
 *@param data what will be inserted into the list
 *@param compar whats used to compar elements*/
void insertSorted(List* list,void* data,int(*compar)(void*,void*));
/**gets the length of the list
 *@param list length is being accessed from
 *@return int the length of the list*/
int getListLength(List* list);



/**gets the parent of a node
 *@param a node
 *@return the nodes parent*/
List* getParent(Node* node);

/**deletes the list without deleting any of the  data inside
 *@param List to be deleted.
*/
void deleteList(List* list);
#endif
