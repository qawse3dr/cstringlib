/*
 *Lawrence Milne
 *1049930
 *March 26th 2020
 *Assignment 4
*/


/**dynamic Array api used to hold void*
  */
#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array_Struct{
  void** data;
  int length;
  void (*delete)(void*);
}Array;

/**mallocs an array structure
 *@return a pointer to an array structure*/
Array* createArray(void (*delete)(void*));

/**frees the array structure
 *@param Array the array to be freed
 */
void freeArray(Array* array);

/**pushes values on the the array stack
 *@param array the array the the value is being appened too
 *@param data the data being pushed on*/
void arrayPush(Array* array, void* data);

/**gets a value from index i
 *@param Array the array the index is being accessed from
 *@param i the index the element is in
 *@return the value at the index NULL if it is out of bounds
*/
void* arrayGet(Array* array,int i);

/**finds if a value is inside of an array
  *@param array the array being checked
  *@param key the key being searched for
  *@param compar a function that compars 2 functions
  *@return returns 1 if contains 0 if it doesnt
*/
int arrayContains(Array* array,void* key, int(*compar)(void*,void*));

/**generic free function that just deletes the pointer itself*/
void genericFree(void*);

/**a function that doesnt do anything for freeing data*/
void emptyFree(void*);
/**uses qsort to sort the array
 *@param array to be sorted
 *@param compar used to compar values in the array*/
void arrayQsort(Array* array,int(*compar)(void*,void*));
#endif
