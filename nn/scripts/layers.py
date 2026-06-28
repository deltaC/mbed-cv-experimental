"""
NEURAL NETWORK LAYERS
"""

def add_layer(layer: str)->str:
  match layer:
    case "dense":
      return add_dense_layer()


def add_dense_layer()->str:
  s = '''
void dense(const float* w, const float* b,
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
  '''
  
  return s


def add_conv_layer(out_lang:str)->str:
  if (out_lang == 'C'):
    s = '''
_Float16* conv(_Float16* input,
                const uint8_t* input_size_x, const uint8_t* input_size_y,
                const _Float16* weight, const _Float16* bias,
                const uint8_t* out_channels, const uint8_t* in_channels,
                const uint8_t* kernel_x, const uint8_t* kernel_y,
                const uint8_t* stride_x, const uint8_t* stride_y,
                const uint8_t* padding_x, const uint8_t* padding_y) {

  uint8_t* out_size_x = calloc(1, sizeof(uint8_t));
  *out_size_x = (*input_size_x + 2 * *padding_x - *kernel_x) / *stride_x + 1;

  uint8_t* out_size_y = calloc(1, sizeof(uint8_t));
  *out_size_y = (*input_size_y + 2 * *padding_y - *kernel_y) / *stride_y + 1;
  
  _Float16* output = calloc(*out_channels * *out_size_x * *out_size_y, sizeof(_Float16));
  
  // create padded tensor
  _Float16* input_padded = calloc(*in_channels * (2 * *padding_x + *input_size_x) * (2 * *padding_y + *input_size_y), sizeof(_Float16));
  int* ptr = calloc(1, sizeof(int));

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    *ptr += (2 * *padding_x + *input_size_x) * *padding_y;

    for (uint8_t i = 0; i < *input_size_y; ++i) {
      *ptr += *padding_x;

      for (uint8_t j = 0; j < *input_size_x; ++j) {
        input_padded[*ptr] = input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j];
        *ptr += 1;
      }

      *ptr += *padding_x;
    }

    *ptr += (2 * *padding_x + *input_size_x) * *padding_y;
  }

  free(ptr); ptr = NULL;


  // convolution
  int* out_idx = calloc(1, sizeof(int));
  _Float16* value = calloc(1, sizeof(_Float16));

  for (uint8_t co = 0; co < *out_channels; ++co) {
    for (uint8_t i = 0; i < (2 * *padding_x + *input_size_x) - *kernel_x + 1; i += *stride_x) {
      for (uint8_t j = 0; j < (2 * *padding_y + *input_size_y) - *kernel_y + 1; j += *stride_y) {
        

        for (uint8_t ci = 0; ci < *in_channels; ++ci) {
          for (uint8_t n = 0; n < *kernel_x; ++n) {
            for (uint8_t m = 0; m < *kernel_y; ++m) {
              *value += (input_padded[(ci * ((2 * *padding_x + *input_size_x) * (2 * *padding_y + *input_size_y)) + i * (2 * *padding_x + *input_size_x) + j) + (n * (2 * *padding_x + *input_size_x) + m)] * weight[co * (*in_channels * *kernel_x * *kernel_y) + ci * (*kernel_x * *kernel_y) + n * *kernel_x + m]);
            }
          }
        }
        
        output[*out_idx] = *value;
        *value = 0.f;

        *out_idx += 1;
      }
    }
  }

  free(out_idx); out_idx = NULL;
  free(value); value = NULL;
  free(input_padded); input_padded = NULL;


  // add bias
  for (uint8_t co = 0; co < *out_channels; ++co) {
    for (uint8_t i = 0; i < *out_size_x; ++i) {
      for (uint8_t j = 0; j < *out_size_y; ++j) {
        output[co * (*out_size_x * *out_size_y) + i * (*out_size_x) + j] += bias[co];
      }
    }
  }

  free(out_size_x); out_size_x = NULL;
  free(out_size_y); out_size_y = NULL;

  return output;
}
  '''
    
  elif (out_lang == 'C++'):
    s = '''
float16_t* conv(float16_t* input,
                const uint8_t* input_size_x, const uint8_t* input_size_y,
                const float16_t* weight, const float16_t* bias,
                const uint8_t* out_channels, const uint8_t* in_channels,
                const uint8_t* kernel_x, const uint8_t* kernel_y,
                const uint8_t* stride_x, const uint8_t* stride_y,
                const uint8_t* padding_x, const uint8_t* padding_y) {

  uint8_t* out_size_x = new uint8_t((*input_size_x + 2 * *padding_x - *kernel_x) / *stride_x + 1);
  uint8_t* out_size_y = new uint8_t((*input_size_y + 2 * *padding_y - *kernel_y) / *stride_y + 1);
  
  float16_t* output = new float16_t[*out_channels * *out_size_x * *out_size_y];
  
  // create padded tensor
  float16_t* input_padded = new float16_t[*in_channels * (2 * *padding_x + *input_size_x) * (2 * *padding_y + *input_size_y)]();
  int* ptr = new int(0);

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    *ptr += (2 * *padding_x + *input_size_x) * *padding_y;

    for (uint8_t i = 0; i < *input_size_y; ++i) {
      *ptr += *padding_x;

      for (uint8_t j = 0; j < *input_size_x; ++j) {
        input_padded[*ptr] = input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j];
        *ptr += 1;
      }

      *ptr += *padding_x;
    }

    *ptr += (2 * *padding_x + *input_size_x) * *padding_y;
  }

  delete ptr;


  // convolution
  int* out_idx = new int();
  float16_t* value = new float16_t();

  for (uint8_t co = 0; co < *out_channels; ++co) {
    for (uint8_t i = 0; i < (2 * *padding_x + *input_size_x) - *kernel_x + 1; i += *stride_x) {
      for (uint8_t j = 0; j < (2 * *padding_y + *input_size_y) - *kernel_y + 1; j += *stride_y) {
        

        for (uint8_t ci = 0; ci < *in_channels; ++ci) {
          for (uint8_t n = 0; n < *kernel_x; ++n) {
            for (uint8_t m = 0; m < *kernel_y; ++m) {
              *value += (input_padded[(ci * ((2 * *padding_x + *input_size_x) * (2 * *padding_y + *input_size_y)) + i * (2 * *padding_x + *input_size_x) + j) + (n * (2 * *padding_x + *input_size_x) + m)] * weight[co * (*in_channels * *kernel_x * *kernel_y) + ci * (*kernel_x * *kernel_y) + n * *kernel_x + m]);
            }
          }
        }
        
        output[*out_idx] = *value;
        *value = 0.f;

        *out_idx += 1;
      }
    }
  }

  delete out_idx;
  delete value;
  delete[] input_padded;


  // add bias
  for (uint8_t co = 0; co < *out_channels; ++co) {
    for (uint8_t i = 0; i < *out_size_x; ++i) {
      for (uint8_t j = 0; j < *out_size_y; ++j) {
        output[co * (*out_size_x * *out_size_y) + i * (*out_size_x) + j] += bias[co];
      }
    }
  }

  delete out_size_x;
  delete out_size_y;

  return output;
}
  '''

  return s


