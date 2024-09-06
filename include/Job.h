/*
 * Job.h
 *
 *  Created on: 1 mrt. 2021
 *      Author: na_le
 */

#ifndef JOB_H_
#define JOB_H_

#include <vector>
#include <string>
#include "Task.h"

class Job
{
public:
	Job(std::vector<Task> jobList);
	virtual ~Job();
	Job(const Job &otherJob);
	Job operator=(const Job &job);
	int getTotalDuration() const;
	void setTotalDuration(int totalDuration);
	int calcTotalDuration(std::vector<Task> jobList);
	void addTOJobList();
	// begintime
	int getBeginTime() const;
	void setBeginTime(int beginTime);
	// endtime
	int getEndTime() const;
	void setEndTime(int endTime);
	// currentTime
	int getCurrentTime() const;
	void setCurrentTime(int currentTime);
	bool getRunningStatus();
	void setRunningStatus(bool newStatus);

	std::vector<Task> getTaskList();
	void setTaskList(std::vector<Task> taskList);
	bool isBegon();
	void printJob();

	void setDone();
	bool getDoneStatus();
	void setIndex(int newIndex);
	int getIndex();
	int getRemaining();
	void reduceRemaining();

private:
	std::string name;
	int beginTime;
	int endTime;
	std::vector<Task> taskList;
	int totalDuration;
	int remainingDuration;
	bool isRunning;
	bool isDone;
	bool begon;
	int index;
};

#endif /* JOB_H_ */
