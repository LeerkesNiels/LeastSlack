#ifndef JOBSHOP_H_
#define JOBSHOP_H_

#include "Job.h"
#include <iostream>
#include <string>
#include <vector>

class JobShop
{
public:
	JobShop(int longestJob);
	virtual ~JobShop();
	void calcLongestJob();
	void setLongestJob(int longestJob);
	void AddToJoblist(Job j);
	int getLongestJobIndex() const;
	void makeLeastSlack();

	void clearJobShop();
	std::vector<std::string> parseString(const std::string &inputString);
	void setJobName(std::string name);
	void setJobDetails(const std::string &detailString);
	int setJobList(const std::string &input);
	void printJobShop();
	void schedule();
	void tick(Job job, int index);
	void removeFirstInLine(Job job, int index);
	void activateJob(int jobNr);
	bool checkRunningMachine(int machineNr);
	void removeFromActiveMachineList(int machineNr);
	void printActiveMachineList();
	bool checkForFasterMachines(int machieNr, Job job);
	bool finishCheck();
	void checkAvailableJobs(int machineNr);

private:
	int amountOfMachines;
	int amountOfJobs;
	int currentTime;
	std::string name;
	int longestJob;
	std::vector<Job> jobList;
	bool finished;

	std::vector<int> activeMachines;
};

#endif /* JOBSHOP_H_ */
