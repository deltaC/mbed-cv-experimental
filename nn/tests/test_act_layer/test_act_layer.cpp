#include "test_act_layer.hpp"

/*            / x, if x > 0
 * ReLU(x) = | 
 *            \ 0, if x <= 0
*/   
void relu(float* x, const uint8_t& h, const uint8_t& w, const uint8_t& c) {
  for (int k {0}; k < c; ++k) {
    for (int i {0}; i < w; ++i) {
      for (int j {0}; j < h; ++j) {
        float& value = x[k * (w * h) + i * w + j];
        if (value < 0.f)
          value = 0.f;
      }
    }
  }
}


/*                   1
 * Sigmoid(x) = -----------
 *               1 + e^(-x)
*/
void sigmoid(float* x, const uint8_t& h, const uint8_t& w, const uint8_t& c) {
  for (int k {0}; k < c; ++k) {
    for (int i {0}; i < w; ++i) {
      for (int j {0}; j < h; ++j) {
        float& value = x[k * (w * h) + i * w + j];
        value = (1.f / (1.f + exp(-value)));
      }
    }
  }
}


TEST(TestAct, TestActReLU) {
  for (uint8_t test_conf_idx {0}; test_conf_idx < test_configurations.size(); ++test_conf_idx) {
    uint8_t h = test_configurations[test_conf_idx].h_;
    uint8_t w = test_configurations[test_conf_idx].w_;
    uint8_t c = test_configurations[test_conf_idx].c_;

    std::vector<float> X = test_configurations[test_conf_idx].X_;
    float* X_f = X.data();
    
    std::vector<float> Y = test_configurations[test_conf_idx].Y_;
    float* Y_f = Y.data();

    ActivationFunction act_type = test_configurations[test_conf_idx].act_type_;

    switch(act_type) {
      case ActivationFunction::RELU:
        relu(X_f, h, w, c);
        break; 

      case ActivationFunction::SIGMOID:
        sigmoid(X_f, h, w, c);
        break;
    }

    for (uint8_t k {0}; k < c; ++k) {
      for (uint8_t i {0}; i < w; ++i) {    
        for (uint8_t j {0}; j < h; ++j) {
          ASSERT_FALSE(abs(X_f[k * w * h + i * w + j] - Y_f[k * w * h + i * w + j]) > EPSILON);
        }
      }
    } 
  }  
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}