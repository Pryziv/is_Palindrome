#include "Palindrome.h"
std::ostream& operator<<(std::ostream& os, const Palindrome& obj)
{
    os<<obj.str<<" "<<std::endl
        <<std::setw(5)<<""<<"loc:"<<std::setw(3)<<obj.start_loc<<", "
                          <<"len:"<<std::setw(3)<<obj.length<<std::endl;
    return os;
}

bool Palindrome::operator <(const Palindrome& other)
{
    //this < other?
    if(this->length == other.length){
        return (this->str < other.str);
    }else{
        return(this->length < other.length);
    };
}

bool Palindrome::operator >(const Palindrome& other)
{
    if(this->length == other.length){
        return (this->str > other.str);
    }else{
        return(this->length > other.length);
    };
}

bool Palindrome::operator ==(const Palindrome& other)
{
    //return(this->str == other.str);
    if(this->start_loc != other.start_loc){
        return false;
    }
    if(this->length != other.length){
        return false;
    }
    return (this->str == other.str);
}

Palindrome::~Palindrome()
{
}

//this is the sort priority for the vector
bool ptrToPalindrome(Palindrome* p, const Palindrome* p2){
    return (*p > *p2);
}


Palindrome* getPalindrome(const std::string& str, std::string::const_iterator left, std::string::const_iterator right){
    while(right != str.end() && left != str.begin()){
        left--;
        right++;
        if(std::toupper(*left) != std::toupper(*right)){
            //end found move back one and exit loop
            left++;
            right--;
            break;
        }
    }
    int start_loc = std::distance(str.begin(),left);
//TODO clean up future
    Palindrome* P = new Palindrome( str.substr(start_loc, std::distance(left,right) + 1), start_loc );
    return P;
}

void checkPattern(const std::string& str, size_t loc, std::vector<Palindrome*>& list, std::mutex& mtx, const int CONCURRENCY){
    while(loc < str.length() ){
        std::string::const_iterator at = str.begin()+loc;
        
        //check for |a|a
        std::string::const_iterator next = at+1;
        if( std::toupper(*at) == std::toupper(*next) ){
            //check for a|a|a for mid sequence 
            std::string::const_iterator before = at-1;
            if( std::toupper(*before) == std::toupper(*at) ){ //mid sequence abandon
                return;
            }else{
                std::string::const_iterator after = next+1;
                if( std::toupper(*after) == std::toupper(*at) ){//found sequence process as such
                    while( next != str.end() ){
                        next++;
                        if(std::toupper(*next) != std::toupper(*at)){//we reached end of sequence
                            next--;
                            break;
                        }
                    }
                }//end of sequence processing
                Palindrome* p = getPalindrome(str, at, next);
                mtx.lock();
                list.push_back ( p );
                mtx.unlock();
            }
        }else{
            //check for |a|b|a|
            std::string::const_iterator after = next+1;
            if( std::toupper(*after) == std::toupper(*at) ){
                Palindrome* p =  getPalindrome(str, at, after);
                mtx.lock();
                list.push_back ( p );
                mtx.unlock();
            }
        }
    loc+=CONCURRENCY;
    }  
}