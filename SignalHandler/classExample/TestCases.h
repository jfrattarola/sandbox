#ifndef TEST_CASES_H
#define TEST_CASES_H

#include "Callable.h"
#include "SignalHandler.h"
#define SINGLE_SIG 1
#define MULTI_SIG  2
#define REG_SIG    3
#define RECURS_SIG 4
#define ERROR_SIG  5


class SingleCallable : public Callable {
public :
  void call() {
    printf("SINGLE_SIG was raised\n");
  }
};

class MultiCallable : public Callable {
  int id;
public :
  MultiCallable( int _id ) : 
    Callable() {
    id = _id;
  }

  void call() {
    printf("MULTI_SIG was raised. In function %d\n", id);
  }
};

class RegisterCallable : public Callable {
 public :
  RegisterCallable( SignalHandler* _sig, MultiCallable* _mc ) :
    Callable() {
    sig = _sig;
    mc = _mc;
  }

  ~RegisterCallable()  {
    if (mcNew) delete mcNew;
  }

  void call() {
    printf("REG_SIG was raised.\n");
    printf("\tWill unregister function 3 for  MULTI_SIG\n");
    printf("\tWill register function 4 for MULTI_SIG\n");
    sig->unregisterCallback( MULTI_SIG, *mc );
    mcNew = new MultiCallable( 4 );
    sig->registerCallback( MULTI_SIG, *mcNew );
  }
  
private :
  SignalHandler* sig;
  MultiCallable* mc;
  MultiCallable* mcNew;
};

class RecursiveCallable : public Callable {
public :
  RecursiveCallable( SignalHandler* _sig ) :
    Callable() {
    sig = _sig;
  }

  void call() {
    printf("RECURS_SIG was raised.\n");
    printf("\tWill raise signal: SINGLE_SIG now\n");
    sig->signal( SINGLE_SIG );
  }
  
private :
  SignalHandler* sig;
};

class InfiniteCallable : public Callable {
public :
  InfiniteCallable( SignalHandler* _sig ) :
    Callable() {
    sig = _sig;
  }

  void call() {
    printf("ERROR_SIG was raised.\n");
    printf("\tWill raise signal: ERROR_SIG now...This will initiate a recursive, infinite loop if not handled correctly.\n");
    sig->signal( ERROR_SIG ); 
  }
  
private :
  SignalHandler* sig;
};


#endif
