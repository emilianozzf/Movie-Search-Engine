- Name: Emiliano Zhu
- How many hours did it take you to complete this assignment? 15 hours.
- Did you collaborate with any other students/TAs/Professors? (Name them below)
  - None
- Did you use any external resources? (Cite them below)
  - https://www.ibm.com/developerworks/cn/linux/l-pthred/index.html
  - https://blog.csdn.net/sws9999/article/details/5824836
  - https://blog.csdn.net/liangxanhai/article/details/7767430
- (Optional) What was your favorite part of the assignment? Threads manipulating.
- (Optional) How would you improve the assignment? Refactoring code.

See Canvas for all the details! 

# A10: Multi-Threading

## Files: 
* ```Benchmarker```: builds multiple indexes, using both the single-threaded and multi-threaded approaches.
* ```DirectoryParser_MT```: builds the multi-threaded version of DirectoryParser.c (from last week).
* ```main```: basically runs the system (as before).
* ```libA8```: library from our previous assignment 8.
* ```libA9```: library from our previous assignment 9.
* ```libHtll```: library for HashTable and LinkedList.

## To run main program

```
./main dir/
(where dir is the directory to look for files to index)
Example:
./main data_tiny/

(DON'T FORGET THE TRAILING SLASH)
```

## To run benchmarker program

```
./benchmarker dir/
(where dir is the directory to look for files to index)
Example:
./benchmarker data_tiny/

(DON'T FORGET THE TRAILING SLASH)
```
