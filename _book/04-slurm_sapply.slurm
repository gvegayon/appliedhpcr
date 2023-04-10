#!/bin/sh
#SBATCH --job-name=slurm_sapply
#SBATCH --time=00:10:00

module load usc r
Rscript --vanilla 04-slurm_sapply.R

