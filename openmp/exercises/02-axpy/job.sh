#!/bin/bash
#SBATCH --job-name=hello
#SBATCH --account=project_2019754
#SBATCH --partition=gpumedium
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --gres=gpu:gh200:1
#SBATCH --time=00:02:00
#SBATCH --out=omp2.out

# Enable OpenMP offload debugging by uncommenting the line below
export NVCOMPILER_ACC_NOTIFY=3

# Run the program
srun ./omp_test2.o
