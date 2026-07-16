import os, sys
import json
import numpy
import torch

from generate import *

torch.set_printoptions(
  threshold=torch.iinfo(torch.int32).max,
  edgeitems=10000,
  linewidth=1000
)


def main(model_arch_path:str, model_weights_path:str, output_dir_path:str)->None:
  # Loading weights
  weights = torch.load(model_weights_path)

  # Loading arch
  with open(model_arch_path, 'r') as model_arch_file:
    model_arch: dict = json.load(model_arch_file)

  # Generating net.h
  net_h: str = generate_net_h(model_arch, weights)
  output_net_path: str = os.path.join(output_dir_path, "net.h")
  with open(output_net_path, 'w') as net_file:
    net_file.write(net_h)
  



if __name__ == "__main__":
  model_arch_path = sys.argv[1]
  model_weights_path = sys.argv[2]
  output_dir_path = sys.argv[3]

  main(model_arch_path, model_weights_path, output_dir_path)