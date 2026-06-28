//    RULES_H     //

#ifndef RULES_H
#define RULES_H

#include "math.h"


void relu(float* x, const uint8_t& h, const uint8_t& w, const uint8_t& c) {
  for (int k = 0; k < c; ++k) {
    for (int i = 0; i < w; ++i) {
      for (int j = 0; j < h; ++j) {
        float& value = x[k * (w * h) + i * w + j];
        if (value < 0.f)
          value = 0.f;
      }
    }
  }
}
  
void sigmoid(float* x, const uint8_t& h, const uint8_t& w, const uint8_t& c) {
  for (int k = 0; k < c; ++k) {
    for (int i = 0; i < w; ++i) {
      for (int j = 0; j < h; ++j) {
        float& value = x[k * (w * h) + i * w + j];
        value = (1.f / (1.f + exp(-value)));
      }
    }
  }
}  
  
float* dense(const float* w, const float* b,
                 const float* x, float* o,
                 const uint8_t& n, const uint8_t& m, const uint8_t& p,
                 float* membuf) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      membuf[0] = 0.f;

      for (int k = 0; k < m; ++k) {
        membuf[0] += w[i * m + k] * x[k * p + j];
      }

      o[i * p + j] = membuf[0];
    }
  }

  // add biass
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      o[i * p + j] += b[i];
    }
  }
}
  
#endif // RULES_H
