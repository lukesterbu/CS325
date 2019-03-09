README file for Luke's binpack.cpp

binpack.cpp Instructions
To compile this program on flip use the following command: "g++ -std=c++11 binpack.cpp -o binpack". Once you have compiled the .cpp file using C++11 you will be able to run the program using "./binpack". If "bin.txt" is in the same directory as where you compiled "binpack.cpp" then the program will print out results similar to the below (in the format from the homework instructions):

Test Case 1 First Fit: 4, First Fit Decreasing: 3, Best Fit: 4
Test Case 2 First Fit: 15, First Fit Decreasing: 10, Best Fit: 15
Test Case 3 First Fit: 3, First Fit Decreasing: 2, Best Fit: 2

If the file is not in the same directory as where you compiled "binpack.cpp" then the program will print out "The file bin.txt does not exist in this directory.". The program uses sample input in the format below:

3
10
6
5 10 2 5 4 4
10
20
4 4 4 4 4 4 4 4 4 4 6 6 6 6 6 6 6 6 6 6
10
4
3 8 2 7

The first line is the number of test cases, followed by the capacity of bins for that test case, the number of items and then the weight of each item. You can assume that the weight of an item does not exceed the capacity of a bin for that problem.
