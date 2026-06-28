"""
GENERATION
"""
from act_funcs import *
from layers import *
from weights import *


def generate_rules_h(model_arch: dict)->str:
  rules_h = "//    RULES_H     //\n\n"
  rules_h += "#ifndef RULES_H\n"
  rules_h += "#define RULES_H\n\n"
  rules_h += '#include "math.h"\n\n'
  

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
    rules_h += add_activation_function(activation_function)

  # add layers
  for layer in presented_layers:
    rules_h += add_layer(layer)

  rules_h += "\n#endif // RULES_H\n"

    
  return rules_h


def generate_weights_h(weights)->str:
  weights_h = "//     WEIGHTS_H     //\n\n"
  weights_h += "#ifndef WEIGHTS_H\n"
  weights_h += "#define WEIGHTS_H\n\n"

  for key in weights.keys():
    weights_h += add_weight(key, weights[key])

  weights_h += "#endif // WEIGHTS_H\n"

  return weights_h


def generate_net_h(model_arch: str, rules_path: str, weights_path: str)->str:
  net_h = "//     NET_H     //\n\n"
  net_h += "#ifndef NET_H\n"
  net_h += "#define NET_H\n\n"

  # add parameters

  # TODO: create membuf

  # adopt rules





  net_h += "#endif // NET_H\n"

  return net_h