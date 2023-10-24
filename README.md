# Browser-History-Search Autocomplete System
Cache.txt
As a Sample input we have inserted some sentences that we assumed have been searched multiple times.

# SearchAutoCompleteSystem.cpp
This File contains the main program which works the following way :

Load all the sentences previously searched along with frequencies (Which we have taken to be Cache.txt)
Add all the sentences and frequencies using appropriate Data Structure.
Start Taking input from user letter by letter and calculate results for the same. (We are showing only top 3 results for now)
When The user enters '#' we assume the word is complete and we show the final results.
Add the Searched sentence in the Data Structure with increased frequency as well as in Cache.txt if it is not present.
