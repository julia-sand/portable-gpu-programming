// SPDX-FileCopyrightText: 2025 CSC - IT Center for Science Ltd. <www.csc.fi>
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <cmath>



int main(int argc, char** argv)
{

  constexpr size_t N = 100;

  double *x = (double *) malloc(N * sizeof(double));
  double *y = (double *) malloc(N * sizeof(double));

  //lambdas
  auto lambda1 = [N](int i){return cos(i * 2*M_PI / (N-1) ); };
  auto lambda2 = [N](int i){return sin(i * 2*M_PI / (N-1) ); };
  

  // Initialize x and y
  // TODO: create here a lambda function for the loop body below, and
  // call it within the loop
  for (size_t i = 0; i < N; i++) 
  {
    x[i] = lambda1(i);//cos(i * 2*M_PI / (N-1) ); 
    y[i] = lambda2(i);//sin(i * 2*M_PI / (N-1) );
  }

  std::cout << "First and last elements before dot product: " << std::endl
            << "x: " << x[0] << "," << x[N-1] << std::endl
            << "y: " << y[0] << "," << y[N-1] << std::endl;

  // Perform dot product
  double result = 0.0;
  auto lambda3 = [](double x, double y){return x*y; };
  
  // TODO: create here a lambda function for the loop body below, and
  // call it within the loop
  for (size_t i = 0; i < N; i++) 
  {
    result += lambda3(x[i],y[i]);
  }

  // Check results
  std::cout << "Result (should be 0): " << result << std::endl;
}
