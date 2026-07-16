"""
GENERATION
"""
from act_funcs import *
from layers import *
from weights import *
from inference import *


def generate_net_h(model_arch: dict, weights)->str:
  net_h = "//     NET_H     //\n\n"
  net_h += "#ifndef NET_H\n"
  net_h += "#define NET_H\n\n"
  net_h += '#include "math.h"\n'
  net_h += '#include "stdint.h"\n\n'


  net_h += "/// PARAMETERS\n\n"  
  for weight in weights.keys():
    net_h += add_weight(weight, weights[weight])


  net_h += "/// RULES"
  # find all unique activation functions
  presented_activation_functions: list[str] = []
  for layer_name in model_arch.keys():
    activation_function: str = model_arch[layer_name]["nonlinearity"]
    if activation_function not in presented_activation_functions:
      presented_activation_functions.append(activation_function)

  # find all unique layers
  presented_layers: list[str] = []
  for layer_name in model_arch.keys():
    type: str = model_arch[layer_name]["type"]
    if type not in presented_layers:
      presented_layers.append(type)

  # add activation functions
  for activation_function in presented_activation_functions:
    net_h += add_activation_function(activation_function)

  # add layers
  for layer in presented_layers:
    net_h += add_layer(layer)


  net_h += "/// INFERENCE"
  # initialize memory buffer
  # net_h += add_memory_buffer(model_arch)

  # write layer settings
  # TODO

  # net_h += add_inference()


  net_h += "#endif // NET_H\n"

  return net_h