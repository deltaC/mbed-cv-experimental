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
								GPIO_Port* port ) : n_proc(n_proc), processes(processes), port(port) {}

void CyclicExecutor::startMeasure_(int proc_number) {
	this->port->pinToggle(proc_number);
}

void CyclicExecutor::endMeasure_(int proc_number) {
	this->port->pinToggle(proc_number);
}

void CyclicExecutor::runIteration() {
	for (int i = 0; i < this->n_proc; ++i) {
		this->startMeasure_(i);
		this->processes[i].run();
		this->endMeasure_(i);
		for (int j = 0; j < 1000; ++j)
			asm("nop");
	}
}
