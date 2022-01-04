is_Palindrome_thread contains:
    2 .cpp files
    1 .h
    of programing that generate the program UPalindrome 2022.

On startup you will enter the main menu a gui built around user supplied integer commands ( 1, 2, 3, 4, 5) are the only accepted inputs the rest would make the program re-ask the user for input.
The main two commands (1. Read from file) and (2.Read from User) are how th euser will supply the program with the strings they wish to find the palindromes within
Command (3. Print the list) is how the user will view all Palindromes stored in the Program from what the user supplied
Command (4. Toggle time_task) changes the programs setting on outputing the time to process a given file or string. Time_task is default on false.
Command (5. Exit) will end the program

e.g. step 1. Run program (for windows UPalindrome.exe)
        The main menu will be displayed
    step 2. press the '2' key and the 'enter' key
        The program will now await your input for a string
    step 3. input a string such as "abba"
        The program will process the given string and return the user to the main menu
    step 4. press the '3' key and the 'enter' key
        The program will now display the palindrome abba with its starting location (0) in the provided string and its length (4)



Time complexity: the checkPattern function is the algorithm that iterates over the string searching for the patterns |aa|, and |aba| this requires checking the value in front (next) the value after
an extra check on the value before is necessary with threads to prevent duplication of sequences/palindromes. This means that under a brute force approach it takes a minimum 3 comparisons of values per character to check for
being a palindrome O(3n). To reduce this time complexity UPalindrome generates a thread_pool that will run the char comparisons in parallel. This reduces the time complexity to O(3n/T) where T is  the number of threads
the computer can run based upon |std::thread::hardware_concurrency()|. The time complexity of gathering the extent of a palindrome is n/2 - p where p is the length of the starting pattern, this can be approximated to worst case
n/2 being the worst case for the entire provided string being 1 palindrome, and best case O(1) where the provided starting pattern is the extent of the pattern.

In summary the worst case being a single threading system and the entire string is 1 palindrome O(3n + n/2) -> O(3.5n)
if no palindromes are provided O(3n/T)

Testing:
    Test1 small pattern checking
    Test2 provided input test
    Test3 tests for ignoring case sensitivity
    test4 tests for large input 


Manual compiling instructions while in shell 

g++ -std=c++17 main.cpp Palindrome.cpp Palindrome.h -o UPalindrome

