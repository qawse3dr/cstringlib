/**test units for String lib*/
#include "String.h"
#include <string.h>
#include <stdio.h>

void test(char* testDesc,int testResult){
  //keeps track of test number
  static int testNum = 0;
  static int pass = 0;
  static int fail = 0;
  testNum++;

  if(strcmp(testDesc,"Done") == 0){
    printf("Testing complete\n");
    printf("\n\nRESULT\n");
    printf("------\n");
    printf("\nTests Failed: %d\n",fail);
    printf("Tests Passed: %d\n",pass);
    return;
  }
  printf("Test %d (%s): ",testNum,testDesc);
  if(testResult){
    printf("PASS\n");
    pass++;
  } else{
    fail++;
    printf("\033[0;31m");
    printf("FAIL\n");
    printf("\033[0m");
  }
}
int main(){

  //test createString and setString with NULL
  printf("Create String test\n");
  printf("------------------\n\n");

  test("Creating string with NULL",!createString(NULL));
  test("freeString With NULL PASS if it doesn't crash",1);
  freeString(NULL);
  //test1 string creation
  String hello = createString("Hello World!");
  String bye = createString("bye");


  //one line tests
  test("Creating a string hello",strcmp(hello->data, "Hello World!") == 0 );
  printf("\n");

  printf("checking value for string\n");
  printf("-------------------------\n\n");

  test("charAt(hello,0)",'H' == charAt(hello,0));
  test("charAt(hello,-1)",'\0' == charAt(hello,-1));
  test("charAt(hello,100)",'\0' == charAt(hello,100));
  printf("\n");

  printf("Testing strcmp functions\n");
  printf("-----------------------\n\n");

  test("Checking value for getString",strcmp(hello->data,getString(hello)) == 0);
  test("Checking for correct Length",hello->length == 12);
  test("stringcmp(\"Hello World!\", \"bye\")",stringcmp(hello,bye));
  test("stringcmp(\"Hello World!\", \"Hello World!\"",stringcmp(hello,hello) == 0);
  test("stringcmp(NULL,NULL)",stringcmp(NULL,NULL));
  test("stringcmp(NULL,NULL)",stringcmp(hello,NULL));
  test("stringcmp(NULL,NULL)",stringcmp(NULL,bye));

  test("stringcmpC(\"Hello World!\", \"Hello World!\")",stringcmpC(hello,"Hello World!") == 0);
  test("stringcmpC(\"Hello World!\", \"bye\")",stringcmpC(hello,"bye"));
  test("stringcmpC(NULL,NULL)",stringcmpC(NULL,NULL));
  test("stringcmpC(NULL,NULL)",stringcmpC(hello,NULL));
  test("stringcmpC(NULL,NULL)",stringcmpC(NULL,"Hello"));
  printf("\n");


  printf("Test set fuctions\n");
  printf("-----------------\n\n");

  //test setCharAt
  setCharAt(hello,0,'B');
  test("setCharAt(hello,0,\'B\')",charAt(hello,0));

  //testing setString

  setString(hello,bye);
  test("changing value of hello to \"bye\" using SetString",stringcmp(hello,bye) == 0);
  test("Checking hellos length was changed to 3",hello->length == 3);

  setStringC(hello,"test");
  test("changing value of hello to \"test\" using SetString",stringcmpC(hello,"test") == 0);
  test("Checking hellos length was changed to 4",hello->length == 4);
  printf("\n");

  printf("Test for concat functions\n");
  printf("-------------------------\n\n");

  //testing concat function
  stringcat(1,hello,bye);
  test("concating bye to hello",stringcmpC(hello,"testbye") == 0);

  stringcat(2,hello,bye,bye);
  test("concating bye 2 times to hello",stringcmpC(hello,"testbyebyebye") == 0);

  stringcatC(1,bye,"hello");
  test("concating \"hello\" to bye",stringcmpC(bye,"byehello") == 0);

  stringcatC(2,bye,"hello","hello");
  test("concating \"hello\" 2 times to bye",stringcmpC(bye,"byehellohellohello") == 0);

  setStringC(bye,"hello");
  stringcatChar(5,bye,'h','e','l','l','o');
  test("concating chars \"hello\" to bye",stringcmpC(bye,"hellohello") == 0);
  //testing copy string
  freeString(bye);
  printf("\n");

  printf("Test starts with and ends with functions\n");
  printf("----------------------------------------\n\n");
  setStringC(hello,"hello");
  bye = copyString(hello);
  test("Checking copy string", stringcmp(bye,hello) == 0 && bye->data != hello->data);

  //testing starts with and ends with function
  test("starts with when equal",stringStartsWith(hello,bye));
  test("ends with when equal",stringStartsWith(hello,bye));
  test("char* starts with when equal",stringStartsWithC(hello,"hello"));
  test("char* ends with when equal",stringStartsWithC(hello,"hello"));

  setStringC(bye,"bye");
  test("starts with when not equal",!stringStartsWith(hello,bye));
  test("ends with when not equal",!stringStartsWith(hello,bye));
  test("char* starts with when not equal",!stringStartsWithC(bye,"hello"));
  test("char* ends with when not equal",!stringStartsWithC(bye,"hello"));

  setStringC(hello,"ye");
  test("ends with when end equal",stringEndsWith(bye,hello));
  test("char* ends with when end equal",stringEndsWithC(bye,"ye"));

  setStringC(hello,"by");
  test("starts with when start equal",stringStartsWith(bye,hello));
  test("char* starts with when start equal",stringStartsWithC(hello,"by"));

  //testing for null parameters
  test("starts with with null parameters",!stringStartsWith(hello,NULL));
  test("starts with with null parameters 2",!stringStartsWith(NULL,hello));
  test("starts with with null parameters 3",!stringStartsWith(NULL,NULL));

  test("char* starts with with null parameters",!stringStartsWithC(hello,NULL));
  test("char* starts with with null parameters 2",!stringStartsWithC(NULL,"hello"));
  test("char* starts with with null parameters 3",!stringStartsWithC(NULL,NULL));

  test("ends with with null parameters",!stringEndsWith(hello,NULL));
  test("ends with with null parameters 2",!stringEndsWith(NULL,hello));
  test("ends with with null parameters 3",!stringEndsWith(NULL,NULL));

  test("ends with with null parameters",!stringEndsWithC(hello,NULL));
  test("ends with with null parameters 2",!stringEndsWithC(NULL,"hello"));
  test("ends starts with with null parameters 3",!stringEndsWithC(NULL,NULL));
  printf("\n");

  printf("Test trim\n");
  printf("---------\n\n");
  setStringC(hello," \t\n test  \n\t\n ");
  trim(hello);

  test("test trim \"\\t\\n test  \\n\\t\\n \"",stringcmpC(hello,"test") == 0);
  test("strlength of trim test == 4",hello->length == 4);
  printf("\n");


  printf("String munipluation tests\n");
  printf("-------------------------\n\n");
  String fileName = createString("test/latin.txt");
  String fileString = fileToString(fileName);
  freeString(fileName);

  //reads in content from latin.txt
  FILE* fp = fopen("test/latin.txt","r");
  char fileBuffer[10000];

  int i;
  //work done in loop
  for(i = 0; (fileBuffer[i] = getc(fp)) != EOF; i++);
  fileBuffer[i] = '\0';
  fclose(fp);
  fileName = createString("/not/a/file/txt");
  test("test fileToString", stringcmpC(fileString,fileBuffer) == 0);
  test("test fileToString with null value",!fileToString(NULL));
  test("test fileToString with invalid file",!fileToString(fileName));
  freeString(fileName);

  printf("\n");

  printf("test convertion from types to string\n");
  printf("------------------------------------\n\n");

  //create data for convertion testing
  String stringChar = stringFromChar('a');
  String stringInt = stringFromInt(100);
  String stringFloat = stringFromFloat(10.222222,1);

  //tests for convertion
  test("test stringFromChar", stringcmpC(stringChar,"a") == 0);
  test("test stringFromInt", stringcmpC(stringInt,"100") == 0);
  test("test StringFromFloat", stringcmpC(stringFloat,"10.2") == 0);

  //free data from testing
  freeString(stringChar);
  freeString(stringInt);
  freeString(stringFloat);
  printf("\n");

  printf("test string search functions\n");
  printf("----------------------------\n\n");

  //uses string from stringFromFile
  String searchString = createString("ea");
  test("Tests string contains", stringContains(fileString,searchString));
  setStringC(searchString,"test");
  test("Tests string contains for string no in file", !stringContains(fileString,searchString));
  test("test 1 String contains invalid args nulls",stringContains(NULL,NULL) == 0);
  test("test 2 String contains invalid args nulls",stringContains(fileString,NULL) == 0);
  test("test 3 String contains invalid args nulls",stringContains(NULL,searchString) == 0);

  //tests stringContainsC
  test("Tests string containsC", stringContainsC(fileString,"ea"));
  test("Tests string contains for string no in fileC", !stringContainsC(fileString,"test"));
  test("test 1 String containsC invalid args nulls",stringContainsC(NULL,NULL) == 0);
  test("test 2 String containsC invalid args nulls",stringContainsC(fileString,NULL) == 0);
  test("test 3 String containsC invalid args nulls",stringContainsC(NULL,"test") == 0);

  //test countStrings
  setStringC(searchString,"ea");
  test("Tests string count for ea == 4",countString(fileString,searchString) == 4);
  setStringC(searchString,"test");
  test("Tests string count for test == 0",countString(fileString,searchString) == 0);
  test("test 1 String invalid args nulls",countString(NULL,NULL) == 0);
  test("test 2 String invalid args nulls",countString(fileString,NULL) == 0);
  test("test 3 String invalid args nulls",countString(NULL,searchString) == 0);

  //test countStringC
  setStringC(searchString,"ea");
  test("Tests string count for ea == 4",countStringC(fileString,"ea") == 4);
  setStringC(searchString,"test");
  test("Tests string count for test == 0",countStringC(fileString,"test") == 0);
  test("test 1 String invalid args nulls",countStringC(NULL,NULL) == 0);
  test("test 2 String invalid args nulls",countStringC(fileString,NULL) == 0);
  test("test 3 String invalid args nulls",countStringC(NULL,"string") == 0);

  String delimiter = createString("\n\t ");
  Array* array = splitToArray(fileString,delimiter);
  test("splitToArray ArrayLength", array->length == 98);
  test("splitToArray index 0",stringcmpC(arrayGet(array,0),"Lorem") == 0);
  test("splitToArray index 97",stringcmpC(arrayGet(array,97),"Persius") == 0);
  test("splitToArray invalid args 1",!splitToArray(NULL,NULL));
  test("splitToArray invalid args 2",!splitToArray(fileString,NULL));
  test("splitToArray invalid args 3",!splitToArray(NULL,fileString));
  freeArray(array);

  array = splitToArrayC(fileString,"\n\t ");
  test("splitToArrayC ArrayLength", array->length == 98);
  test("splitToArrayC index 0",stringcmpC(arrayGet(array,0),"Lorem") == 0);
  test("splitToArrayC index 97",stringcmpC(arrayGet(array,97),"Persius") == 0);
  test("splitToArrayC invalid args 1",!splitToArrayC(NULL,NULL));
  test("splitToArrayC invalid args 2",!splitToArrayC(fileString,NULL));
  test("splitToArrayC invalid args 3",!splitToArrayC(NULL,"string"));
  freeArray(array);

  //split to list
  List* list = splitToList(fileString,delimiter);
  test("SplitToList length",list->length == 98);
  test("SplitToList head",stringcmpC(getData(getHead(list)),"Lorem") == 0);
  test("SplitToList tail",stringcmpC(getData(getTail(list)),"Persius") == 0);
  test("SplitToList invalid args 1",!splitToList(NULL,NULL));
  test("SplitToList invalid args 2",!splitToList(fileString,NULL));
  test("SplitToList invalid args 3",!splitToList(NULL,delimiter));
  freeList(list);

  //split to listC
  list = splitToListC(fileString,"\n\t ");
  test("SplitToList length",list->length == 98);
  test("SplitToList head",stringcmpC(getData(getHead(list)),"Lorem") == 0);
  test("SplitToList tail",stringcmpC(getData(getTail(list)),"Persius") == 0);
  test("SplitToList invalid args 1",!splitToListC(NULL,NULL));
  test("SplitToList invalid args 2",!splitToListC(fileString,NULL));
  test("SplitToList invalid args 3",!splitToListC(NULL,"string"));
  freeList(list);

  //test replace
  setStringC(fileString,"This is a test string a apple is nice");
  setStringC(hello,"apple");
  setStringC(bye,"potato");
  stringReplace(fileString,hello,bye);
  test("test stringReplace",stringcmpC(fileString,"This is a test string a potato is nice") == 0);
  test("test stringReplace strlength", fileString->length == 38);
  test("test stringRepalce with invalid args if it doesn't crash it passes",1);
  stringReplace(NULL,NULL,NULL);
  stringReplace(fileString,NULL,NULL);
  stringReplace(NULL,hello,NULL);
  stringReplace(NULL,NULL,bye);
  stringReplace(fileString,hello,NULL);
  stringReplace(fileString,NULL,bye);
  stringReplace(NULL,hello,bye);

  //test replaceC
  setStringC(fileString,"This is a test string a apple is nice");
  stringReplaceC(fileString,"a","");
  test("test stringReplaceC",stringcmpC(fileString,"This is  test string  pple is nice") == 0);
  test("test stringReplaceC strlength", fileString->length == 34);

  test("test stringReplaceC with invalid args if it doesn't crash it passes",1);
  stringReplaceC(NULL,NULL,NULL);
  stringReplaceC(fileString,NULL,NULL);
  stringReplaceC(NULL,"hello",NULL);
  stringReplaceC(NULL,NULL,"bye");
  stringReplaceC(fileString,"hello",NULL);
  stringReplaceC(fileString,NULL,"bye");
  stringReplaceC(NULL,"hello","bye");


  printf("\nfreeing Strings\n\n");
  freeString(delimiter);

  freeString(searchString);
  freeString(hello);
  freeString(bye);
  freeString(fileString);


  test("Done",1);
}
