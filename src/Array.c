/*
 *Lawrence Milne
 *1049930
 *March 26th 2020
 *Assignment 4
*/

/**dynamic Array api used to hold void*
  */

#include <stdlib.h>
#include "Array.h"


/**mallocs an array structure
 *@delete the delete function for deleteing the array
 *@return a pointer to an array structure*/
Array* createArray(void (*delete)(void*)){
  Array* array = malloc(sizeof(Array));
  array->delete = delete;
  array->data = NULL;
  array->length = 0;
  return array;
}

/**frees the array structure
 *@param Array the array to be freed
 */
void freeArray(Array* array){
  if(array){
    if(array->data){

      //frees data inside of array
      void* value;
      for(int i=0; i < array->length; i++){
        value = arrayGet(array,i);

        if(value){ //frees data with there free function
          array->delete(value);
        }
      }
      //free array list
      free(array->data);
    }
    //frees array structure
    free(array);
  }
}

/**pushes values on the the array stack
 *@param array the array the the value is being appened too
 *@param data the data being pushed on
 *@post if it fails array will be untouched*/
void arrayPush(Array* array, void* data){
  if(array){
    if(array->length){ //length is greater than 0
      array->data = realloc(array->data,sizeof(void*)*(array->length + 1));
      (array->data)[array->length] = data;
      ++(array->length);
    }else{ //malloc for new array length = 0;
      array->data = malloc(sizeof(void*));
      (array->data)[0] = data;
      ++(array->length);
    }
  }
}

/**gets a value from index i
 *@param Array the array the index is being accessed from
 *@param i the index the element is in
 *@return the value at the index NULL if it is out of bounds
*/
void* arrayGet(Array* array,int i){
  if(i > array->length-1){
    return NULL;
  }
  return (array->data)[i];
}


/**finds if a value is inside of an array
  *@param array the array being checked
  *@param key the key being searched for
  *@param compar a function that compars 2 functions
  *@return returns 1 if contains 0 if it doesnt
*/
int arrayContains(Array* array,void* key, int(*compar)(void*,void*)){
  if(array){
    for(int i = 0; i < array->length; i++){
      if(compar(key,arrayGet(array,i)) == 0){ //found
        return 1;
      }
    }
}//not found
  return 0;
}

/**generic free function that just deletes the pointer itself*/
void genericFree(void* value){
  free(value);
}

/**a function that doesnt do anything for freeing data*/
void emptyFree(void*a){}
/**uses qsort to sort the array
 *@param array to be sorted
 *@param compar used to compar values in the array*/
void arrayQsort(Array* array,int(*compar)(void*,void*)){
    qsort(array->data,array->length,sizeof(void*),(int(*)(const void*,const void*))compar);
}
