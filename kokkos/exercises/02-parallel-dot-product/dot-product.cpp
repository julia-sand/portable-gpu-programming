// SPDX-FileCopyrightText: 2025 CSC - IT Center for Science Ltd. <www.csc.fi>
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <cmath>
#include <Kokkos_Core.hpp>

int main(int argc, char** argv)
{
  Kokkos::initialize(argc, argv);
 {
  constexpr size_t N = 100;

  //double *x = (double *) malloc(N * sizeof(double));
  //double *y = (double *) malloc(N * sizeof(double));

  Kokkos::View<double*> x("x",N);
  Kokkos::View<double*> y("y",N);

  Kokkos::View<double*, Kokkos::HostSpace> h_x("h_x",N);
  Kokkos::View<double*, Kokkos::HostSpace> h_y("h_y",N);

  // Initialize x and y
  Kokkos::parallel_for("init_loop",N,
  KOKKOS_LAMBDA (const int i) 
  {
    x[i] = cos(i * 2*M_PI / (N-1) );
    y[i] = sin(i * 2*M_PI / (N-1) );
  });

  //copy back to cpu for printing
  Kokkos::deep_copy(h_x,x); 
  Kokkos::deep_copy(h_y,y);

  std::cout << "First and last elements before dot product: " << std::endl
            << "x: " << h_x[0] << "," << h_x[N-1] << std::endl
            << "y: " << h_y[0] << "," << h_y[N-1] << std::endl;

  // Perform dot product
  double result = 0.0;
  Kokkos::parallel_reduce("sum_loop",N,
  KOKKOS_LAMBDA (const size_t i, double &result) 
  {
    result += x[i] * y[i];
  },result);
  
  //copy results
  Kokkos::deep_copy(h_y,y);
  
  // Check results
  std::cout << "Result (should be 0): " << result << std::endl;
  };
  Kokkos::finalize();
}
