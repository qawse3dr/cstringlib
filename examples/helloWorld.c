/*Author: qawse3dr aka Lawrence Milne
  compilation: gcc helloWorld.c -lcstring
*/

#include <stdio.h>
#include <cstring.h>

int main(){
  String string = createString("hello world");

  printf("%s\n",getString(string));

  return 0;
}
