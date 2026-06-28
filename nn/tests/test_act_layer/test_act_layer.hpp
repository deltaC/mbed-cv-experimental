#ifndef TEST_NN_ACT_LAYER
#define TEST_NN_ACT_LAYER

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>
#include <cstdint>
#include <cmath>


const float EPSILON = 0.0001f;

enum class ActivationFunction {
  RELU,
  SIGMOID
};


class TestConfiguration {
public:
  TestConfiguration(ActivationFunction act_type,
    const uint8_t& h, const uint8_t& w, const uint8_t& c,
    const std::vector<float>& X, const std::vector<float>& Y) :
  act_type_(act_type),
  h_(h), w_(w), c_(c),
  X_(X), Y_(Y) {}

public:
  ActivationFunction act_type_;
  uint8_t h_, w_, c_;
  std::vector<float> X_;
  std::vector<float> Y_;
};



/// 1

TestConfiguration test_configuration_1 (
  ActivationFunction::RELU,
  8, 8, 3,
  {1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  1.f,

   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,

   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f},


  {1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,

   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,

   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}
);


/// 2

TestConfiguration test_configuration_2 (
  ActivationFunction::SIGMOID,
  8, 8, 3,
  {1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  1.f,

   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,

   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  1.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, -1.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f,
   1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f,
   1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f,
   1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f},


  {0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,      0.73105f,

   0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,      0.73105f,
   0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,

   0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,      0.73105f,
   0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.26894f,
   0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.26894f,
   0.73105f, 0.5f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.26894f,
   0.73105f, 0.5f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.73105f, 0.5f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.73105f, 0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.26894f,
   0.73105f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,      0.26894f}
);

static std::vector<TestConfiguration> test_configurations = {
  test_configuration_1,
  test_configuration_2
};


/*            / x, if x > 0
 * ReLU(x) = | 
 *            \ 0, if x <= 0
*/           
void relu(float* x, const uint8_t& h, const uint8_t& w, const uint8_t& c);


/*                   1
 * Sigmoid(x) = -----------
 *               1 + e^(-x)
*/
void sigmoid(float* x, const uint8_t& h, const uint8_t& w, const uint8_t& c);

#endif // TEST_NN_ACT