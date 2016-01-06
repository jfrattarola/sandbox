#include "SIG.h"
#include <stdlib.h>
#include <map>
#include <set>

namespace SIG {
  struct CB {
    callbackFunction cb;
    void* tag;
  };

  struct HANDLE {
    std::multimap<int, CB*>* sigMap;
    std::set<callbackFunction>* deduper;
    int level;
    bool safe;
  };

  //  typedef void (*callbackFunction)( void* tag );

  HANDLE* init( bool safe/*=true*/ ) {
    HANDLE* res = (HANDLE*)malloc( sizeof(*res) );
    res->sigMap = new std::multimap<int, CB*>;
    res->deduper = new std::set<callbackFunction>;
    res->level = 0;
    res->safe = safe;
    return res;
  }

  void destroy( HANDLE*& h ) {
    if (h) {
      for (std::multimap<int, CB*>::iterator iter = h->sigMap->begin(); 
	   iter != h->sigMap->end();
	   ++iter) {
	CB* cb = iter->second;
	free(cb);
      }
      delete h->deduper;
      delete h->sigMap;
      free(h);
      h = NULL;
    }
  }

  void registerCallback( HANDLE* h, int signal_id, callbackFunction func, void* tag ) {
    if (h && func) {
      CB* cb = (CB*)malloc(sizeof(*cb));
      cb->cb = func;
      cb->tag = tag;
      h->sigMap->insert(std::pair<int, CB*>(signal_id, cb));
    }
  }

  void unregisterCallback( HANDLE* h, int signal_id, callbackFunction func ) {
    if (h && func) {
      std::pair<std::multimap<int, CB*>::iterator, std::multimap<int, CB*>::iterator> rangeIter;
      rangeIter = h->sigMap->equal_range(signal_id);
      for (std::multimap<int, CB*>::iterator iter = rangeIter.first; 
	   iter != rangeIter.second;
	   ++iter) {
	CB* cb = iter->second;
	if (cb->cb == func) {
	  free(cb);
	  h->sigMap->erase(iter);
	  break;
	}
      }
    }
  }

  void signal( HANDLE* h, int signal_id ) {
    if (h) {
      h->level++;
      std::pair<std::multimap<int, CB*>::iterator, std::multimap<int, CB*>::iterator> rangeIter;
      rangeIter = h->sigMap->equal_range(signal_id);
      for (std::multimap<int, CB*>::iterator iter = rangeIter.first; 
	   iter != rangeIter.second;
	   ++iter) {
	CB* cb = iter->second;
	bool shouldCall = true;
	if (h->safe) {
	  std::pair<std::set<callbackFunction>::iterator, bool> success = h->deduper->insert(cb->cb);
	  shouldCall = success.second;
	}
	if (shouldCall) {
	  cb->cb(cb->tag);
	}
      }
      h->level--;
      if (!h->level && h->safe) {
	h->deduper->clear();
      }
    }
  }
};
