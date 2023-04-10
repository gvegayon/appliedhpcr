#!/bin/sh
#SBATCH --job-name=sapply
#SBATCH --time=00:10:00

module load usc r
Rscript --vanilla 01-sapply.R

