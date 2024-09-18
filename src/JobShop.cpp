#include "JobShop.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <tgmath.h>

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
	for (auto job : jobList)
	{
		std::cout << job.getIndex() << '\t' << job.getBeginTime() << '\t' << job.getEndTime() << '\t' << job.getTotalDuration() << '\t' << "[" << job.getRunningStatus() << "]" << '\t' << ",";
		for (auto task : job.getTaskList())
		{
			std::cout << "( " << task.getMachine() << " " << task.getDuration() << "), " << "[" << job.getDoneStatus() << "]" << '\n';
		}
	}
	std::cout << "Longest job at index: " << longestJob << std::endl;
	std::cout << "current time = " << currentTime << std::endl;
	std::cout << "===================================================" << std::endl
			  << std::endl;
	// printActiveMachineList();
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
	int size = static_cast<int>(split.size()) / 2;
	for (auto i = 0; i < size; ++i)
	{
		Task t(i, std::stoi(split.at(index)), std::stoi(split.at(index + 1)));
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
	if (job.getBeginTime() == -1)
	{
		job.setBeginTime(currentTime);
	}
	job.setRunningStatus(true);
	activeMachines.push_back(job.getTaskList().at(0).getMachine());
	jobList.at(job.getIndex()) = job;
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
	int size = static_cast<int>(jobList.size());
	while (!finished)
	{
		for (int jobNr = 0; jobNr < size; ++jobNr)
		{
			// check if the job is active
			if (!jobList.at(jobNr).getRunningStatus())
			{
				activateNextJob(jobList.at(jobNr));
			}
			else
			{
				// task finished remove task and find and activate a new task.
				if (jobList.at(jobNr).getTaskList().at(0).getDuration() <= 0)
				{
					removeFirstInLine(jobList.at(jobNr));
					jobList.at(jobNr).setRunningStatus(false);
					for (auto job : jobList)
					{
						activateNextJob(job);
					}
					finished = finishCheck();
				}
			}
		}
		++currentTime;
		// printJobShop();
		// tick all the jobs at once.
		tickAll();
	}
	printResult();
}

void JobShop::activateNextJob(Job incomingJob)
{
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
	int size = static_cast<int>(activeMachines.size());
	for (int i = 0; i < size; ++i)
	{
		if (activeMachines.at(i) == machineNr)
		{
			return true;
		}
	}
	return false;
}

bool JobShop::checkForFasterMachines(Job currentJob)
{
	for (auto job : jobList)
	{
		// check if you are not checking yourself
		if (currentJob.getIndex() != job.getIndex())
		{
			if (!job.getRunningStatus() && !job.getDoneStatus())
			{
				if (currentJob.getTaskList().at(0).getMachine() == job.getTaskList().at(0).getMachine())
				{
					if (currentJob.getRemaining() < job.getRemaining())
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

void JobShop::removeFirstInLine(Job job)
{
	std::vector<Task> helperList = {};
	helperList = job.getTaskList();
	Job j = job;
	int machineNr = job.getTaskList().at(0).getMachine();
	if (job.getTaskList().size() > 1)
	{
		helperList.erase(helperList.begin());
	}
	else
	{
		j.setDone();
		if (j.getEndTime() == -1)
		{
			j.setEndTime(currentTime);
		}

		Task t(-1, -1, -1);
		helperList.at(0) = t;
	}
	j.setTaskList(helperList);
	removeFromActiveMachineList(machineNr);
	jobList.at(j.getIndex()) = j;
}

void JobShop::removeFromActiveMachineList(int machineNr)
{
	int index = 0;
	int onIndex = 0;
	for (auto x : activeMachines)
	{
		if (machineNr == x)
		{
			onIndex = index;
		}
		++index;
	}
	activeMachines.erase(activeMachines.begin() + onIndex);
}

void JobShop::tick(Job job)
{
	Task currentTask = job.getTaskList().at(0);
	currentTask.reduceDuration();
	std::vector<Task> helperList;
	helperList = job.getTaskList();
	helperList.at(0) = currentTask;
	Job j = job;
	j.reduceRemaining();
	j.setTaskList(helperList);
	jobList.at(job.getIndex()) = j;
}
void JobShop::tickAll()
{
	for (auto job : jobList)
	{
		if (job.getRunningStatus())
		{
			tick(job);
		}
	}
}
void JobShop::printResult()
{

	for (auto job : jobList)
	{
		std::cout << job.getIndex() << '\t' << job.getBeginTime() << '\t' << job.getEndTime() << '\n';
	}
}
