// Includes
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include <functional>

void FunctionPointerCallback(const size_t iteration, const double guess) {
  std::cout << iteration << " : " << guess << " (Function Pointer)\n";
}

class MemberFunctionCallback {
public:
  void Call(const size_t iteration, const double guess) {
    std::cout << iteration << " : " << guess << " (Member Function)\n";
  }
};

class FunctorCallback {
public:
  void operator()(const size_t iteration, const double guess) {
    std::cout << iteration << " : " << guess << " (Functor)\n";
  }
};

// Class with callback
class SquareRoot {
public:
  // Callback typedefs
  using TCallback = std::function<void(const size_t, const double)>;
  using TCallbackVector = std::vector<TCallback>;

  // Push callbacks onto the stack.
  void add_callback(TCallback cb) {
    m_callbacks.push_back(cb);
  }

  // Main logic of class.
  double run(const double input) {
    if (input < 0.0) throw 0; // Error checking.
    this->iteration = 0;      // Reset iteration number.
    double guess = input;     // Set initial guess to input.
    // Babylonian method.
    while (std::fabs(guess - input/guess) > this->epsilon) {
      for (const auto &cb : m_callbacks) {
        cb(iteration, guess);
      }
      guess = (guess + input / guess) / 2.0;
      ++iteration;
    }
    return guess;
  }

private:
  const double epsilon = 1e-6; // Maximum Allowed Error.
  size_t iteration = 0;        // Iteration Number.

  // Data member holding callbacks.
  TCallbackVector m_callbacks;

};

int main() {

  SquareRoot p;

  // Function Pointer
  auto *cb_a = FunctionPointerCallback;
  p.add_callback(cb_a);

  // Member Function
  MemberFunctionCallback cb_b_tmp;
  auto cb_b = std::bind(&MemberFunctionCallback::Call, // function
                        &cb_b_tmp,                     // First argument (*this)
                        std::placeholders::_1,         // 1st placeholder
                        std::placeholders::_2);        // 2nd placeholder
  p.add_callback(cb_b);

  // Functor
  FunctorCallback cb_c;
  p.add_callback(cb_c);

  // Lambda
  auto cb_d = [](const size_t iteration, const double guess)
    { std::cout << iteration << " : " << guess << " (Lambda)\n"; };
  p.add_callback(cb_d);

  std::cout << "Result: " << p.run(1234.5*1234.5) << std::endl;

  return EXIT_SUCCESS;

}
