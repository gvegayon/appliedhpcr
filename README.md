# Applied HPC with R: C++, Parallelism, and Performance

[![Read online](https://img.shields.io/badge/read-book--hpc.ggvy.cl-blue)](https://book-hpc.ggvy.cl)
[![Leer en español](https://img.shields.io/badge/leer-en%20espa%C3%B1ol-blue)](https://book-hpc.ggvy.cl/es/)
[![PDF](https://img.shields.io/badge/download-PDF-red)](https://book-hpc.ggvy.cl/Applied-HPC-with-R.pdf)

**Applied HPC with R** is a free, open-source book by [George G. Vega Yon](https://ggvy.cl) on making R code faster. It grew out of talks and lectures given at USC and the University of Utah, and covers:

- **Fundamentals**: [profiling R code](https://book-hpc.ggvy.cl/profiling.html) with profvis and [writing efficient R code](https://book-hpc.ggvy.cl/efficiency.html).
- **Parallel computing**: [an introduction to HPC](https://book-hpc.ggvy.cl/intro.html) and [the parallel package](https://book-hpc.ggvy.cl/parallel-pkg.html) (PSOCK/fork clusters, `parLapply`, `mclapply`, parallel RNG).
- **Working with a cluster**: [Slurm fundamentals](https://book-hpc.ggvy.cl/slurm-fundamentals.html) and [running R on Slurm](https://book-hpc.ggvy.cl/slurm-simpi.html) with `sbatch` and [slurmR](https://github.com/USCbiostats/slurmR).
- **Using C++**: [speeding up R with Rcpp](https://book-hpc.ggvy.cl/rcpp-part1.html), RcppArmadillo and OpenMP, and [debugging C++ code with Valgrind and GDB](https://book-hpc.ggvy.cl/rcpp-debugging.html).

## Languages / Idiomas

- **English** (original): [book-hpc.ggvy.cl](https://book-hpc.ggvy.cl) · source in the main directory.
- **Español**: [book-hpc.ggvy.cl/es](https://book-hpc.ggvy.cl/es/) · código fuente en [`es/`](es/).

## Citation

If you use this book, please cite it. GitHub's "Cite this repository" button (from [`CITATION.cff`](CITATION.cff)) provides APA and BibTeX formats:

> Vega Yon, G. G. (2026). *Applied HPC with R: C++, Parallelism, and Performance*. https://book-hpc.ggvy.cl

## Building the Book

To build the English version:
```bash
quarto render
```

To build the Spanish version:
```bash
cd es/
quarto render
```

## Contributing

Contributions are welcome! Please see the individual language directories for specific guidelines.

For the Spanish translation, see [es/README.md](es/README.md).