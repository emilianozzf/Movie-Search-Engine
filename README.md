# MOVIE SEARCH ENGINE


# Assignment 7: Linked List with Iterator, Google Testing

## Files

* ```Makefile```: a makefile you can use to compile the assignment using the Linux command make all.
* ```LinkedList.h```: a header file that defines and documents the API to the linked list. A customer of the linked list includes this header file and uses the functions defined within in. Read through this header file very carefully to understand how the linked list is expected to behave.
* ```LinkedList_priv.h, LinkedList.c```: ```LinkedList_priv.h``` is a **private** header file included by ```LinkedList.c```; it defines the structures we diagrammed above. ```LinkedList.c``` contains the partially completed implementation of our doubly-linked list. Your task will be to finish the implementation. Take a minute and read through both files; note that there are a bunch of places in ```LinkedList.c``` that say "STEP X:" these labels identify the missing pieces of the implementation that you will finish.
* ```example_program_ll.c```: this is a simple example of how a customer might use the linked list; in it, you can see the customer allocating a linked list, adding elements to it, creating an iterator, using the iterator to navigate a bit, and then cleaning up.
* ```test_linkedlist.cc```: this file contains unit tests that we wrote to verify that the linked list implementation works correctly. The unit tests are written to use the Google Test (Links to an external site.) unit testing framework, which has similarities to Java's JUnit testing framework. Further, this test harness will assist TAs in grading your assignment: as you add more pieces to the implementation, the test harness will make it further through the unit tests, and it will print out a cumulative score along the way. You don't need to understand what's in the test driver for this assignment, though if you peek inside it, you might get hints for what kinds of things you should be doing in your implementation!
* ```solution_binaries```: in this directory, you'll find some Linux executables, including ```example_program_ll``` and ```test_suite```. These binaries were compiled with a complete, working version of ```LinkedList.c```; you can run them to explore what should be displayed when your assignment is working!

# A8: Building a Data Indexer

## Files: 
* ```FileParser```: Responsible for reading in a file, checking for errors, and parse out movies.
* ```Movie```: A struct holding all the Movie info (id, title, type, genre, etc.)
* ```MovieIndex```: A hashtable that indexes movies according to specified field. Basically wraps a hashtable with functionality specific to adding/removing/destroying with MovieSets. The key is the description for the document set, and the value is the document set.
* ```MovieReport```: Responsible for printing out a report given a MovieIndex, to the command line or file.
* ```MovieSet```: A set of Movies that are connected somehow: they have the same value for a given field. If the field is Year, all the movies in the set are made in the same year. It consists of a description and a LinkedList of Movies.


## To run a single Google test

Instead of running all the tests at once, you can run just a single test something like this: 

```
./test_fileparser --gtest_filter=FileParser.CreateMovieFromRow
```

Here, only the ```FileParser.CreateMovieFromRow``` test will run.

# A9: Indexing Files to Query

## Files: 
* ```DocIdMap```: A DocIdMap is a Hashtable that maps unique IDs to filenames.
* ```FileCrawler```: Iterates through a given directory, and for all files it finds, adds them to the provided DocIdMap to assign a unique id.
* ```DocSet```: A DocSet is a set of documents. doc_index is a hashtable where the key is a doc_id, and the value is a linked list. The payloads in the linked list is a row_id that indicates which row in the specified file has the info about the movie that belongs in this set.
* ```MovieTitleIndex```: An index is a hashtable where they key is a term, and the value is either a MovieSet or SetOfMovies.
* ```DirectoryParser```: Given a map of all the files that we want to index and search, open each file and index the contents to index.
* ```QueryProcessor```: Responds to queries.
* ```Main```: Sets up the index and runs a loop for the user to query the index.

## To run a single Google test

Instead of running all the tests at once, you can run just a single test something like this: 

```
./test_suite --gtest_filter=DocIdMap.*
```

Here, only the ```DocIdMap.*``` test will run. 

## To run main program

```
./main dir/
(where dir is the directory to look for files to index)
Example:
./main data_tiny/

(DON'T FORGET THE TRAILING SLASH)
```

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
