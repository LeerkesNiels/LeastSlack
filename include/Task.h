#ifndef TASK_H_
#define TASK_H_

class Task
{
public:
	/**
	 * @brief Task constructor with defalt -1 values.
	 * 
	 */
	Task();

	/**
	 * @brief Task constructor.
	 * 
	 * @param machine 
	 * @param duration 
	 * @param id 
	 */
	Task(int machine, int duration,int id);

	/**
	 * @brief Construct a new Task object
	 * 
	 * @param otherTaks 
	 */
	Task(const Task& otherTaks);

	/**
	 * @brief Copy constructor. 
	 * 
	 * @param task other task.
	 * @return Pointer to the new task
	 */
	Task operator=(const Task& task);

	/**
	 * @brief Destroy the Task
	 * 
	 */
	virtual ~Task();

	/**
	 * @brief Get the Duration
	 * 
	 * @return int 
	 */
	int getDuration() const;

	/**
	 * @brief Set the Duration of the task
	 * 
	 * @param duration 
	 */
	void setDuration(const int duration);

	/**
	 * @brief Get the Machine number of the task
	 * 
	 * @return int 
	 */
	int getMachine() const;

	/**
	 * @brief Set the Machine number of the task
	 * 
	 * @param machine 
	 */
	void setMachine(const int machine);

	/**
	 * @brief Get the task Id.
	 *
	 * @return int 
	 */
	int getId() const;

	/**
	 * @brief Reduce the duration of the task by one. 
	 * 
	 */
	void reduceDuration();

private:
	int id;
	int machine;
	int duration;

};

#endif /* TASK_H_ */
