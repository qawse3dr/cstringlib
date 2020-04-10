/**A String api for C that compiles to a lib
 *Author: Lawrence Milne .AKA. qawse3dr*/

/*#typedef struct String{
  char* data;
  long length;
}string_struct;
#typedef String string_struct* */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "String.h"

/**These are used for string search of boyerMoore
 *static as they should not be used by the user*/
/**Creates a shift table for a given pattern
 *@param key the given pattern in which the table will be created from
 *@return the created table*/
static Array* createBadShift(String key){
  //sets all the letters to the length of key
  //then itterate though changing all the values based on ascii value
  Array* table = createArray();
  int* value;
  int keyLength = key->length;
  for(int i = 0; i < 128; i++){
    value = malloc(sizeof(int));
    *value = keyLength;
    arrayPush(table,value);
  }

  //sets new value based on ascii
  for(int i = 0; i < keyLength-1 ;i++){
    *((int*)arrayGet(table,charAt(key,i))) = keyLength -i -1;
  }

  return table;
}
/**is a strcmp that also stop checking after the second string ends
  *@param string the string being searched
  *@param key the string being cmpared
  *@return int 0 if true 1 if false*/
static int searchString(char* string,char* key){
    int keyLength = strlen(key);
    for(int i=0; i < keyLength; i++){
      if(string[i] != key[i]){
        return 1;
      }
    }
    return 0;
}
/**Max function*/
static int max(int x, int y){
    return (x > y) ? x : y;
}
/**creates a goodshift tabel for the boyer Moore algo
 *@param key the string that the function will be based off of
 *@return the table*/
static Array* createGoodShift(String key){
    int keyLength = key->length;

    //holds the current suffix
    String suffix = createString("");
    //array that holds the shift table
    Array* table = createArray();

    //holds the values that go into the array
    //array starts at index 1. so adding a dummy var to fill inux 0;
    int* value = malloc(sizeof(int));
    *value = keyLength;
    arrayPush(table,value);

    //finds shift value for k lengths
    for(int i = 0; i < keyLength-1; i++){
        value = malloc(sizeof(int));
        *value = *(int*)arrayGet(table,i);
        //gets suffix
        setStringC(suffix,&(getString(key)[keyLength -  i-1]));

        //checks if a match is found would custom strcmp
        for(int j = 0; j < suffix->length; j++){
          if(searchString(getString(key),&getString(suffix)[suffix->length-1-j]) == 0){
            *value = keyLength - j -1;
          }
        }
        for(int j = 0; j < keyLength-suffix->length; j++ ){
            if(searchString(&(getString(key)[j]),getString(suffix)) == 0){ // match
              *value = keyLength - j-suffix->length;
            }
        }
        arrayPush(table,value);
    }
    freeString(suffix);
    return table;
}

/*Creates a string from a char*
 *@param str the string to be turned into the String struct*
 *@return String the newly malloced string2*/
String createString(const char* str){

  //create string
  String string = malloc(sizeof(string_struct));
  string->length = strlen(str);
  string->data = malloc(sizeof(char)*(string->length+1));
  strcpy(string->data,str);

  return string;
}

/*Frees the string
 *@param string the string to be freed*/
void freeString(String string){
  free(string->data);
  free(string);
}

/*Frees the container without freeing the string content
 *@param string the string container to be freed*/
void freeStringContainer(String string){
  free(string);
}

/*gets the string data
 *@param string
 *@return char* the strings data*/
char* getString(String string){
  return string->data;
}

/*sets the new value of a string
 *@param string the current string
 *@param what the value of the new string is*/
void setString(String string, String new){
  string->length = new->length;
  string->data = realloc(string->data,new->length+1);
  strcpy(string->data,new->data);
}
void setStringC(String string, char* new){
  string->length = strlen(new);
  string->data = realloc(string->data,string->length+1);
  strcpy(string->data,new);
}
/*splits a string by a delimiter or mutiple delimiter
 *@param string the string that will be split
 *@param delimiter the characters that will be split by
 *@return An Array of the string*/
Array* splitToArray(String string, String delimiter);
Array* splitToArrayC(String string, char* delimiter);

/*splits a string by a delimiter or mutiple delimiter
 *@param string the string that will be split
 *@param delimiter the characters that will be split by
 *@return A list of the string*/
List* splitToList(String string, String delimiter);
List* splitToListC(String string, char* delimiter);

/*copys a substring from a string
 *@param string the string that will be copied from
 *@param lower the lower bound
 *@param upper the upper bound
 *@return the sub string[lower to upper]*/
String subString(const String string, long lower, long upper){
  //invalid input
  if(!string || lower < 0 || upper > string->length-1 || upper < lower){
    return NULL;
  }

  //creates blank String
  String subStr = createString("");

  //copies string from lower to upper
  for(int i = lower; i <= upper; i++){
    stringcatChar(1,subStr,charAt(string,i));
  }

  return subStr;
}

/*copy a string
 *@param string the string to be copied
 *@return the copy of the string*/
String copyString(String string){
  //a wrapper for substring
  return subString(string,0,string->length-1);
}