def add_upconv_layer(out_lang:str)->str:
  if (out_lang == 'C'):
    s = '''
_Float16* upconv(_Float16* input,
                  const uint8_t* input_size_x, const uint8_t* input_size_y,
                  const _Float16* weight, const _Float16* bias,
                  const uint8_t* out_channels, const uint8_t* in_channels,
                  const uint8_t* kernel_x, const uint8_t* kernel_y,
                  const uint8_t* stride_x, const uint8_t* stride_y,
                  const uint8_t* padding_x, const uint8_t* padding_y) {
  // add zeros
  uint8_t* output_size_x = calloc(1, sizeof(uint8_t));
  *output_size_x = *stride_x * *input_size_x;

  uint8_t* output_size_y = calloc(1, sizeof(uint8_t));
  *output_size_y = *stride_y * *input_size_y;
                  
  _Float16* input_padded = calloc(*in_channels * *output_size_x * *output_size_y, sizeof(_Float16));

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    for (uint8_t i = 0; i < *output_size_x; i += *stride_x) {
      for (uint8_t j = 0; j < *output_size_y; j += *stride_y) {
        input_padded[ci * (*output_size_x * *output_size_y) + i * *output_size_x + j] = input[ci * (*output_size_x * *output_size_y) + (i / *stride_x) * *input_size_x + (j / *stride_y)];
      }
    }
  }
  

  // do a convolution
  uint8_t* upconv_stride = calloc(1, sizeof(uint8_t));
  *upconv_stride = 1;

  _Float16* output = conv(input_padded,
                           output_size_x, output_size_y,
                           weight, bias,
                           out_channels, in_channels,
                           kernel_x, kernel_y,
                           upconv_stride, upconv_stride,
                           padding_x, padding_y);

  free(output_size_x); output_size_x = NULL;
  free(output_size_y); output_size_y = NULL;
  free(input_padded); input_padded = NULL;

  free(upconv_stride); upconv_stride = NULL

  return output;                  
}
  ''' 
    
  elif (out_lang == 'C++'):
    s = '''
float16_t* upconv(float16_t* input,
                  const uint8_t* input_size_x, const uint8_t* input_size_y,
                  const float16_t* weight, const float16_t* bias,
                  const uint8_t* out_channels, const uint8_t* in_channels,
                  const uint8_t* kernel_x, const uint8_t* kernel_y,
                  const uint8_t* stride_x, const uint8_t* stride_y,
                  const uint8_t* padding_x, const uint8_t* padding_y) {
  // add zeros
  const uint8_t* output_size_x = new uint8_t(*stride_x * *input_size_x);
  const uint8_t* output_size_y = new uint8_t(*stride_y * *input_size_y);
                  
  float16_t* input_padded = new float16_t[*in_channels * *output_size_x * *output_size_y]();

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    for (uint8_t i = 0; i < *output_size_x; i += *stride_x) {
      for (uint8_t j = 0; j < *output_size_y; j += *stride_y) {
        input_padded[ci * (*output_size_x * *output_size_y) + i * *output_size_x + j] = input[ci * (*output_size_x * *output_size_y) + (i / *stride_x) * *input_size_x + (j / *stride_y)];
      }
    }
  }
  

  // do a convolution
  const uint8_t* upconv_stride = new uint8_t(1);

  float16_t* output = conv(input_padded,
                           output_size_x, output_size_y,
                           weight, bias,
                           out_channels, in_channels,
                           kernel_x, kernel_y,
                           upconv_stride, upconv_stride,
                           padding_x, padding_y);

  delete output_size_x;
  delete output_size_y;
  delete[] input_padded;

  delete upconv_stride;

  return output;                  
}
  ''' 

  return s
  


