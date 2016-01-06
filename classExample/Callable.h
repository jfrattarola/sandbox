#ifndef CALLABLE_H
#define CALLABLE_H

#include <stdlib.h>
#include <stdio.h>

class Callable {
 public :
  Callable() { }
  
  virtual void call() {printf("default\n");}

  ~Callable() { }
};

#endif
