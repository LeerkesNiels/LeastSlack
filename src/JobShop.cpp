#include "JobShop.h"
#include <iostream>
#include <sstream>
#include <cstring>

JobShop::JobShop(int longestJob = 0) : longestJob(longestJob)
{
	amountOfJobs = 0;
	amountOfMachines = 0;
	finished = false;
}

JobShop::~JobShop()
{
}

void JobShop::clearJobShop()
{
	for (auto job : jobList)
	{
		job.getTaskList().clear();
	}
	jobList.clear();
	finished = false;
}

void JobShop::setJobName(std::string name)
{
	this->name = name;
}

void JobShop::printJobShop()
{
	// printActiveMachineList();
	std::cout << "===================================================" << std::endl;
	std::cout << "Job name: " << this->name << std::endl;
	std::cout << "amount of jobs: " << this->amountOfJobs << std::endl
			  << "Amount of machines: " << this->amountOfMachines << std::endl;
	// for loop to print all the data
	for (int i = 0; i < this->jobList.size(); ++i)
	{
		int jobSize = jobList.at(i).getTaskList().size();
		std::cout << jobList.at(i).getIndex() << '\t' << jobList.at(i).getBeginTime() << '\t' << jobList.at(i).getEndTime() << '\t' << jobList.at(i).getTotalDuration() << '\t' << "[" << jobList.at(i).getRunningStatus() << "]" << '\t' << ",";
		for (int y = 0; y < this->jobList.at(i).getTaskList().size(); ++y)
		{
			std::cout << "( " << this->jobList.at(i).getTaskList().at(y).getMachine() << " " << this->jobList.at(i).getTaskList().at(y).getDuration() << "), " << "[" << jobList.at(i).getDoneStatus() << "]";
		}
		std::cout << std::endl;
		// std::cout << i << ",is active : " << jobList.at(i).getRunningStatus();
	}
	std::cout << "Longest job at index: " << longestJob << std::endl;
	std::cout << "current time = " << currentTime << std::endl;
	std::cout << "===================================================" << std::endl
			  << std::endl;
	printActiveMachineList();
}

std::vector<std::string> JobShop::parseString(const std::string &inputString)
{
	std::string cleanedString = inputString;
	std::string replace_spaces = "  ";
	std::string replace_by = " ";

	size_t pos = cleanedString.find(replace_spaces);

	while (pos != std::string::npos)
	{
		cleanedString.replace(pos, replace_spaces.size(), replace_by);
		pos = cleanedString.find(replace_spaces,
								 pos + replace_by.size());
	}

	std::string replace_tabs = "\t";
	std::string replace_by2 = " ";
	size_t pos2 = cleanedString.find(replace_tabs);
	while (pos2 != std::string::npos)
	{
		cleanedString.replace(pos2, replace_tabs.size(), replace_by2);
		pos2 = cleanedString.find(replace_tabs,
								  pos2 + replace_by2.size());
	}
	std::vector<std::string> split;
	std::stringstream ss(cleanedString);
	std::string item;
	char delim = ' ';
	while (getline(ss, item, delim))
	{
		split.push_back(item);
	}
	int index = 0;
	for (auto x : split)
	{
		if (x.size() == 0)
		{
			split.erase(split.begin() + index);
		}
		++index;
	}
	return split;
}

void JobShop::setJobDetails(const std::string &detailString)
{
	std::vector<std::string> split = parseString(detailString);
	this->amountOfJobs = std::stoi(split.at(0));
	this->amountOfMachines = std::stoi(split.at(1));
}

int JobShop::setJobList(const std::string &input, int jobNr)
{
	std::vector<std::string> split = parseString(input);
	// std::cout <<"input in setJobList: "<< input << std::endl;
	std::vector<Task> taskList;
	int index = 0;
	for (int i = 0; i < split.size() / 2; ++i)
	{
		Task t(std::stoi(split.at(index)), std::stoi(split.at(index + 1)), i);
		taskList.push_back(t);
		index += 2;
	}
	Job job(taskList);
	job.setIndex(jobNr);
	jobList.push_back(job);
	return 0;
}

void JobShop::calcLongestJob()
{
	// setLongestJob(0);
	int i = 0;
	int longest = 0;
	for (auto x : jobList)
	{
		if (jobList.at(longest).getTotalDuration() < x.getTotalDuration())
		{
			longest = i;
		}
		++i;
	}
	setLongestJob(longest);
}

int JobShop::getLongestJobIndex() const
{
	return longestJob;
}

void JobShop::setLongestJob(int longestJob)
{
	this->longestJob = longestJob;
}

void JobShop::AddToJobList(Job j)
{
	jobList.push_back(j);
}

void JobShop::activateJob(Job job)
{
	std::cout << "setting the following job on active:" << job.getIndex() << std::endl;
	std::cout << "my machine nr at index 0 = " << job.getTaskList().at(0).getMachine() << std::endl;

	if (job.getBeginTime() == -1)
	{
		job.setBeginTime(currentTime);
	}
	job.setRunningStatus(true);
	activeMachines.push_back(job.getTaskList().at(0).getMachine());
	jobList.at(job.getIndex()) = job;
	tick(job);
}

