# Ring list based on an array

##### _Author Vorontsov Amadey_


# Introduction

### This is a simple library that you can use to work with a list or a ring buffer.

### The advantage of this library is that due to its implementation, this list works faster than the standard std::list


# Instalation

### To install this library, it is enough to register #include

# Graph Dump

### For debugging convenience, the library provides access to the GraphDump() method, which graphically depicts your list

![alt text](https://github.com/vorontsov-amd/List/blob/main/graph.png?raw=true)

# Documentation

```c++
--------------------------------------------------------------------------------------
int Incert(int index, const T& value);

Precondition: 
[index] points to the memory cell after which we want to insert the element
[value] - the element we want to insert into the list

Postcondition:
[value] is logically related to the previous element located in the [index] cell
The function returns the number of the cell in which the [value] element is placed
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
int PushFront(const T& value);

Precondition: 
[value] - the element we want to insert into head the list

Postcondiyion:
[value] is at the top of the list
The function returns the number of the cell in which the [value] element is placed
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
int PushBack(const T& value);

Precondition: 
[value] - the element we want to insert into tail the list

Postcondiyion:
[value] is at the end of the list
The function returns the number of the cell in which the [value] element is placed
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
T Delete(int index);

Precondition:
[index] shows the number of the cell we want to remove from the list

Postcondiyion:
Item removed from the list
The function returns the value of the deleted element
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
T Show(int index);

Precondition:
[index] shows the number of the cell we want to show from the list

Postcondition:
The function returns the value of the element
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------
T PopFront();

Postcondition:
Head item removed from the list
The function returns the value of the deleted element
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------
T PopBack();

Postcondition:
Tail item removed from the list
The function returns the value of the deleted element
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------
void GraphDump(const char * const graphname = "graph");

Precondition:
[graphname] is a string containing the name that will be used to name the file with the list dump. By default "graph"

Postcondition:
There are 2 files in the project folder .dot and .png
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
void Dump();

Postcondition:
Console dump and information about the contents of the list
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
void Sorting();

Postcondition:
The list is sorted so that the logical order coincides with the physical one
----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
bool ListIsSoreted();

Postcondition:
Returns the fact that the list is sorted
----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
int TranslateIndex(int logic_index);

Precondition:
[logic_index] is the logical number of the node in the list

Postcondition:
The function returns the physical number of the cell in the array where the node is located

Try to save cell numbers using the Insert() return value.
-----------------------------------------------------------------------------------------
```

