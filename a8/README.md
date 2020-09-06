- Name: Emiliano Zhu
- How many hours did it take you to complete this assignment? 20 hours.
- Did you collaborate with any other students/TAs/Professors? (Name them below)
  - None
- Did you use any external resources? (Cite them below)
  - https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
  - https://blog.csdn.net/afei__/article/details/81261879
- (Optional) What was your favorite part of the assignment? Memory Manipulating.
- (Optional) How would you improve the assignment? Refactoring code.

See Canvas for all the details! 

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
