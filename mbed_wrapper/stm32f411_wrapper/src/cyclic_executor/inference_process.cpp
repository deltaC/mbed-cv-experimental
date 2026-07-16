#include "processes.hpp"
#include "../net/net.h"
#include "../../data/prepared/data.h"

ProcessInference::ProcessInference () {
    this->nn_output = 0;
}

void ProcessInference::run() {
	 inference(flatten_image, &(this->nn_output));
}
