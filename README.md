# Assignment_4

How to Compile and Run
Make sure wordhunt.cpp and dictionary.txt are in the same folder.

Compile the program using:
g++ -o wordhunt wordhunt.cpp

Run the program using:
./wordhunt


Program Description

This program is a simple word hunt game inspired by Boggle.
It generates a board with random uppercase letters and the user tries to
find words by moving through adjacent letters on the board.
The board is created using dynamic memory and pointers.
Recursion is used to search for different possible word paths on the board.


Features Implemented (as described in Assignment)

- Uses recursion to search for words
- Board size can be from 3x3 to 6x6
- Dictionary is loaded from a text file
- Score depends on the length of the word

No extra features were implemented.

Known Limitations / Bugs
- Same word can be found and scored more than once
- Random letters sometimes result in very few valid words
- Dictionary search is linear and not very efficient 
- Program does not properly handle invalid menu input

Bonus Features
None (bas aur nahi horaha bhai)
