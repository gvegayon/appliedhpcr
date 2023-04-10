#!/bin/sh
#SBATCH --output=00-hello-world.out
module load usc r
Rscript -e "paste('Hello from node', Sys.getenv('SLURMD_NODENAME'))"

