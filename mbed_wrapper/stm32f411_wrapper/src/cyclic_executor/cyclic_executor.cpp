/*
 * cyclic_executor.cpp
 *
 *  Created on: Jun 24, 2026
 *      Author: g_phaidros
 */

#include "cyclic_executor.hpp"
#include "../periphery/periphery.hpp"


CyclicExecutor::CyclicExecutor(	int n_proc,
								IProcess* processes,
								GPIO_port* port ) : n_proc(n_proc), processes(processes), port(port) {}

void CyclicExecutor::start_measure_(int proc_number) {
	this->port->pin_toggle(proc_number);
}

void CyclicExecutor::end_measure_(int proc_number) {
	this->port->pin_toggle(proc_number);
}

void CyclicExecutor::run_iteration() {
	for (int i = 0; i < this->n_proc; ++i) {
		this->start_measure_(i);
		this->processes[i].run();
		this->end_measure_(i);
		for (int j = 0; j < 1000; ++j)
			asm("nop");
	}
}
