#ifndef PALINDROME_H
#define PALINDROME_H
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <future>


class Palindrome
{
private:
    std::string str;
    int start_loc;
    int length;
    
public:
    friend std::ostream& operator<<(std::ostream& os, const Palindrome& obj);
    
    bool operator<(const Palindrome& other);
    bool operator>(const Palindrome& other);
    bool operator==(const Palindrome& other);
    
    
    Palindrome(std::string str, int start_loc):str(str),start_loc(start_loc)
        {
            this->length = str.length();
        };
    Palindrome(std::string str, int start_loc, int length):str(str), start_loc(start_loc), length(length){};
    ~Palindrome();

};

//supporting function for vector sorting
bool ptrToPalindrome(Palindrome* p, const Palindrome* p2);

//function expands the search from the centre of a palindrome
//and add the Palindrome to the list
//should get copies of the iterators and a reference to the list
Palindrome* getPalindrome(const std::string& str, std::string::const_iterator left, std::string::const_iterator right);

//function pattern checks for centre of palindrome and sequencing based at location size_t start_loc
//must have functionality to prevent mid sequence duplication of Palindrome 
void checkPattern(const std::string& str, size_t loc, std::vector<Palindrome*>& list, std::mutex& mtx, const int);
#endif // PALINDROME_, H
