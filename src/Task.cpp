#include "Task.h"
#include <iostream>

Task::Task()
{
	machine = -1;
	duration = -1;
	id = -1;
}

Task::Task(int id, int machine, int duration) : id(id), machine(machine), duration(duration)
{
}

Task::~Task()
{
}

Task::Task(const Task &otherTask)
{
	this->id = otherTask.id;
	this->machine = otherTask.machine;
	this->duration = otherTask.duration;
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
	this->duration--;
}

int Task::getDuration() const
{
	return duration;
}

void Task::setDuration(const int duration)
{
	this->duration = duration;
}

int Task::getMachine() const
{
	return machine;
}

void Task::setMachine(const int machine)
{
	this->machine = machine;
}

int Task::getId() const
{
	return id;
}