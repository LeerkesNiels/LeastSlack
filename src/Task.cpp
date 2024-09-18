/*
 * Task.cpp
 *
 *  Created on: 1 mrt. 2021
 *      Author: na_le
 */

#include "Task.h"
#include <iostream>

Task::Task()
{
	machine = 0;
	duration = 0;
	duration = 0;
	finished = false;
}

Task::Task(int id, int machine, int duration) : id(id), machine(machine), duration(duration)
{
	finished = false;
}

Task::~Task()
{
}
Task::Task(const Task &otherTask)
{
	this->id = otherTask.id;
	this->machine = otherTask.machine;
	this->duration = otherTask.duration;
	this->finished = otherTask.finished;
}
Task Task::operator=(Task const &newTask)
{
	this->id = newTask.id;
	this->machine = newTask.machine;
	this->duration = newTask.duration;

	return *this;
}

void Task::reduceDuration()
{
	this->duration = duration - 1;
}

int Task::getDuration() const
{
	return duration;
}

void Task::setDuration(int duration)
{
	this->duration = duration;
}

int Task::getMachine() const
{
	return machine;
}

void Task::setMachine(int machine)
{
	this->machine = machine;
}

int Task::getId() const
{
	return id;
}