C++ Developer Qualification Test 

Developer: Victor V. Rudakov
Tool: MS Visual Studo 2022

i) Results

File "safe_queue.h" - contains decription and implementation of an asynchronous message exchange template class "SafeQueue"   
File  "safe_queue_test.cpp" - contains decription  and implementation of demo tests for class  "SafeQueue" (as Win32 console application)

ii) Task and requirements:

You are asked to implement an asynchronous message exchange queue between ‘Writer’ (aka ‘Producer’) thread and “Reader” (aka ‘Consumer’) thread. 
This queue is supposed to be used for temporary traffic peaks mitigation (e.g. 'Reader’ is consuming messages with a constant rate, while ‘Writer’ produces messages randomly)

Requirements:
1. 
Queue must be of fixed size (specified during construction)
2. 
Queue ‘pop’ operation must be blocking: returns a message or blocks waiting for it
3. 
Queue ‘push’ operation must be non-blocking: in case message addition is not possible, returns an error.
4. 
Every message sent by a ‘writer’ thread must be consumed by a ‘reader’ thread in FIFO order.
5. 
Class code should be written in ‘production’ style. That is the class should be reusable, containing all the necessary attributes, and being ready to be plugged into application.
6. 
No external libraries allowed. You can use C++ and STL only.

7. 
Implement ‘close’ function, that makes further pop/push impossible (update the interface and implementation of pop/push functions accordingly). Close can be entered by any thread.
8. 
Make ‘push’ enterable by several ‘writer’ threads, ‘pop’ enterable by several ‘reader’ threads.
9. 
Implement get (PREDICATE) method, which accepts predicate, and returns first matching element from the queue.
10. 
Implement blocking ‘push’ method: in case message addition is not possible, wait until it possible
11. 
Implement non-blocking ‘pop’ method: in case message is not available, return an error


