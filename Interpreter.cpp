// Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Meat/Meat.h"

void printUsage()
{
    std::cout << "Error: unknown file. Use a valid filename. " << std::endl;
}

int main(int argc, char *argv[])
{
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
