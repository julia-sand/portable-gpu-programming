// SPDX-FileCopyrightText: 2024 CSC - IT Center for Science Ltd. <www.csc.fi>
//
// SPDX-License-Identifier: MIT

#include <Kokkos_Core.hpp>
#include <iostream>

int main(int argc, char* argv[]) {

  // Initialize Kokkos
  Kokkos::initialize(argc, argv);

  {
    int n = 20;
    int m = 20;

    Kokkos::View<int**> a("a", n, m);
    //Kokkos::View<int**, Kokkos::HostSpace> ha("ha",n,m);
    //Kokkos::View<int**, Kokkos::SharedSpace> ma("ma",n,m);

    // Subviews of boundaries
    auto a_top = Kokkos::subview(a,0,Kokkos::ALL() );
    auto a_left = Kokkos::subview(a, Kokkos::ALL(), 0);
    auto a_bottom = Kokkos::subview(a, 19,  Kokkos::ALL());
    auto a_right = Kokkos::subview(a, Kokkos::ALL(), 19);

    // Initialize boundaries in parallel
    Kokkos::parallel_for("init_boundary",n,
      KOKKOS_LAMBDA (const int i) {
       a_left[i] = 2;
       a_right[i] = 4;
       a_top[i] = 1;
       a_bottom[i] = 3;
     });
    Kokkos::fence();

    // Create mirror views
    // by default it is on host
    auto ma = Kokkos::create_mirror(a);

    // Copy to host
    Kokkos::deep_copy(ma,a);

    // Check results  
    std::cout << "Top (should be 1): " << ma(0,4) << std::endl;
    std::cout << "Bottom (should be 3): " << ma(19,2) << std::endl;
    std::cout << "Left (should be 2): " << ma(4,0) << std::endl;
    std::cout << "Right (should be 4): " << ma(2,19) << std::endl;

    Kokkos::fence();

  }
  Kokkos::finalize();
  return 0;
}
