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
#include <iostream>

#include "Task.h"

class Job
{
public:
	/**
	* @brief Construct a new Job 
	*   
	* @param taskList Sets a vector list of tasks as the tasklist
	*/
	Job(const std::vector<Task> taskList);
	/**
	 * @brief clear the tasklist before destroying the job.
	 * 
	 */
	virtual ~Job();
	/**
	 * @brief Construct a new Job object
	 * 
	 * @param otherJob 
	 */
	Job(const Job &otherJob);

	/**
	 * @brief copy constructor for job.
	 * 
	 * @param job the incomming job.
	 * @return The new job object.  
	 */
	Job operator=(const Job &job);

	/**
	 * @brief Get the Total Duration for this Job.
	 * 
	 * @return int 
	 */
	int getTotalDuration() const;

	/**
	 * @brief Set the Total Duration 
	 * 
	 * @param totalDuration 
	 */
	void setTotalDuration(const int totalDuration);

	/**
	 * @brief Get the Begin Time 
	 * 
	 * @return int 
	 */
	int getBeginTime() const;
	
	/**
	 * @brief Set the Begin Time
	 * 
	 * @param beginTime 
	 */
	void setBeginTime(const int beginTime);

	/**
	 * @brief Get the End Time
	 * 
	 * @return int 
	 */
	int getEndTime() const;

	/**
	 * @brief Set the End Time 
	 * 
	 * @param endTime 
	 */
	void setEndTime(int endTime);
	
	/**
	 * @brief Get the Running Status
	 * 
	 * @return bool, true if the job is currently active false for inactive. 
	 */
	bool getRunningStatus();

	/**
	 * @brief Set the running status. 
	 * 
	 * @param newStatus (true)
	 */
	void setRunningStatus(const bool newStatus);

	/**
	 * @brief Get the Task List
	 * 
	 * @return taskList
	 */
	const std::vector<Task> getTaskList();
	
	/**
	 * @brief Replace the current task list with the incomming one. 
	 * 
	 * @param taskList 
	 */
	void setTaskList(const std::vector<Task> taskList);

	/**
	 * @brief Check if the job is already started.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isBegon();

	/**
	 * @brief set done flag.
	 * 
	 */
	void setDone();

	/**
	 * @brief print all the tasks in the job.
	 * 
	 */
	void printJob();

	/**
	 * @brief get the done status for the job.
	 * 
	 */
	bool getDoneStatus();
	
	/**
	 * @brief set the job index in the jobshop.
	 * 
	 * @param newIndex 
	 */
	void setIndex(int newIndex);

	/**
	 * @brief get the index of the job in the jobshop.
	 * 
	 * @return int 
	 */
	int getIndex();

	/**
	 * @brief Get the Remaining time left of the job.
	 * 
	 * @return int 
	 */
	int getRemaining();

	/**
	 * @brief recude the remaining time of the job by 1. 
	 * 
	 */
	void reduceRemaining();

private:
	int index;
	
	int beginTime;
	int endTime;

	int totalDuration;
	int remainingDuration;
	
	std::vector<Task> taskList;
	
	bool isRunning;
	bool isDone;
	bool begon;
};

#endif /* JOB_H_ */
