#include <fstream>
#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include "Palindrome.h"
#include <string>
#include <algorithm>

const int TITLE_PADDING {10};
const int LINE_PADDING {48};
const int MENU_PADDING {8};
const int OFFSET_PADDING {4};

void print_menu();
void print_list(const std::vector<Palindrome*>&);
void process_string(const std::string&, std::vector<Palindrome*>&, std::mutex&, const int);

int main(int argc, char **argv)
{
    //set up important objects
    std::mutex g_mtx;
	const int CONCURRENCY = std::thread::hardware_concurrency()-1; //the negative one is for safety
    std::vector<Palindrome*> list;
    std::ifstream in_file;
    std::string line;
    
    bool time_task {false};
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    bool run {true};
    int task {0};
    std::string user_input;
    
    std::cout<<std::setfill('*')<<std::setw(TITLE_PADDING)<<""<<"Welcome To U Palindrome 2022"<<std::setw(TITLE_PADDING)<<""<<std::endl<<std::endl<<std::setfill(' ');
    std::cout<<"Please input the integer value associated with your request (1-5)"<<std::endl;
    
    //gui loop
    while(run == true){
        print_menu();
        std::cin>>task;
        switch(task){
            case 1:{
                std::cout<<"Input File address >>";
                std::cin>>line;
                in_file.open( line );
                if(in_file){
                    if(time_task){
                        start = std::chrono::steady_clock::now();
                    }
                    while(getline(in_file,line)){
                        process_string(line, list, g_mtx, CONCURRENCY);
                    }
                    std::sort(list.begin(), list.end(), ptrToPalindrome);
                    if(time_task){
                        end = std::chrono::steady_clock::now();
                        std::cout<<"time_task: "<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<std::endl;
                    }
                    in_file.close();
                    std::cout<<std::setw(OFFSET_PADDING)<<""<<"Succussfully Read from file"<<std::endl;
                }else{
                    std::cout<<"Error: could not read from test file, does file exist?, check format of name for IDE or compiler"<<std::endl;
                }
                
                break;
            }
            case 2:{
                std::cout<<"Awaiting input: >>";
                std::cin>>user_input;
                if(time_task){
                    start = std::chrono::steady_clock::now();
                }
                process_string(user_input, list, g_mtx, CONCURRENCY);
                std::sort(list.begin(), list.end(), ptrToPalindrome);
                if(time_task){
                    end = std::chrono::steady_clock::now();
                    std::cout<<"time_task: "<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<" milliseconds"<<std::endl;
                }
                break;
            }
            case 3:{
                print_list(list);
                break;
            }
            case 4:{
                time_task = !(time_task);
                if(time_task){std::cout<<"time_task: ENABLED"<<std::endl;}else{std::cout<<"time_task: DISABLED"<<std::endl;}
                break;
            }
            case 5:{
                run = false;
                break;
            }
            default:
                std::cout<<std::setw(OFFSET_PADDING)<<""<<"ERROR::User input not accepted returning to main menu"<<std::endl<<std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                break;
        }
    }
    
}

//divide up the work by spawning threads and passing to checkPattern which will pass to getPalindrome
void process_string(const std::string& str, std::vector<Palindrome*>& list, std::mutex& mtx, const int CONCURRENCY){
    std::vector<std::thread> threads;
    size_t temp = 0;

    if( str.length()>30){
        for(auto i{0};i<CONCURRENCY;i++){
        threads.push_back( std::thread(checkPattern, ref(str), temp+i, ref(list), ref(mtx), CONCURRENCY) );
        }
        for(auto i=0;i<CONCURRENCY;i++){
            threads[i].join();
        }
    }else{
        checkPattern(str, 0, list, mtx, 1);
    }
    return;
}

//print the gui main menu
void print_menu(){
    std::cout<<std::setw(OFFSET_PADDING)<<""<<"Main Menu:"<<std::endl
            <<std::setw(MENU_PADDING)<<""<<"1. Read From File"<<std::endl
            <<std::setw(MENU_PADDING)<<""<<"2. Read From User"<<std::endl
            <<std::setw(MENU_PADDING)<<""<<"3. Print List"<<std::endl
            <<std::setw(MENU_PADDING)<<""<<"4. Toggle time_task"<<std::endl
            <<std::setw(MENU_PADDING)<<""<<"5. Exit"<<std::endl<<std::endl
            <<">>";
    return;
}

//print the stored list of Palindromes
void print_list(const std::vector<Palindrome*>& list){
    std::cout<<std::setfill('*')<<std::setw(TITLE_PADDING)<<""<<"Printing List of Palindromes"<<std::setw(TITLE_PADDING)<<""<<std::endl<<std::setfill(' ');
    for(auto member:list){
        std::cout<<*member<<std::endl;
    }
    std::cout<<std::setfill('*')<<std::setw(LINE_PADDING)<<""<<std::endl<<std::endl<<std::setfill(' ');
}