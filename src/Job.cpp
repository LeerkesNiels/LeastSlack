/*
 * Job.cpp
 *
 *  Created on: 1 mrt. 2021
 *      Author: na_le
 */

#include "Job.h"
#include <iostream>

Job::Job(std::vector<Task> jobList) : beginTime(-1), endTime(0), taskList(jobList)
{
	int totalDuration = 0;
	for (auto x : jobList)
	{
		totalDuration += x.getDuration();
	}
	this->totalDuration = totalDuration;
	isRunning = false;
	begon = false;
	isDone = false;
}

Job::~Job()
{
	// TODO Auto-generated destructor stub
}

Job::Job(const Job &otherJob)
{
	this->name = otherJob.name;
	this->beginTime = otherJob.beginTime;
	this->endTime = otherJob.endTime;
	this->taskList = otherJob.taskList;
	this->totalDuration = otherJob.totalDuration;
	this->isRunning = otherJob.isRunning;
	this->begon = otherJob.begon;
	this->isDone = otherJob.isDone;
	this->index = otherJob.index;
}
Job Job::operator=(Job const &otherJob)
{
	this->name = otherJob.name;
	this->beginTime = otherJob.beginTime;
	this->endTime = otherJob.endTime;
	this->taskList = otherJob.taskList;
	this->totalDuration = otherJob.totalDuration;
	this->isRunning = otherJob.isRunning;
	this->begon = otherJob.begon;
	this->isDone = otherJob.isDone;
	this->index = otherJob.index;
	return *this;
}

std::vector<Task> Job::getTaskList()
{
	return taskList;
}

int Job::getTotalDuration() const
{
	return totalDuration;
}

void Job::setTotalDuration(int totalDuration)
{
	this->totalDuration = totalDuration;
}

int Job::getBeginTime() const
{
	return beginTime;
}

void Job::setBeginTime(int beginTime)
{
	this->beginTime = beginTime;
}

int Job::getEndTime() const
{
	return endTime;
}

void Job::setEndTime(int endTime)
{
	this->endTime = endTime;
}

void Job::setRunningStatus(bool newStatus)
{
	this->isRunning = newStatus;
}

bool Job::getRunningStatus()
{
	return this->isRunning;
}

void Job::setTaskList(std::vector<Task> taskList)
{
	this->taskList = taskList;
}

void Job::printJob()
{
	for (auto task : taskList)
	{
		std::cout << "(" << task.getMachine() << " " << task.getDuration() << ")";
	}
	std::cout << std::endl;
}

bool Job::isBegon()
{
	return begon;
}

void Job::setDone()
{
	this->isDone = true;
}

bool Job::getDoneStatus()
{
	return isDone;
}

void Job::setIndex(int newIndex)
{
	this->index = newIndex;
}

int Job::getIndex()
{
	return this->index;
}