#ifndef SIG_H
#define SIG_H

#include <stdio.h>
#include <inttypes.h>

namespace SIG {
  struct HANDLE;

  typedef void (*callbackFunction)( void* tag );

  /* If safe is true, a callback function can only be called once.  
     This will prevent accidental infinite callback loops where A either calls
     A directly, or some callback function triggered by A ends up calling A again 
     somewhere down the chain.
     However, this prevents a single function to be called multiple times in a safe way
     ( for instance, B is some logging function, which is called in the set of cb by each signal raised.
     if multiple signals are raised, B would only log the first)
  */
  HANDLE* init( bool safe=true );
  void destroy( HANDLE*& );

  void registerCallback( HANDLE*, int signal_id, callbackFunction, void* tag );
  void unregisterCallback( HANDLE*, int signal_id, callbackFunction );
  void signal( HANDLE*, int signal_id );
};

#endif
