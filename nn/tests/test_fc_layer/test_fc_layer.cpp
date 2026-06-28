#include "test_fc_layer.hpp"


// (n x p) = (n x m) * (m x p)
void matmul(const float* w, const float* x, float* o,
    const uint8_t& n, const uint8_t& m, const uint8_t& p) {
  float sum;

  for (int i {0}; i < n; ++i) {
    for (int j {0}; j < p; ++j) {
      sum = 0.f;

      for (int k {0}; k < m; ++k) {
        sum += w[i * m + k] * x[k * p + j];
      }

      o[i * p + j] = sum;
    }
  }
}

void matmul_strassen(const float* w, const float* x, float* o,
    const uint8_t& n, const uint8_t& m, const uint8_t& p) {
  
}


TEST(TestMatmul, TestMatmulSimple) {
  for (uint8_t test_conf_idx {0}; test_conf_idx < test_configurations.size(); ++test_conf_idx) {
    uint8_t n = test_configurations[test_conf_idx].n_;
    uint8_t m = test_configurations[test_conf_idx].m_;
    uint8_t p = test_configurations[test_conf_idx].p_;

    std::vector<float> W = test_configurations[test_conf_idx].W_;
    float* W_f = W.data();

    std::vector<float> X = test_configurations[test_conf_idx].X_;
    float* X_f = X.data();
    
    std::vector<float> Y = test_configurations[test_conf_idx].Y_;
    float* Y_f = Y.data();

    std::vector<float> O = std::vector<float>(n * p);
    float* O_f = O.data();

    matmul(W_f, X_f, O_f, n, m, p);
    
    for (uint8_t i {0}; i < n; ++i) {
      for (uint8_t j {0}; j < p; ++j) {
        ASSERT_FALSE(O_f[i * p + j] != Y_f[i * p + j]);
      }
    } 
  }  
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}