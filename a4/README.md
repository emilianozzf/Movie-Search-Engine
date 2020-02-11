1. Differences between memory on the stack and heap:

    Stack is used for static memory allocation and Heap for dynamic memory allocation, both stored in the computer's RAM .

    Variables allocated on the stack are stored directly to the memory and access to this memory is very fast, and it's allocation is dealt with when the program is compiled. When a function or a method calls another function which in turns calls another function etc., the execution of all those functions remains suspended until the very last function returns its value. The stack is always reserved in a LIFO order, the most recently reserved block is always the next block to be freed. This makes it really simple to keep track of the stack, freeing a block from the stack is nothing more than adjusting one pointer.

    Variables allocated on the heap have their memory allocated at run time and accessing this memory is a bit slower, but the heap size is only limited by the size of virtual memory. Element of the heap have no dependencies with each other and can always be accessed randomly at any time. You can allocate a block at any time and free it at any time. This makes it much more complex to keep track of which parts of the heap are allocated or free at any given time.

     You can use the stack if you know exactly how much data you need to allocate before compile time and it is not too big. You can use heap if you don't know exactly how much data you will need at runtime or if you need to allocate a lot of data.

     In a multi-threaded situation each thread will have its own completely independent stack but they will share the heap. Stack is thread specific and Heap is application specific. The stack is important to consider in exception handling and thread executions.

2. How to build and run the codie
    * make
    * make test
    * make play
    * ./test
    * ./play

3. Description of the files in the directory
    * a4.c: The Hand and other functions are in here.
    * a4.h: the header file. 
    * a4\_run.c: The run functions are in here.
    * a4\_helper.c: The helper functions are in here.
    * a4\_test.c: The test functions are in here.
    * deck.c: The deck functions are in here.
    * Makefile
 
4. A summary of the assignment
    In this assignment, I am going to implement some key components to a card game. The card game is NEUchre (pronounced "N-E-U-ker"), which is a 2-player version of a game called Euchre (pronounced "U-ker").

5. How much time you spent on it
    6 hours.
