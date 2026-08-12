#!/bin/bash
#SBATCH --job-name=hello
#SBATCH --account=project_2019754
#SBATCH --partition=gpumedium
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --gres=gpu:gh200:1
#SBATCH --time=00:02:00
#SBATCH --out=heat2_collapse.out

# Enable OpenMP offload debugging by uncommenting the line below
export NVCOMPILER_ACC_NOTIFY=3
export OMP_NUM_TEAMS=16

# Run the program
srun ./heat_collapse.o
