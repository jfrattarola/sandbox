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
  printf("Initializing SIG::HANDLE\n");
  test->sh = SIG::init();

  printf("Calling registerCallback( SINGLE_SIG, singleSignalCB )\n");  
  SIG::registerCallback( test->sh, SINGLE_SIG, singleSignalCB, test );
  printf("Calling registerCallback( MULTI_SIG, multiSignalCB1 )\n");  
  SIG::registerCallback( test->sh, MULTI_SIG, multiSignalCB1, test );
  printf("Calling registerCallback( MULTI_SIG, multiSignalCB2 )\n");  
  SIG::registerCallback( test->sh, MULTI_SIG, multiSignalCB2, test );
  printf("Calling registerCallback( MULTI_SIG, multiSignalCB3 )\n");  
  SIG::registerCallback( test->sh, MULTI_SIG, multiSignalCB3, test );
  printf("Calling registerCallback( REG_SIG, registerSignalCB )\n");  
  SIG::registerCallback( test->sh, REG_SIG, registerSignalCB, test );
  printf("Calling registerCallback( RECURS_SIG, recursiveSignalCB )\n");  
  SIG::registerCallback( test->sh, RECURS_SIG, recursiveSignalCB, test );
  printf("Calling registerCallback( ERROR_SIG, infLoopSignalCB )\n");  
  SIG::registerCallback( test->sh, ERROR_SIG, infLoopSignalCB, test );
  printf("\n");
  printf("\n$ Invoking signal(SINGLE_SIG)...\n");
  SIG::signal( test->sh, SINGLE_SIG );
  printf("\n$ Invoking signal(REG_SIG) - this should deregister multi3 and register multi4...\n");
  SIG::signal( test->sh, REG_SIG );
  printf("\n$ Invoking signal(MULTI_SIG) - was REG_SIG successful?...\n");
  SIG::signal( test->sh, MULTI_SIG );
  printf("\n$ Invoking signal(RECURS_SIG) - will call signal for SINGLE_SIG...\n");
  SIG::signal( test->sh, RECURS_SIG );
  printf("\n$ Invoking signal(ERROR_SIG) - this will cause an infinite loop unless safe was set to true...\n");
  SIG::signal( test->sh, ERROR_SIG );

  printf("\nDestroying SIG::HANDLE\n");
  SIG::destroy(test->sh);
  free(test);
  return 0;
}
