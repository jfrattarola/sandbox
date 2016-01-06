#include "SIG.h"
#include <stdio.h>
#include <stdlib.h>

#define SINGLE_SIG 1
#define MULTI_SIG  2
#define REG_SIG    3
#define RECURS_SIG 4
#define ERROR_SIG  5

struct TEST {
  SIG::HANDLE* sh;
  int someMember;
};

void singleSignalCB( void* tag ) {
  printf("SINGLE_SIG was raised\n");
}

void multiSignalCB1( void* tag ) {
  printf("MULTI_SIG was raised. In CB1\n");
}

void multiSignalCB2( void* tag ) {
  printf("MULTI_SIG was raised. In CB2\n");
}

void multiSignalCB3( void* tag ) {
  printf("MULTI_SIG was raised. In CB3\n");
}

void multiSignalCB4( void* tag ) {
  printf("MULTI_SIG was raised. In CB4\n");
}

void registerSignalCB( void* tag ) {
  printf("REG_SIG was raised.\n");
  printf("\tWill unregister MULTI_SIG with multiSignalCB3()\n");
  printf("\tWill register MULTI_SIG with multiSignalCB4()\n");
  TEST* test = (TEST*)tag;
  SIG::unregisterCallback( test->sh, MULTI_SIG, multiSignalCB3 );
  SIG::registerCallback( test->sh, MULTI_SIG, multiSignalCB4, test );
}

void recursiveSignalCB( void* tag ) {
  printf("RECURS_SIG was raised.\n");
  printf("\tWill raise signal: SINGLE_SIG now\n");
  TEST* test = (TEST*)tag;
  SIG::signal( test->sh, SINGLE_SIG );
}

void infLoopSignalCB( void* tag ) {
  printf("RECURS_SIG was raised.\n");
  printf("\tWill raise signal: ERROR_SIG now...This will initiate a recursive, infinite loop if not handled correctly.\n");
  TEST* test = (TEST*)tag;
  SIG::signal( test->sh, ERROR_SIG ); 
}

int main() {

  TEST* test = (TEST*)malloc(sizeof(*test));
  test->sh = SIG::init();
  
  SIG::registerCallback( test->sh, SINGLE_SIG, singleSignalCB, test );
  SIG::registerCallback( test->sh, MULTI_SIG, multiSignalCB1, test );
  SIG::registerCallback( test->sh, MULTI_SIG, multiSignalCB2, test );
  SIG::registerCallback( test->sh, MULTI_SIG, multiSignalCB3, test );
  SIG::registerCallback( test->sh, REG_SIG, registerSignalCB, test );
  SIG::registerCallback( test->sh, RECURS_SIG, recursiveSignalCB, test );
  SIG::registerCallback( test->sh, ERROR_SIG, infLoopSignalCB, test );

  SIG::signal( test->sh, SINGLE_SIG );
  SIG::signal( test->sh, REG_SIG );
  SIG::signal( test->sh, MULTI_SIG );
  SIG::signal( test->sh, RECURS_SIG );
  SIG::signal( test->sh, ERROR_SIG );

  SIG::destroy(test->sh);
  free(test);
  return 0;
}
