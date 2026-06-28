#ifndef TEST_NN_FC_LAYER
#define TEST_NN_FC_LAYER

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <cstdint>


class TestConfiguration {
public:
  TestConfiguration(const uint8_t& n, const uint8_t& m, const uint8_t& p,
    const std::vector<float>& W,
    const std::vector<float>& X,
    const std::vector<float>& Y) :
  n_(n), m_(m), p_(p),
  W_(W), X_(X), Y_(Y) {}

public:
  uint8_t n_, m_, p_;
  std::vector<float> W_;
  std::vector<float> X_;
  std::vector<float> Y_;
};


/// 1

TestConfiguration test_configuration_1 (
  8, 8, 8,
  {1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f},

  {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f},

  {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
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
  8, 4, 8,
  {1.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 1.f,
   1.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 1.f},

  {1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f},

  {1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f,
   1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f}
);

/// 3

TestConfiguration test_configuration_3 (
  16, 1, 16,
  {1.f,
   2.f,
   3.f,
   4.f,
   5.f,
   6.f,
   7.f,
   8.f,
   9.f,
   10.f,
   11.f,
   12.f,
   13.f,
   14.f,
   15.f,
   16.f},
  
  {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f},

  {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f,
   2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f, 32.f,
   3.f, 6.f, 9.f, 12.f, 15.f, 18.f, 21.f, 24.f, 27.f, 30.f, 33.f, 36.f, 39.f, 42.f, 45.f, 48.f,
   4.f, 8.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f, 40.f, 44.f, 48.f, 52.f, 56.f, 60.f, 64.f,
   5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f, 40.f, 45.f, 50.f, 55.f, 60.f, 65.f, 70.f, 75.f, 80.f,
   6.f, 12.f, 18.f, 24.f, 30.f, 36.f, 42.f, 48.f, 54.f, 60.f, 66.f, 72.f, 78.f, 84.f, 90.f, 96.f,
   7.f, 14.f, 21.f, 28.f, 35.f, 42.f, 49.f, 56.f, 63.f, 70.f, 77.f, 84.f, 91.f, 98.f, 105.f, 112.f,
   8.f, 16.f, 24.f, 32.f, 40.f, 48.f, 56.f, 64.f, 72.f, 80.f, 88.f, 96.f, 104.f, 112.f, 120.f, 128.f,
   9.f, 18.f, 27.f, 36.f, 45.f, 54.f, 63.f, 72.f, 81.f, 90.f, 99.f, 108.f, 117.f, 126.f, 135.f, 144.f,
   10.f, 20.f, 30.f, 40.f, 50.f, 60.f, 70.f, 80.f, 90.f, 100.f, 110.f, 120.f, 130.f, 140.f, 150.f, 160.f,
   11.f, 22.f, 33.f, 44.f, 55.f, 66.f, 77.f, 88.f, 99.f, 110.f, 121.f, 132.f, 143.f, 154.f, 165.f, 176.f,
   12.f, 24.f, 36.f, 48.f, 60.f, 72.f, 84.f, 96.f, 108.f, 120.f, 132.f, 144.f, 156.f, 168.f, 180.f, 192.f,
   13.f, 26.f, 39.f, 52.f, 65.f, 78.f, 91.f, 104.f, 117.f, 130.f, 143.f, 156.f, 169.f, 182.f, 195.f, 208.f,
   14.f, 28.f, 42.f, 56.f, 70.f, 84.f, 98.f, 112.f, 126.f, 140.f, 154.f, 168.f, 182.f, 196.f, 210.f, 224.f,
   15.f, 30.f, 45.f, 60.f, 75.f, 90.f, 105.f, 120.f, 135.f, 150.f, 165.f, 180.f, 195.f, 210.f, 225.f, 240.f,
   16.f, 32.f, 48.f, 64.f, 80.f, 96.f, 112.f, 128.f, 144.f, 160.f, 176.f, 192.f, 208.f, 224.f, 240.f, 256.f}
);

static std::vector<TestConfiguration> test_configurations = {
  test_configuration_1,
  test_configuration_2,
  test_configuration_3
};


// (n x p) = (n x m) * (m x p)
void matmul(const float* w, const float* x, float* o,
  const uint8_t& n, const uint8_t& m, const uint8_t& p);

void matmul_strassen(const float* w, const float* x, float* o,
    const uint8_t& n, const uint8_t& m, const uint8_t& p);

#endif // TEST_NN_FC