/*removes all whiteSpaces newlines and tabs from both ends
 *@param string to be edited*/
void trim(String string){
  //invalid input
  if(!string || !string->data){
    fprintf(stderr,"trim invalid input.\n");
    return;
  }

  //the lower and upper bound of the trimmed string
  int lower = 0;
  int upper = string->length;
  //trim front
  //todo fix memleak
  String whiteSpace = createString("\n\t ");
  for(int i = lower; i < string->length && !stringContainsChar(whiteSpace,charAt(string,i)); i++){
    lower++;
  }
  //trim back
  for(int i = upper; i >= 0 && !stringContainsChar(whiteSpace,charAt(string,i)); i--){
    upper--;
  }
  //copies data
  String trimmedString = subString(string,lower,upper);

  freeString(whiteSpace);
  //frees old data
  free(string->data);
  //new length and data
  string->length = trimmedString->length - lower - (string->length-upper);
  string->data = trimmedString->data;
}

/*gets the character at an index index.
 *@param string the string being indexed
 *@param index the index of the string char will be gotten from
 *@return char the character at string[index]
 */
char charAt(String string, long index){
  if(!string && index >= 0 && index <= string->length-1){
    fprintf(stderr,"charAt invalid input.\n");
    return '\0';
  }
  return string->data[index];
}
void setCharAt(String string,long index,char value){
  if(!string && index >= 0 && index <= string->length-1){
    fprintf(stderr,"setCharAt invalid input.\n");
    return;
  }
  string->data[index] = value;
}
/*String cmp between string structs
 *@param string1 first string to be checked
 *@param string2 second string to be checked against string1
 *@return int the comparation*/
int stringcmp(String string1, String string2){
  if(!string1 || !string2) {
    fprintf(stderr,"stringcmp invalid input.\n");
    return 0;
  }
  return strcmp(string1->data,string2->data);
}
int stringcmpC(String string1, char* string2){
  if(!string1 || !string2) {
    fprintf(stderr,"stringcmp invalid input.\n");
    return 0;
  }
  return strcmp(string1->data,string2);
}

/*Counts how many times a string occurs in another string
 *uses boyer-moore
 *@param string the string being searched
 *@param search the string being searched for
 *@return how many instances there is
*/
int countString(String string,String search){
  //takes the key and creates the shift table
  Array* badTable = createBadShift(search);
  Array* goodTable = createGoodShift(search);

  //boyerMooreAlgo
  int found = 0;
  //find lengths out here so it isnt calculated ever itterations
  int keyLength = search->length;
  int stringLength = string->length;

  //loop var
  int k=0;
  //how much it should get shifted over
  int shiftAmount;

  for(int i = keyLength-1; i < stringLength; i+=shiftAmount){

    k = 0;
    //checks for matching index
    while(k < keyLength && charAt(search,keyLength-k-1) == charAt(string,i-k)) k++;
    if(k == keyLength) {
      found++;
      shiftAmount = keyLength;
    }else if( k == 0){

        shiftAmount = *(int*)arrayGet(badTable,(int)charAt(string,i));
    } else{

        shiftAmount = max(max(*(int*)arrayGet(badTable,(int)charAt(string,i)) - k,1)
                                          ,*(int*)arrayGet(goodTable,k));
    }
  }

  //free tables
  freeArray(badTable,genericFree);
  freeArray(goodTable,genericFree);
  return found;
}
int countStringC(String string, char* search){
  if(!string && !string->data && !search){
    fprintf(stderr,"countStringC invalid input.\n");
  }
  //a wraper for stringContains
  String searchString = createString(search);
  int contains = countString(string,searchString);
  freeString(searchString);
  return contains;
}

/*checks if a strings contains a value using boyer-moore
 *@param string that is being searched
 *@param search what is being searched for
 *@return 1 if it contains the string 0 if it doesnt
 */
int stringContains(String string,String search){
  //takes the key and creates the shift table
  Array* badTable = createBadShift(search);
  Array* goodTable = createGoodShift(search);

  //boyerMooreAlgo
  int found = 0;
  //find lengths out here so it isnt calculated ever itterations
  int keyLength = search->length;
  int stringLength = string->length;

  //loop var
  int k=0;
  //how much it should get shifted over
  int shiftAmount;

  for(int i = keyLength-1; i < stringLength; i+=shiftAmount){

    k = 0;
    //checks for matching index
    while(k < keyLength && charAt(search,keyLength-k-1) == charAt(string,i-k)) k++;
    if(k == keyLength) {
      found++;
      break;
      shiftAmount = keyLength;
    }else if( k == 0){

        shiftAmount = *(int*)arrayGet(badTable,(int)charAt(string,i));
    } else{

        shiftAmount = max(max(*(int*)arrayGet(badTable,(int)charAt(string,i)) - k,1)
                                          ,*(int*)arrayGet(goodTable,k));
    }
  }

  //free tables
  freeArray(badTable,genericFree);
  freeArray(goodTable,genericFree);
  return found;
}
int stringContainsC(String string, char* search){
  if(!string && !string->data && !search){
    fprintf(stderr,"StringContainsC invalid input.\n");
  }
  //a wraper for stringContains
  String searchString = createString(search);
  int contains = stringContains(string,searchString);
  freeString(searchString);
  return contains;
}
int stringContainsChar(String string,char search){
  if(!string || !string->data){
    fprintf(stderr,"StringContainsChar invalid input.\n");
  }
  int contains = 0;
  for(int i = 0; i < string->length; i++){
    if(charAt(string,i) == search){
      contains = 1;
      break;
    }
  }
  return contains;
}

