#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

#include "../Utils/CommonIncludes.h"

//This creates a JeffFile object which stores the position of the interpreting script.
// and other relevant data. 


class JeffFile
{
public:
	JeffFile(const std::string& fileName);
	~JeffFile();

	//Opens the file if fileName is set. 
	// Sets position to 0. 

	void startReading();

	Position getPosition();
	void setPosition(Position pos);

	// Path should include the fileName
	std::string getPathName();
	void setPathName(const std::string& path);

	//Increments position in file, and returns the next string in the file. 
	//
	// returns bool on valid read. 
	bool getLine(std::string&);

private:

	//Includes filename with the path name. 
	std::string m_absoluteFileName;
	std::string m_outputLine;
		
	bool m_fileNameSet;

	std::fstream m_file;
	Position m_linePosition;
};