void JobShop::printActiveMachineList()
{
	std::cout << "the following machines are active: " << std::endl;
	for (auto x : activeMachines)
	{
		std::cout << x << ",";
	}
	std::cout << std::endl;
}

void JobShop::schedule()
{
	int loops = 0;
	// while (loops < 10)
	while (!finished)
	{
		int index = 0;
		for (int jobNr = 0; jobNr < jobList.size(); ++jobNr)
		{
			// check if the job is already active
			if (!jobList.at(jobNr).getRunningStatus())
			{
				activateNextJob(jobList.at(jobNr));
			}
			else
			{
				if (jobList.at(jobNr).getTaskList().at(0).getDuration() <= 0)
				{
					removeFirstInLine(jobList.at(jobNr));
					jobList.at(jobNr).setRunningStatus(false);
					activateNextJob(jobList.at(jobNr));
					for (auto job : jobList)
					{
						activateNextJob(job);
					}
					finished = finishCheck();
				}
				else
				{
					tick(jobList.at(jobNr));
				}
			}
			++index;
		}
		++loops;
		printJobShop();
		++currentTime;
	}
	std::cout << "exiting the schedule function!" << std::endl;
}
void JobShop::activateNextJob(Job incomingJob)
{
	int i = 0;
	int machineNr = incomingJob.getTaskList().at(0).getMachine();
	for (auto job : jobList)
	{
		// job not done and not currently running.
		if (!job.getRunningStatus() && !job.getDoneStatus())
		{
			// check if the machine is already in the active machine list.
			if (!checkRunningMachine(machineNr))
			{
				// check if there are other machines that have a longer duration
				if (checkForFasterMachines(incomingJob))
				{
					activateJob(incomingJob);
				}
			}
		}
		++i;
	}
}
bool JobShop::finishCheck()
{
	for (auto job : jobList)
	{
		if (!job.getDoneStatus())
		{
			return false;
		}
	}
	return true;
}

bool JobShop::checkRunningMachine(int machineNr)
{
	// printActiveMachineList();
	// std::cout << "incoming nr : " << machineNr << std::endl;

	for (int i = 0; i < activeMachines.size(); ++i)
	{
		// std::cout << "machineNr: " << machineNr << " == " << machine << std::endl;
		if (activeMachines.at(i) == machineNr)
		{
			// std::cout << "returning true;" << std::endl;
			return true;
		}
	}
	// std::cout << "returning false;" << std::endl;
	return false;
}

bool JobShop::checkForFasterMachines(Job currentJob)
{
	int index = 0;
	// std::cout << "my total duration = " << currentJob.getTotalDuration() << std::endl;
	for (auto job : jobList)
	{
		// check if you are not checking yourself
		if (currentJob.getIndex() != job.getIndex())
		{
			if (!job.getRunningStatus() && !job.getDoneStatus())
			{
				if (currentJob.getTaskList().at(0).getMachine() == job.getTaskList().at(0).getMachine())
				{
					if (currentJob.getTotalDuration() < job.getTotalDuration())
					{
						// i am not the one with the longest duration
						// std::cout << "found longer job at index" << job.getIndex() << std::endl;
						return false;
					}
				}
			}
		}
	}
	// std::cout << "check for faster returning false with index: " << currentJob.getIndex() << std::endl;
	// i am the longest one
	return true;
}

void JobShop::removeFirstInLine(Job job)
{
	std::vector<Task> helperList = {};
	helperList = job.getTaskList();
	Job j = job;
	int machineNr = job.getTaskList().at(0).getMachine();
	// std::cout << "removing the following machine nr: " << helperList.at(0).getMachine() << std::endl;
	std::cout << "size = " << job.getTaskList().size() << std::endl;
	if (job.getTaskList().size() > 1)
	{
		helperList.erase(helperList.begin());
	}
	else
	{
		std::cout << "current time when ending the whole job = " << currentTime << std::endl;

		std::cout << "size of j.taskList= " << j.getTaskList().size() << std::endl;
		j.setDone();
		j.setEndTime(currentTime);
		Task t(-1, -1, -1);
		helperList.at(0) = t;
	}
	j.setTaskList(helperList);
	removeFromActiveMachineList(machineNr);
	jobList.at(j.getIndex()) = j;
}

void JobShop::removeFromActiveMachineList(int machineNr)
{
	// std::cout << "before removing:" << machineNr << std::endl;
	// printActiveMachineList();
	int index = 0;
	int onIndex = 0;
	for (auto x : activeMachines)
	{
		if (machineNr == activeMachines.at(index))
		{
			onIndex = index;
		}
		++index;
	}
	// std::cout << "removing at index:" << onIndex << std::endl;
	activeMachines.erase(activeMachines.begin() + onIndex);
	// std::cout << "after removing:" << std::endl;
	// printActiveMachineList();
}

void JobShop::tick(Job job)
{
	Task currentTask = job.getTaskList().at(0);
	currentTask.reduceDuration();
	std::vector<Task> helperList;
	helperList = job.getTaskList();
	helperList.at(0) = currentTask;
	Job j = job;
	j.setTaskList(helperList);
	jobList.at(job.getIndex()) = j;
}

void JobShop::makeLeastSlack()
{
}
