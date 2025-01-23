#include "Parse.h"
#include <iostream>

Parse::Parse(int id) : id(id)
{
}

Parse::~Parse()
{
}

void Parse::parseFile(std::string fileName, JobShop shop)
{
	std::string line;
	std::ifstream infile;
	int lineNr = -2;
	int jobNr = 0;
	infile.open(fileName);
	bool prevLineEOL = false;
	while (!infile.eof()) // To get you all the lines.
	{
		getline(infile, line); // Saves the line in STRING.
		if (line.size() == 0)
		{
			if(!prevLineEOL)
			{
				prevLineEOL = true;
				shop.calcLongestJob();
				shop.schedule();
				shop.clearJobShop();
				jobNr = 0;
				lineNr = -3;
			}else
			{
				lineNr = -3;
			}
		}
		else
		{
			prevLineEOL = false;
			if (lineNr == -2)
			{
				shop.setJobName(line);
			}
			else if (lineNr == -1)
			{
				shop.setJobDetails(line);
			}
			else
			{
				shop.setJobList(line, jobNr);
				++jobNr;
			}
		}
		++lineNr;
	}
	infile.close();
}
