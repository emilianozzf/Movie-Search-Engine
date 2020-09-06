- Name: Emiliano Zhu
- How many hours did it take you to complete this assignment? 15 hours.
- Did you collaborate with any other students/TAs/Professors? (Name them below)
  - None
- Did you use any external resources? (Cite them below)
  - https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
  - https://blog.csdn.net/afei__/article/details/81261879
- (Optional) What was your favorite part of the assignment? Memory Manipulating.
- (Optional) How would you improve the assignment? Refactoring code.

See Canvas for all the details! 

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