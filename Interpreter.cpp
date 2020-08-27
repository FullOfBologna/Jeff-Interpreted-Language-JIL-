// Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>

#include "Meat/Meat.h"

//**** Used in the print function to determine line and file ****//
#define STRX(x) #x
#define TOSTRING(x) STRX(x)
#define info __FILE__ ": " TOSTRING(__LINE__)   // info contains the information of the file and line
void print(const char* locationInfo, std::string msg)
{
    const char* c = msg.c_str();
    printf("%s: %s\n", locationInfo, c);
}

void printUsage()
{
    std::cout << "Error: unknown file. Use a valid filename. " << std::endl;
}

int main(int argc, char *argv[])
{
    print(info, "test");
    if (argc != 2)
    {
        printUsage();

        return 0;
    }

    std::string fileName;

    fileName = argv[1];

    std::cout << "Input filename:" << fileName << std::endl;

    Meat meat;

    meat.setScript(fileName);

    meat.readFile();
    return 0;
}
