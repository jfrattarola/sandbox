#include "TestCases.h"
#include "SignalHandler.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Instantiating SignalHandler\n");  
  SignalHandler* sig = new SignalHandler();
  SingleCallable sc;
  MultiCallable mc1( 1 );
  MultiCallable mc2( 2 );
  MultiCallable mc3( 3 );
  RegisterCallable rc( sig, &mc3 );
  RecursiveCallable rcc( sig );
  InfiniteCallable ic( sig );

  printf("Calling registerCallback( SINGLE_SIG, SingleCallable )\n");  
  sig->registerCallback( SINGLE_SIG, sc );
  
  printf("Calling registerCallback( MULTI_SIG, MultiCallable(1) )\n");  
  sig->registerCallback( MULTI_SIG, mc1 );
  printf("Calling registerCallback( MULTI_SIG, MultiCallable(2) )\n");  
  sig->registerCallback( MULTI_SIG, mc2 );
  printf("Calling registerCallback( MULTI_SIG, MultiCallable(3) )\n");  
  sig->registerCallback( MULTI_SIG, mc3 );
  printf("Calling registerCallback( REG_SIG, RegisterCallable )\n");  
  sig->registerCallback( REG_SIG, rc );
  printf("Calling registerCallback( RECURS_SIG, RecursiveCallable )\n");  
  sig->registerCallback( RECURS_SIG, rcc );
  printf("Calling registerCallback( ERROR_SIG, InfiniteCallable )\n");  
  sig->registerCallback( ERROR_SIG, ic );
  printf("\n");
  

  printf("\n$ Invoking signal(SINGLE_SIG)...\n");
  sig->signal( SINGLE_SIG );
  printf("\n$ Invoking signal(REG_SIG) - this should deregister multi3 and register multi4...\n");
  sig->signal( REG_SIG );
  printf("\n$ Invoking signal(MULTI_SIG) - was REG_SIG successful?...\n");
  sig->signal( MULTI_SIG );
  printf("\n$ Invoking signal(RECURS_SIG) - will call signal for SINGLE_SIG...\n");
  sig->signal( RECURS_SIG );
  printf("\n$ Invoking signal(ERROR_SIG) - this will cause an infinite loop unless safe was set to true...\n");
  sig->signal( ERROR_SIG );
  
  return 0;
}
