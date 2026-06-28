import os, sys
import json, ujson
import torch


class FCNN(torch.nn.Module):
  def __init__(self, in_features: int, intermediate_features: int, out_features: int)->None:
    super(FCNN, self).__init__()

    self.in_features = in_features
    self.intermediate_features = intermediate_features
    self.out_features = out_features

    self.relu = torch.nn.ReLU(inplace=True)
    self.sigmoid = torch.nn.Sigmoid()

    self.dense1 = torch.nn.Linear(in_features, intermediate_features)
    self.dense2 = torch.nn.Linear(intermediate_features, out_features)

  def forward(self, x: torch.Tensor)->torch.Tensor:
    x: torch.Tensor = self.relu(self.dense1(x))
    x: torch.Tensor = self.sigmoid(self.dense2(x))

    return x

  # TODO: improve
  def dump_arch(self, arch_path: str)->None:
    arch: dict = {}

    arch["dense1"] = {
      "inputs": ["input"],
      "type": "dense",
      "shape": [self.in_features, self.intermediate_features],
      "bias": True,
      "nonlinearity": "relu"
    }
    
    arch["dense2"] = {
      "inputs": ["dense1"],
      "type": "dense",
      "shape": [self.intermediate_features, self.out_features],
      "bias": True,
      "nonlinearity": "sigmoid"
    }

    with open(arch_path, 'w') as fp:
      ujson.dump(arch, fp, sort_keys=False, indent=2)



# in_features = H * W (image sizes)
# (n_samples x in_features) * (in_features x intermediate_features) * (intermediate_features x out_features)

def main()->None:
  in_features: int = 14 * 14
  intermediate_features: int = 64
  out_features: int = 1
  n_samples: int = 1

  arch_path: str = "/home/vav/Projects/mbed-cv-experimental/experiments/0/arch.json"

  model: FCNN = FCNN(in_features, intermediate_features, out_features)
  model.dump_arch(arch_path)

  model_save_path: str = "/home/vav/Projects/mbed-cv-experimental/experiments/0/model.pth"
  torch.save(model.state_dict(), model_save_path)

  


if __name__ == "__main__":
  main()