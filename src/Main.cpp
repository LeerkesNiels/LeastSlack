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

	char name[256];

	std::cout << "Enter the file name:";
	std::cin.getline(name, 256);
	std::cout << name << std::endl;
	parseFile(name);
	shoppie.makeLeastSlack();

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
		// std::cout <<lineNr <<" raw: "<< line <<std::endl;
		if (line.size() == 0)
		{
			shoppie.calcLongestJob();
			shoppie.schedule();

			std::cout << "finished the scheduling" << line << std::endl;
			shoppie.printJobShop();
			// shoppie.clearJobShop();
			jobNr = 0;
			lineNr = -3;
		}
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
		++lineNr;
		// std::cout << amoundOfLines << " : "<< line << std::endl;
		// std::cout << "size: " << wholeLine.size() << std::endl;
	}
	// 	switch (eolCounter)
	// 	{
	// 	case 0:
	// 		std::cout << "titlel:" << std::endl;
	// 		break;
	// 	case 1:
	// 		std::cout << "hoeveel bj hoeveel:" << std::endl;
	// 		std::string s = "";
	// 		int i = 0;
	// 		for (auto x : wholeLine):
	// 		{

	// 			std::cout << "couter at: " << i << std::endl;
	// 			if (x == ' ')
	// 			{
	// 				s = "";
	// 				++counterForParse;
	// 			}
	// 			else
	// 			{
	// 				s += x;
	// 				if (counterForParse == 0)
	// 				{
	// 					int tempString = stoi(s);
	// 					amountOfJob = tempString;
	// 				}
	// 				else
	// 				{
	// 					int tempString = stoi(s);
	// 					amountOfMachines = tempString;
	// 				}
	// 			}
	// 			++i;
	// 		}
	// 		counterForParse = 0;
	// 		s= "";
	// 		std::cout << "amount of machines: " << amountOfMachines
	// 				<< std::endl;
	// 		std::cout << "amount of jobs: " << amountOfJob << std::endl;
	// 		counterForParse = 0;
	// 		break;
	// 	}

	// 	if (eolCounter > 1 && eolCounter < 2 + amountOfJob)
	// 	{
	// 		std::string s2 = "";
	// 		for (auto x : wholeLine)
	// 		{
	// 			if (x == ' ')
	// 			{

	// 				int tempString2 = stoi(s2);
	// 				helpVector1.push_back(tempString2);
	// 				s2 = "";
	// 			}
	// 			else
	// 			{
	// 				s2 += x;
	// 			}
	// 		}
	// 		int tempString2 = stoi(s2);
	// 		helpVector1.push_back(tempString2);
	// 		s2 = "";
	// 		std::vector<Task> jobList;
	// 		for (int i = 0; i < amountOfMachines * 2; i += 2)
	// 		{
	// 			Task task(helpVector1.at(i), helpVector1.at(i + 1));
	// 			jobList.push_back(task);
	// 		}
	// 		Job job(jobList);
	// 		shoppie.AddToJoblist(job);
	// 		helpVector1.clear();
	// 	}
	// 	if (eolCounter > amountOfJob + 1)
	// 	{
	// 		eolCounter = -1;
	// 		amountOfJob = 0;
	// 		amountOfMachines = 0;
	// 	}
	// 	std::cout << wholeLine << std::endl; // Prints our STRING.
	// 	++eolCounter;
	// }
	infile.close();
}