#ifndef MATHS_H
#define MATHS_H

#include <cstdlib>
#include <cmath>
#include <vector>

//

static const double LEAKY_RELU_CONSTANT = 100;

//

inline double drandom(double min, double max) {
  --max;
  return static_cast<double>(rand() % 100001) / 100000 * (max - min + 1) + min;
}

inline int irandom(int min, int max) {
  --max;
  return static_cast<double>(rand() % 101) / 100 * (max - min + 1) + min;
}

//

inline void ReLu(std::vector<double>& values) {
  for (double& value : values) {
    value = (value > 0)? value : 0;
  }
}

inline void LeakyReLu(std::vector<double>& values) {
  for (int i = 0; i < values.size(); ++i) {
    values[i] = (values[i] > 0)? values[i] : values[i] / LEAKY_RELU_CONSTANT;
  }
}

inline void sigmoid(std::vector<double>& values) {
  for (int i = 0; i < values.size(); ++i) {
    values[i] = 1.f / (1 + exp(-values[i]));
  }
}

#endif
