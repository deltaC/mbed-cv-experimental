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

#endif /* CYCLIC_EXECUTOR_PROCESSES_HPP_ */
