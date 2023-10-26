# Search Autocomplete System
Input.txt
As a Sample input I have inserted some sentences that I assumed have been searched multiple times.

# SearchAutoCompleteSystem.cpp
This File contains the program which works the following way :

1) Load all the sentences previously searched along with frequencies (Which we have taken to be Input.txt)
2) Add all the sentences and frequencies using appropriate Data Structure.
3) Start Taking input from user letter by letter and calculate results for the same. (We are showing only top 3 results for now)
4) When The user enters '#' we assume the word is complete and we show the final results.
5) Add the Searched sentence in the Data Structure with increased frequency as well as in Input.txt if it is not present.
