#ifndef PARSE_H_
#define PARSE_H_

#include "JobShop.h"
#include <string>
#include <fstream>

class Parse 
{
public:
	/**
	 * @brief Task constructor with defalt -1 values.
	 * 
	 */
	Parse(int id);

	/**
	 * @brief Task constructor.
	 * 
	 * @param id 
	 */
	// Parse(int machine, int duration,int id);
	
	virtual ~Parse();
	void parseFile(std::string fileName, JobShop shop);

private:
	int id;

};

#endif /* Parse_H_ */
