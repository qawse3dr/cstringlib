/**A String api for C that compiles to a lib
 *Author: Lawrence Milne .AKA. qawse3dr*/

/*#typedef struct String{
  char* data;
  long length;
}string_struct;
#typedef String string_struct* */

#include <stdlib.h>
#include <stdio.h>

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
    stringcatChar(subStr,charAt(string,i));
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
  for(int i = lower; i < string->length && !stringContainsChar("\n\t ",charAt(string,i)); i++){
    lower++;
  }
  //trim back
  for(int i = upper; i >= 0 && !stringContainsChar("\n\t ",charAt(string,i)); i--){
    upper--;
  }
  //copies data
  String trimmedString = subString(string,lower,upper);

  //frees old data
  free(string->data);
  //new length and data
  string->length = trimmmedString->length - lower - (string->length-upper);
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
    return "\0";
  }
  return string->data[index];
}
void setCharAt(String string,long index,char value){
  if(!string && index >= 0 && index <= string->length-1){
    fprintf(stderr,"setCharAt invalid input.\n");
    return;
  }
  return string->data[index] = value;
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
int countString(String string,String search);
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
  if(!string && !string->data &&{
    fprintf(stderr,"StringContainsChar invalid input.\n");
  }
  int contains = 0;
  for(int i = 0; i < string->length; i++){
    if(CharAt(string,i) == search){
      contains = 1;
      break;
    }
  }
  return contains;
}

/*contains as many string as your want to one string\
 *@param string the string being concated too
 *@param ... the strings being added to it*/
void stringcat(String string, ...){ //String

}
void stringcatC(String string, ...){ //char*
}
void stringcatChar(String string, ...){ //char

}
/*converts a file to a string returns void it it fails
 *@param fileName name of the file
 *@return the file as a string*/
String fileToString(String fileName){
  if(!fileName){
    return NULL;
  }
  String fileString = NULL;
  FILE* fp = fopen(fileName,"r")
  if(fp){
    fileString = createString("");
    char c;
    //copies to string
    while((c = getc(fp)) != '\0'){
      stringcatChar(fileString,c);
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
  if(!string && !suffix){
    fprintf(stderr,"stringEndsWith invalid input.\n");
    return 0;
  }

}
int stringEndsWithC(String string, char* sufix){

}

/*returns it a string starts with a sufix
 *@param string being searched
 *@param prefix the value being searched for*/
int stringStartsWith(String string, String prefix);
int stringStartsWith(String string, char* prefix);

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
  stringcatChar(string,value);
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
