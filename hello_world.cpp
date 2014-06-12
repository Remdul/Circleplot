//Need this library to print stuff
#include <iostream>
#include <string>

//So we dont have to type std::string
//every time we want to use a string
using std::string;

//All C++ programs start with main
//It must look exactly like this line
int main(int argc, char *argv[])
{
    string message="Hello World!";
    //std::endl is a newline
    std::cout << message << std::endl;


    //Returning 0 means normal program exit
    return 0;
}
