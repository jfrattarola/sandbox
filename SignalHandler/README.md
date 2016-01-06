## Project Specifics
You will implement an in-process signal API with the following functions:
* registerCallback(int signal_id, Callable& callback);
* unregisterCallback(int signal_id, Callable& callback);
* signal(int signal_id);

Assume that the Callable class has a call() method which you can call to invoke the supplied callback.

The semantics of the API are that any number of callbacks can be registered for a given signal ID. E.g., signal 5 can have 0 callbacks, signal 6 can have 1000 callbacks, etc. Callbacks are unregistered via the same tuple that they are registered with. When signal() is invoked, all callbacks that have been registered should be called.

Implementation/expectation notes:
* Multi-threaded support is not expected.
* Include error checking.
* If poorly behaved callbacks can affect your implementation, add comments on what can happen depending on what they do.
* Your implementation should support recursive entry. I.e., calling back into your API from within a callback. You have some leeway in terms of the exact semantics, but a caller should be able to register/unregister a callback from within a callback, resignal the same signal ID, etc.
* You should include some test cases with your code.
* Your code should compile. C++11 is preferred.

## Version Notes
I present two versions here, one under the folder "namespaceExample" and one under "classExample".

"namespaceExample" is written in the style of C/C++ that I use on a regular basis (namespaces instead of classes).

"classExample" is my effort at reproducing "namespaceExample" in the format implied by the project specifics.

## Build
Both versions of the solution may be built by executing `./build.sh`

An executable, named "sighandler" is produced and should be run without any arguments.

## Sample Output
Depending on which version was run and/or whether the code was modified, output similar to the following should be printed to stdout:

`Instantiating SignalHandler
Calling registerCallback( SINGLE_SIG, SingleCallable )
Calling registerCallback( MULTI_SIG, MultiCallable(1) )
Calling registerCallback( MULTI_SIG, MultiCallable(2) )
Calling registerCallback( MULTI_SIG, MultiCallable(3) )
Calling registerCallback( REG_SIG, RegisterCallable )
Calling registerCallback( RECURS_SIG, RecursiveCallable )
Calling registerCallback( ERROR_SIG, InfiniteCallable )


$ Invoking signal(SINGLE_SIG)...
SINGLE_SIG was raised

$ Invoking signal(REG_SIG) - this should deregister multi3 and register multi4...
REG_SIG was raised.
	Will unregister function 3 for  MULTI_SIG
	Will register function 4 for MULTI_SIG

$ Invoking signal(MULTI_SIG) - was REG_SIG successful?...
MULTI_SIG was raised. In function 1
MULTI_SIG was raised. In function 2
MULTI_SIG was raised. In function 4

$ Invoking signal(RECURS_SIG) - will call signal for SINGLE_SIG...
RECURS_SIG was raised.
	Will raise signal: SINGLE_SIG now
SINGLE_SIG was raised

$ Invoking signal(ERROR_SIG) - this will cause an infinite loop unless safe was set to true...
ERROR_SIG was raised.
	Will raise signal: ERROR_SIG now...This will initiate a recursive, infinite loop if not handled correctly.`