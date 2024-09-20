#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "JobShop.h"
#include "Job.h"
#include "Task.h"
void parseFile(std::string);

JobShop shoppie(0);

int main(int argc, char **argv)
{

	if (argc == 2)
		parseFile(argv[1]);
	else
		std::cout << "invalid amount of arguments. " << '\n';
	// shoppie.makeLeastSlack();

	return 0;
}

void parseFile(std::string filename)
{
	std::string line;
	std::ifstream infile;
	int lineNr = -2;
	int jobNr = 0;
	infile.open(filename);

	while (!infile.eof()) // To get you all the lines.
	{
		getline(infile, line); // Saves the line in STRING.
		if (line.size() == 0)
		{
			shoppie.calcLongestJob();
			shoppie.schedule();
			shoppie.clearJobShop();
			jobNr = 0;
			lineNr = -3;
		}
		else
		{
			if (lineNr == -2)
			{
				shoppie.setJobName(line);
			}
			else if (lineNr == -1)
			{
				shoppie.setJobDetails(line);
			}
			else
			{
				shoppie.setJobList(line, jobNr);
				++jobNr;
			}
		}
		++lineNr;
	}
	infile.close();
}