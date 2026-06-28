"""
ACTIVATION FUNCTIONS
"""

def add_activation_function(activation_function: str)->str:
  match activation_function:
    case "relu":
      return add_relu()
    
    case "sigmoid":
      return add_sigmoid()


def add_relu()->str:
  s = '''
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
  '''
    
  return s
 

def add_symrelu(out_lang:str)->str:
  if (out_lang == 'C'):
    s = '''
void symrelu(float16_t* x) {
  if (*x <= -1.F16) {
    *x = -1.F16;
  } else if (*x >= 1.F16) {
    *x = 1.F16;
  }
}
  '''
    
  elif (out_lang == "C++"):
    s = '''
void symrelu(float16_t* x) {
  if (*x <= -1.f) {
    *x = -1.f;
  } else if (*x >= 1.f) {
    *x = 1.f;
  }
}
  '''
  
  return s


def add_tanh(out_lang:str)->str:
  if (out_lang == 'C'):
    s = '''
void tanh(_Float16* x) {
  *x = (exp(*x) - exp(-*x)) / (exp(*x) + exp(-*x));
}
  '''
  
  elif (out_lang == 'C++'):
    s = '''
void tanh(float16_t* x) {
  *x = (exp(*x) - exp(-*x)) / (exp(*x) + exp(-*x));
}
  '''
  
  return s


def add_sigmoid()->str:
  s = '''
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
  '''
    
  return s