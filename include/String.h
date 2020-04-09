/**A String api for C that compiles to a lib
 *Author: Lawrence Milne .AKA. qawse3dr*/

#include <stdarg.h>
#include "Array.h"
#include "LinkedList.h"

typedef struct String{
  char* data;
  long length;
}string_struct;

typedef string_struct* String;

/*Creates a string from a char*
 *@param str the string to be turned into the String struct*
 *@return String the newly malloced string2*/
String createString(const char* str);

/*Frees the string
 *@param string the string to be freed*/
void freeString(String string);

/*Frees the container without freeing the string content
 *@param string the string container to be freed*/
void freeStringContainer(String string);

/*gets the string data
 *@param string
 *@return char* the strings data*/
char* getString(String string);

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
String subString(const String string, long lower, long upper);

/*copy a string
 *@param string the string to be copied
 *@return the copy of the string*/
String copyString(String string);

/*removes all whiteSpaces newlines and tabs from both ends
 *@param string to be edited*/
void trim(String string);

/*gets the character at an index index.
 *@param string the string being indexed
 *@param index the index of the string char will be gotten from
 *@return char the character at string[index]
 */
char charAt(String string, long index);
void setCharAt(String string,long index, char value);

/*String cmp between string structs
 *@param string1 first string to be checked
 *@param string2 second string to be checked against string1
 *@return int the comparation*/
int stringcmp(String string1, String string2);
int stringcmpC(String string1, char* string2);

/*Counts how many times a string occurs in another string
 *uses boyer-moore
 *@param string the string being searched
 *@param search the string being searched for
 *@return how many instances there is
*/
int countString(String string,String search);
int countStringC(String string, char* search);

/*checks if a strings contains a value using boyer-moore
 *@param string that is being searched
 *@param search what is being searched for
 *@return 1 if it contains the string 0 if it doesnt
 */
int stringContains(String string,String search);
int stringContainsC(String string, char* search);
int stringContainsChar(String string,char search);

/*contains as many string as your want to one string\
 *@param how many strings are being concated
 *@param string the string being concated too
 *@param ... the strings being added to it
 */
void stringcat(int strCount, String string, String stringArgs, ...); //String
void stringcatC(int strCount, String string, char* stringArgs, ...); //char*
void stringcatChar(int strCount, String string, char charArgs, ...); //char

/*converts a file to a string returns void it it fails
 *@param fileName name of the file
 *@return the file as a string*/
String fileToString(String fileName);

/*gets the length of a string
 *@param string the string length will be retrived from
 *@return length of string
long getStringLength(String string);

/*returns it a string ends with a sufix
 *@param string being searched
 *@param suffix the value being searched for*/
int stringEndsWith(String string, String sufix);
int stringEndsWithC(String string, char* sufix);

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
int stringReplace(String string, char current, char new);

/*converstion between types
 *@param value the value to be converted
 *@return the string null if it failed*/
String stringFromChar(char value);
String stringFromInt(int value);
String stringFromFloat(float value, int decimals);
