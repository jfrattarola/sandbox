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