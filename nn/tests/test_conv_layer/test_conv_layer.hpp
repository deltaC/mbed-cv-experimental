#ifndef TEST_NN_CONV_LAYER
#define TEST_NN_CONV_LAYER

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <cstdint>

class TestConfiguration {
public:
  TestConfiguration() {}

public:
  uint8_t _input_size_x, _input_size_y;
  uint8_t _input_channels, _output_channels;
  uint8_t _kernel_x, _kernel_y;
  uint8_t _stride_x, _stride_y;
  uint8_t _padding_x, _padding_y;
  uint8_t _n_repeats;
  std::vector<float> _X;
  std::vector<float> _W;
  std::vector<float> _B;
  std::vector<float> _res;
};

void conv();

#endif // TEST_NN_CONV_LAYER