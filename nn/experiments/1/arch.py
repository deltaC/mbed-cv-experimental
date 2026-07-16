import os, sys
import json, ujson
import torch


class CNN(torch.nn.Module):
  def __init__(self, in_channels: int)->None:
    super(CNN, self).__init__()

    self.in_channels = in_channels

    self.relu = torch.nn.ReLU(inplace=True)
    self.sigmoid = torch.nn.Sigmoid()

    self.conv_bl_1_1 = torch.nn.Conv2d(self.in_channels, 4, (3, 3), (1, 1), (1, 1))
    self.conv_bl_1_2 = torch.nn.Conv2d(4, 4, (2, 2), (2, 2), (0, 0))

    self.conv_bl_2_1 = torch.nn.Conv2d(4, 8, (3, 3), (1, 1), (1, 1))
    self.conv_bl_2_2 = torch.nn.Conv2d(8, 8, (2, 2), (2, 2), (0, 0))

    self.conv_bl_3_1 = torch.nn.Conv2d(8, 12, (3, 3), (1, 1), (1, 1))
    self.conv_bl_3_2 = torch.nn.Conv2d(12, 12, (2, 2), (2, 2), (0, 0))

    self.conv_bl_4_1 = torch.nn.Conv2d(12, 1, (2, 2), (1, 1), (0, 0))


  def forward(self, x: torch.Tensor)->torch.Tensor:
    x = self.relu(self.conv_bl_1_1(x))
    x = self.relu(self.conv_bl_1_2(x))

    x = self.relu(self.conv_bl_2_1(x))
    x = self.relu(self.conv_bl_2_2(x))

    x = self.relu(self.conv_bl_3_1(x))
    x = self.relu(self.conv_bl_3_2(x))

    x = self.sigmoid(self.conv_bl_4_1(x))

    return x


  def dump_arch(self, arch_path: str)->None:
    arch: dict = {}

    arch["conv_bl_1_1"] = {
      "inputs": ["input"],
      "type": "conv",
      "shape": [4, self.in_channels, 3, 3],
      "strides": [1, 1],
      "paddings": [1, 1],
      "bias": True,
      "nonlinearity": "relu" 
    }
    arch["conv_bl_1_2"] = {
      "inputs": ["conv_bl_1_1"],
      "type": "conv",
      "shape": [4, 4, 2, 2],
      "strides": [2, 2],
      "paddings": [0, 0],
      "bias": True,
      "nonlinearity": "relu" 
    }

    arch["conv_bl_2_1"] = {
      "inputs": ["conv_bl_1_2"],
      "type": "conv",
      "shape": [8, 4, 3, 3],
      "strides": [1, 1],
      "paddings": [1, 1],
      "bias": True,
      "nonlinearity": "relu" 
    }
    arch["conv_bl_2_2"] = {
      "inputs": ["conv_bl_2_1"],
      "type": "conv",
      "shape": [8, 8, 2, 2],
      "strides": [2, 2],
      "paddings": [0, 0],
      "bias": True,
      "nonlinearity": "relu" 
    }

    arch["conv_bl_3_1"] = {
      "inputs": ["conv_bl_2_2"],
      "type": "conv",
      "shape": [12, 8, 3, 3],
      "strides": [1, 1],
      "paddings": [1, 1],
      "bias": True,
      "nonlinearity": "relu" 
    }
    arch["conv_bl_3_2"] = {
      "inputs": ["conv_bl_3_1"],
      "type": "conv",
      "shape": [12, 12, 2, 2],
      "strides": [2, 2],
      "paddings": [0, 0],
      "bias": True,
      "nonlinearity": "relu" 
    }

    arch["conb_bl_4_1"] = {
      "inputs": ["conv_bl_3_2"],
      "type": "conv",
      "shape": [1, 12, 2, 2],
      "strides": [1, 1],
      "paddings": [0, 0],
      "bias": True,
      "nonlinearity": "sigmoid"
    }

    with open(arch_path, 'w') as fp:
      ujson.dump(arch, fp, sort_keys=False, indent=2)




def main()->None:
  in_channels: int = 1
  in_width: int = 8
  in_height: int = 8
  n_samples: int = 1

  arch_path: str = "/home/vav/Projects/mbed-cv-experimental/nn/experiments/1/arch.json"

  model: CNN = CNN(in_channels)
  model.dump_arch(arch_path)

  model_save_path: str = "/home/vav/Projects/mbed-cv-experimental/nn/experiments/1/model.pth"
  torch.save(model.state_dict(), model_save_path)  




if __name__ == "__main__":
  main()