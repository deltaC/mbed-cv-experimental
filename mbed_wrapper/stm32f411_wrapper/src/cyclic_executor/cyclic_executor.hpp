/*
 * cyclic_executor.hpp
 *
 *  Created on: Jun 24, 2026
 *      Author: g_phaidros
 */

#ifndef CYCLIC_EXECUTOR_CYCLIC_EXECUTOR_HPP_
#define CYCLIC_EXECUTOR_CYCLIC_EXECUTOR_HPP_

#include "processes.hpp"
#include "../periphery/periphery.hpp"

class CyclicExecutor {
	int n_proc;
	IProcess* processes;
	GPIO_port* port;

	void start_measure_(int proc_number);
	void end_measure_(int proc_number);

public:
	CyclicExecutor(int n_proc, IProcess* processes, GPIO_port* port);

	void run_iteration();
};

#endif /* CYCLIC_EXECUTOR_CYCLIC_EXECUTOR_HPP_ */
