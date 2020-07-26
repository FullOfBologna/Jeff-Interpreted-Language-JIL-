#include "JeffFile.h"

JeffFile::JeffFile(const std::string& fileName) :
	m_absoluteFileName(fileName),
	m_outputLine(""),
	m_fileNameSet(false),
	m_linePosition(0)
{
	if (fileExists(fileName))
	{
		m_fileNameSet = true;
	}
	else
	{
		std::cout << "Error: Unable to find " << fileName << std::endl;
	}
}

JeffFile::~JeffFile()
{

}

void JeffFile::startReading()
{
	m_file = std::fstream(m_absoluteFileName.c_str(), std::ios::in);

	//m_file.open(m_absoluteFileName.c_str(), std::ios::out);
	m_file.seekg(0);

}

Position JeffFile::getPosition()
{
	return m_linePosition;
}

void JeffFile::setPosition(Position inputPosition)
{
	m_linePosition = inputPosition;

	if (m_file.is_open())
	{
		m_file.seekg(m_linePosition);
	}
}

bool JeffFile::getLine(std::string& outputLine)
{
	char tempCharBuffer[256];

	if (!m_file.eof())
	{
		m_file.getline(tempCharBuffer, 256, '\n');

		m_linePosition++;
	}
	else
	{
		return false;
	}
	
	std::string tempOutString(tempCharBuffer);

	outputLine = tempOutString;

	return true;
}

