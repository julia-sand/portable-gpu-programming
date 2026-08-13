// SPDX-FileCopyrightText: 2025 CSC - IT Center for Science Ltd. <www.csc.fi>
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <Kokkos_Core.hpp>

int main(int argc, char** argv)
{

  Kokkos::initialize(argc, argv);
{
  const double a = 0.5;
  constexpr size_t N = 100;

  Kokkos::View<double*> x("x",N);
  Kokkos::View<double*> y("y",N);

  //double *h_x = (double *) malloc(N * sizeof(double));
  //double *h_y = (double *) malloc(N * sizeof(double));

  Kokkos::View<double*, Kokkos::HostSpace> h_x("h_x",N);
  Kokkos::View<double*, Kokkos::HostSpace> h_y("h_y",N);

  // Initialize x and y
  Kokkos::parallel_for("Loop_init_test", N,
  KOKKOS_LAMBDA (const int i) {
    x[i] = (i + 1) * 2.4;
    y[i] = (i + 1) * -1.2;
  });

  Kokkos::fence();

  Kokkos::deep_copy(h_x,x);
  Kokkos::deep_copy(h_y,y);

  std::cout << "First and last elements before axpy: " << std::endl
            << "x: " << h_x[0] << "," << h_x[N-1] << std::endl
            << "y: " << h_y[0] << "," << h_y[N-1] << std::endl;

  //for (size_t i = 0; i < N; i++)
  Kokkos::parallel_for("Loop_test", N,
  KOKKOS_LAMBDA (const int i) {
    y[i] += a * x[i];
  });

  Kokkos::deep_copy(h_x,x);
  Kokkos::deep_copy(h_y,y);

  // Check results
  std::cout << "First and last element (both should be zero):" << std::endl 
            << h_y[0] << "," << h_y[N-1] << std::endl;

}
  //Kokkos::fence();
  Kokkos::finalize();


}
