#include <Rcpp.h>
#include <random>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Rcpp;

// [[Rcpp::plugins(openmp)]]

// [[Rcpp::export]]
std::vector<double> parallel_rand(
    int n,
    int ncores,
    int seed
) {
  
#ifdef _OPENMP
  omp_set_num_threads(ncores);
#endif
  
  // Setting the parallel engine -----------------------------------------------
  std::vector< size_t > seeds;
  std::mt19937 engine;
  std::uniform_real_distribution<> dunif(0.0, 1.0);
  
  // Setting the seed
  engine.seed(seed);
  
  // We use the #ifdef _OPENMP to check whether OMP is supported
#ifdef _OPENMP
  int effective_ncores = ncores;
#else
  int effective_ncores = 1;
#endif
  
  // Maximum size_t in this machine
  double biggest_size_t = static_cast<double>(
    std::numeric_limits<size_t>::max()
  );
  
  for (int i = 1; i < effective_ncores; ++i) {
    
    // Uniform number between [0, biggest_size_t) 
    size_t seed_i = static_cast<size_t>(
      std::floor(biggest_size_t * dunif(engine))
    );
    
    // Saving the seed
    seeds.push_back(seed_i);
    
  }
  
  // Figuring out how many replicates ------------------------------------------
  std::vector< size_t > nreplicates(effective_ncores, 0);
  std::vector< size_t > cumsum(effective_ncores, 0);
  size_t sums = 0u;
  
  for (int i = 0; i < effective_ncores; ++i) {
    
    nreplicates[i] = static_cast<size_t>(
      std::floor(n/effective_ncores)
    );
    
    sums += nreplicates[i];
    
    // We will use this to keep track from where each thread should start writing.
    if (i > 0)
      cumsum[i] += cumsum[i - 1] + nreplicates[i - 1];
    
  }
  
  if (sums < n)
    nreplicates[effective_ncores - 1] += (n - sums);
  
  // Making room ---------------------------------------------------------------
  std::vector< double > res(n);
  
  // Running the experiment ----------------------------------------------------
#pragma omp parallel shared(res, nreplicates, seeds, cumsum) \
  firstprivate(dunif, engine) default(none)
  {
    
    // Getting the thread number
    auto iam = omp_get_thread_num();
    
    // Setting the seed (but not the master since we already did)
    if (iam != 0)
      engine.seed(seeds[iam]);
    
    for (int i = 0; i < nreplicates[iam]; i++)
      res.at(i + cumsum[iam]) = dunif(engine);
    
  }
  
  return res;
  
}

/***R

ans <- parallel_rand(1000, 4, 22)

nsims <- 1e5
res <- microbenchmark::microbenchmark(
  "C++ 4 threads" = parallel_rand(nsims, 4, 22),
  "C++ 2 threads" = parallel_rand(nsims, 2, 22),
  "C++ 1 thread"  = parallel_rand(nsims, 1, 22),
  "R runif"       = runif(nsims),
  times = 500
)

print(res, unit = "relative")
boxplot(
  res, log=TRUE, ylab = "Log Time (s)", unit = "s",
  main = "Pseudo-RNG Uniform (0, 1)",
  sub  = sprintf(
    "(Generating %s Unif() numbers using C++ with OpenMP vs R)",
    formatC(nsims, format = "d", big.mark = ",")
  )
)

*/

