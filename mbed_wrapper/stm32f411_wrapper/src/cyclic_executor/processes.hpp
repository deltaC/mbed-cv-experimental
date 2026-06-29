/*
 * processes.hpp
 *
 *  Created on: Jun 24, 2026
 *      Author: g_phaidros
 */

#ifndef CYCLIC_EXECUTOR_PROCESSES_HPP_
#define CYCLIC_EXECUTOR_PROCESSES_HPP_

class IProcess {
public:
	virtual ~IProcess() = default;

	virtual void run() = 0;
};

class ProcessInference : public IProcess {
	float nn_output; 
public:
	ProcessInference();
	void run() override;
};

#endif /* CYCLIC_EXECUTOR_PROCESSES_HPP_ */
