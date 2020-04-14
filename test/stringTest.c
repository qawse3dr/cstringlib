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
  //test1 string creation
  String hello = createString("Hello World!");
  String bye = createString("bye");

  //one line tests
  test("Creating a string hello",strcmp(hello->data, "Hello World!") == 0 );
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

  test("charAt(hello,0)",'H' == charAt(hello,0));
  test("charAt(hello,-1)",'\0' == charAt(hello,-1));
  test("charAt(hello,100)",'\0' == charAt(hello,100));

  //test setCharAt
  setCharAt(hello,0,'B');
  test("setCharAt(hello,0,\'B\')",charAt(hello,0));

  //testing setString

  setString(hello,bye);
  test("changing value of hello to \"bye\" using SetString",stringcmp(hello,bye) == 0);
  test("Checking hellos length was changed to 3",hello->length == 3);

  setStringC(hello,"Test");
  test("changing value of hello to \"test\" using SetString",stringcmp(hello,"test") == 0);
  test("Checking hellos length was changed to 4",hello->length == 4);

  freeString(bye);
  bye = copyString(hello);
  
  printf("\nfreeing Strings\n\n");
  freeString(hello);
  freeString(bye);

  test("Done",1);
}
