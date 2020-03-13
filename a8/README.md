### TODO Please edit the following information in this README

- Name:
- How many hours did it take you to complete this assignment?
- Did you collaborate with any other students/TAs/Professors? (Name them below)
  - tbd
  - tbd
- Did you use any external resources? (Cite them below)
  - tbd
  - tbd
- (Optional) What was your favorite part of the assignment?
- (Optional) How would you improve the assignment?

See Canvas for all the details! 

# A8: Building a Data Indexer

## Files: 
* ```FileParser```: Responsible for reading in a file, checking for errors, and parse out movies.
* ```Movie```: A struct holding all the Movie info (id, title, type, genre, etc.)
* ```MovieIndex```: A hashtable that indexes movies according to specified field. Basically wraps a hashtable with functionality specific to adding/removing/destroying with MovieSets. The key is the description for the document set, and the value is the document set.
* ```MovieReport```: Responsible for printing out a report given a MovieIndex, to the command line or file.
* ```MovieSet```: A set of Movies that are connected somehow: they have the same value for a given field. If the field is Year, all the movies in the set are made in the same year. It consists of a description and a LinkedList of Movies.

## Tasks 

The basic tasks you need to complete:

* Modify main to accept flags on input and do the right thing.
* Modify Movie struct to hold an array of genres
* Modify MovieSet to ensure no duplicates of movies
* Bulk up tests

To do this, go through each file, and identify the "TODO" tags (listed below; generated with ```grep -n TODO *.c```). 

### The TODOs and some more details

To make sure you've implemented everything, you can run the following line of code: 

```
grep -nr TODO *
```

Note: some will require you to implement some code, while others will require you to answer a question in your writeup (README.md). 

## To run a single Google test

Instead of running all the tests at once, you can run just a single test something like this: 

```
./test_suite --gtest_filter=Hashtable.AddOneRemoveOne
```

Here, only the ```Hashtable.AddOneRemoveOne``` test will run. 