def add_global_avg_pooling_layer(out_lang:str)->str: # TODO: test
  if (out_lang == 'C'):
    s = '''
_Float16* gap(_Float16* input, const uint8_t* in_channels,
               const uint8_t* input_size_x, const uint8_t* input_size_y) {

  _Float16* output = calloc(*in_channels, sizeof(_Float16));
  _Float16* value = calloc(1, sizeof(_Float16));

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    *value = 0.f;

    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        *value += input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j];
      }
    }

    *value /= (*input_size_x * *input_size_y);
    output[ci] = *value;
  }
  free(value); value = NULL;

  return output;
}
'''

  elif (out_lang == 'C++'):
    s = '''
float16_t* gap(float16_t* input, const uint8_t* in_channels,
               const uint8_t* input_size_x, const uint8_t* input_size_y) {

  float16_t* output = new float16_t[*in_channels]();
  float16_t* value = new float16_t;

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    *value = 0.f;

    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        *value += input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j];
      }
    }

    *value /= (*input_size_x * *input_size_y);
    output[ci] = *value;
  }
  delete value;

  return output;
}
'''

  return s


def add_global_max_pooling_layer(out_lang:str)->str: # TODO: test
  if (out_lang == 'C'):
    s = '''
_Float16* gmp(_Float16* input, const uint8_t* in_channels,
               const uint8_t* input_size_x, const uint8_t* input_size_y) {

  _Float16* output = calloc(*in_channels, sizeof(_Float16));
  _Float16* value = calloc(1, sizeof(_Float16));

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    *value = 0.f;

    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        if (*value < input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j]) {
          *value = input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j];
        }
      }
    }

    output[ci] = *value;
  }
  free(value); value = NULL;

  return output;              
}
'''

  elif (out_lang == 'C++'):
    s = '''
float16_t* gmp(float16_t* input, const uint8_t* in_channels,
               const uint8_t* input_size_x, const uint8_t* input_size_y) {

  float16_t* output = new float16_t[*in_channels]();
  float16_t* value = new float16_t;

  for (uint8_t ci = 0; ci < *in_channels; ++ci) {
    *value = 0.f;

    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        if (*value < input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j]) {
          *value = input[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j];
        }
      }
    }

    output[ci] = *value;
  }
  delete value;

  return output;              
}
'''

  return s


