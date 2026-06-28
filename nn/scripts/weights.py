"""
WEIGHTS
"""
import re
import torch

def remove_nestring_brackets(line: str)->str:
  result = []
  brace_count = 0
  
  for char in line:
    if char == '{':
      brace_count += 1
      if brace_count == 1:
        result.append(char)

    elif char == '}':
      if brace_count == 1:
        result.append(char)
      brace_count -= 1

    else:
      result.append(char)
  
  return ''.join(result)


def add_weight(key: str, weight: torch.Tensor)->str:
  key = key.replace('.', '_')
  dims = weight.size()

  weight_str = str(weight)
  weight_str = weight_str.replace("tensor", "")
  weight_str = weight_str.replace("(", "")
  weight_str = weight_str.replace(")", "")
  weight_str = weight_str.replace("[", "{")
  weight_str = weight_str.replace("]", "}")

  weight_str = remove_nestring_brackets(weight_str)

  weight_var_str = f"const float {key}"

  res_dim: int = 1
  for dim in dims:
    res_dim *= dim
   
  weight_var_str += '[' + str(res_dim) + ']'

  return (weight_var_str + " = " + weight_str + ';' + '\n\n')