#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include "Callable.h"
#include <map>
#include <set>

class SignalHandler {
 public :
  SignalHandler(bool _safe=true) {
    safe = _safe;
    level = 0;
    sigMap = new std::multimap<int, Callable*>;
    deduper = new std::set<Callable*>;
  }
  ~SignalHandler() {
    delete sigMap;
    delete deduper;
  }
  
  void registerCallback(int signal_id, Callable& callback) {
    sigMap->insert(std::pair<int, Callable*>(signal_id, &callback));
  }

  void unregisterCallback(int signal_id, Callable& callback) {
    std::pair<std::multimap<int, Callable*>::iterator, std::multimap<int, Callable*>::iterator> rangeIter;
    rangeIter = sigMap->equal_range(signal_id);
    for (std::multimap<int, Callable*>::iterator iter = rangeIter.first;
	 iter != rangeIter.second;
	 ++iter) {
      Callable* cb = iter->second;
      if (cb == &callback) {
	sigMap->erase(iter);
	break;
      }
    }
  }

  void signal(int signal_id) {
    level++;
    std::pair<std::multimap<int, Callable*>::iterator, std::multimap<int, Callable*>::iterator> rangeIter;
    rangeIter =sigMap->equal_range(signal_id);
    for (std::multimap<int, Callable*>::iterator iter = rangeIter.first;
	 iter != rangeIter.second;
	 ++iter) {
      Callable* cb = iter->second;
      std::pair<std::set<Callable*>::iterator, bool> success = deduper->insert(cb);
      if (success.second == true) {
	cb->call();
      }
    }
    level--;
    if (!level && safe) {
      deduper->clear();
    }

  }

 private :
  std::multimap<int, Callable*>* sigMap;
  std::set<Callable*>* deduper;
  int level;
  bool safe;
};

#endif