/*contains as many string as your want to one string
 *@param strCount how many strings are being concated must be greater than 2
 *@param string the string being concated too
 *@param ... the strings being added to it*/
void stringcat(int strCount, String string, String stringArgs, ...){ //String
  if(!string || strCount < 1){
    return;
  }

  //appends each string
  va_list ap;
  va_start(ap,stringArgs);
  for(int i = 0; i < strCount; i++){
    //grabs string from function
    stringArgs = va_arg(ap, String);

    //alloc enough space for new string length
    string->data = realloc(string->data,string->length + stringArgs->length + 1);

    //want to use j outside of the loop for placing null terminator
    int j;
    for(j = string->length; j < string->length + stringArgs->length; j++){
      string->data[j] = stringArgs->data[j - string->length];
    }
    string->data[j] = '\0';
    string->length += stringArgs->length;
  }
  va_end(ap);

}
void stringcatC(int strCount, String string, char* stringArgs, ...){ //char*
  if(!string || strCount < 1){
    return;
  }
  //the new length of the string
  long stringArgsLength;

  //appends each string
  va_list ap;
  va_start(ap,stringArgs);
  for(int i = 0; i < strCount; i++){
    //grabs string from function
    stringArgs = va_arg(ap, char *);
    stringArgsLength = strlen(stringArgs);

    //alloc enough space for new string length
    string->data = realloc(string->data,string->length + stringArgsLength + 1);

    //want to use j outside of the loop for placing null terminator
    int j;
    for(j = string->length; j < string->length + stringArgsLength; j++){
      string->data[j] = stringArgs[j - string->length];
    }
    string->data[j] = '\0';
    string->length += stringArgsLength;
  }
  va_end(ap);
}
void stringcatChar(int charCount, String string, char charArgs, ...){ //char
  if(!string || charCount < 1){
    return;
  }
  //appends each string
  va_list ap;
  va_start(ap,charArgs);

  //alloc enough space for new string length
  string->data = realloc(string->data,string->length + charCount + 1);

  for(int i = 0; i < charCount; i++){

    //grabs char from function
    charArgs = va_arg(ap, int);

    //add char
    string->data[string->length] = charArgs;
    string->data[++string->length] = '\0';
  }
  va_end(ap);
}
/*converts a file to a string returns void it it fails
 *@param fileName name of the file
 *@return the file as a string*/
String fileToString(String fileName){
  if(!fileName){
    return NULL;
  }
  String fileString = NULL;
  FILE* fp = fopen(getString(fileName),"r");
  if(fp){
    fileString = createString("");
    char c;
    //copies to string
    while((c = getc(fp)) != '\0'){
      stringcatChar(1,fileString,c);
    }
  }
  return fileString;
}

/*gets the length of a string
 *@param string the string length will be retrived from
 *@return length of string
long getStringLength(String string);

/*returns it a string ends with a sufix
 *@param string being searched
 *@param suffix the value being searched for*/
int stringEndsWith(String string, String sufix){
  if(!string || !sufix || string->length < sufix->length){
    fprintf(stderr,"stringEndsWith invalid input.\n");
    return 0;
  }
  //assume true till a contradiction is found
  int endsWith = 1;
  for(int i = 0; i > sufix->length; i--){
    if(charAt(string,string->length-1-i) != charAt(sufix,sufix->length-1-i)){
      endsWith = 0;
      break;
    }
  }
  return endsWith;
}
int stringEndsWithC(String string, char* sufix){
  //a wraper for stringContains
  String searchString = createString(sufix);
  int endsWith = stringEndsWith(string,searchString);
  freeString(searchString);
  return endsWith;
}

//TODO convert to strings
/*returns it a string starts with a sufix
 *@param string being searched
 *@param prefix the value being searched for*/
int stringStartsWith(String string, String prefix);
int stringStartsWithC(String string, char* prefix);

/*replaces a character with a new character
 *@param string hhaving characters replaced
 *@param current the value being searched for
 *@param new the new value
 *@return how many have gotten replaced*/
int stringReplace(String string, char current, char new){
  if(!string){
    fprintf(stderr,"stringReplace invlaid input\n");
    return 0;
  }
}

/*converstion between types
 *@param value the value to be converted
 *@return the string null if it failed*/
String stringFromChar(char value){
  String string = createString("");
  stringcatChar(1,string,value);
  return string;
}
String stringFromInt(int value){
  char buffer[1000];
  sprintf(buffer,"%d",value);

  return createString(buffer);
}
String stringFromFloat(float value, int decimals){
  char buffer[1000];
  sprintf(buffer,"%.*f",decimals,value);

  return createString(buffer);
}