def add_concat_layer(out_lang:str)->str:
  if (out_lang == 'C'):
    s = '''
_Float16* concat(_Float16* input1, uint8_t* in_channels1,
                  _Float16* input2, uint8_t* in_channels2,
                  uint8_t* input_size_x, uint8_t* input_size_y) {
  uint8_t* out_channels = calloc(1, sizeof(uint8_t));
  *out_channels = *in_channels1 + *in_channels2;

  _Float16* output = calloc(*out_channels * *input_size_x * *input_size_y, sizeof(_Float16));
  
  // add first tensor
  for (uint8_t ci = 0; ci < *in_channels1; ++ci) {
    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        output[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j] = input1[ci * (*input_size_x * *input_size_x) + i * *input_size_x + j];
      }
    }
  }

  // add second tensor
  for (uint8_t ci = *in_channels1; ci < *in_channels1 + *in_channels2; ++ci) {
    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        output[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j] = input2[(ci - *in_channels1) * (*input_size_x * *input_size_x) + i * *input_size_x + j];
      }
    }
  }
  
  free(out_channels); out_channels = NULL:

  return output;
}
  '''
    
  elif (out_lang == 'C++'):
    s = '''
float16_t* concat(float16_t* input1, uint8_t* in_channels1,
                  float16_t* input2, uint8_t* in_channels2,
                  uint8_t* input_size_x, uint8_t* input_size_y) {
  uint8_t* out_channels = new uint8_t(*in_channels1 + *in_channels2);
  float16_t* output = new float16_t[*out_channels * *input_size_x * *input_size_y]();
  
  // add first tensor
  for (uint8_t ci = 0; ci < *in_channels1; ++ci) {
    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        output[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j] = input1[ci * (*input_size_x * *input_size_x) + i * *input_size_x + j];
      }
    }
  }

  // add second tensor
  for (uint8_t ci = *in_channels1; ci < *in_channels1 + *in_channels2; ++ci) {
    for (uint8_t i = 0; i < *input_size_x; ++i) {
      for (uint8_t j = 0; j < *input_size_y; ++j) {
        output[ci * (*input_size_x * *input_size_y) + i * *input_size_x + j] = input2[(ci - *in_channels1) * (*input_size_x * *input_size_x) + i * *input_size_x + j];
      }
    }
  }
  
  delete out_channels;

  return output;
}
  '''

  return s


def add_bnorm_layer(out_lang:str)->str:
  if (out_lang == 'C'):
    s = '''

  '''
    
  elif (out_lang == 'C++'):
    s = '''

  '''

  return s


def add_lnorm_layer(out_lang: str)->str:
  if (out_lang == 'C'):
    s = '''

  '''
    
  elif (out_lang == 'C++'):
    s = '''
  
  '''
    
  return s


def add_lnorm_simple_layer(out_lang: str)->str:
  if (out_lang == 'C'):
    s = '''

  '''
    
  elif (out_lang == 'C++'):
    s = '''
void lnorm_simple(float16_t* x, const uint8_t* size) {
  float16_t* mean = new float16_t();
  for (int i = 0; i < *size; ++i) {
    *mean += x[i];
  }
  *mean /= *size;

  float16_t* std = new float16_t();
  for (int i = 0; i < *size; ++i) {
    *std += (x[i] - *mean) * (x[i] - *mean);
  }
  *std /= *size;
  *std = sqrt(*std);

  for (int i = 0; i < *size; ++i) {
    x[i] = (x[i] - *mean) / *std;
  }

  delete mean;
  delete std;
}  
  '''
    
  return s


def add_mha_layer(out_lang: str)->str:
  if (out_lang == 'C'):
    s = '''

  '''
    
  elif (out_lang == 'C++'):
    s = '''
  
  '''
    
  return s