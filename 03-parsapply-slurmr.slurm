#!/bin/sh
#SBATCH --job-name=parsapply
#SBATCH --time=00:10:00

module load usc r
Rscript --vanilla 03-parsapply-slurmr.R

