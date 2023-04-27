#include <Rcpp.h>
#include <random>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Rcpp;

// [[Rcpp::plugins(openmp)]]

// [[Rcpp::export]]
std::vector< std::vector<double> > parallel_rand(
    int n,
    int ncores,
    int seed
) {
  
#ifdef _OPENMP
  omp_set_num_threads(ncores);
#endif
  
  // Setting the parallel engine -----------------------------------------------
  std::vector< std::mt19937 > engines;
  std::uniform_real_distribution<> dunif(0.0, 1.0);
  
  engines.push_back(std::mt19937());
  engines[0].seed(seed);
  
  // We use the #ifdef _OPENMP to check whether OMP is supported
#ifdef _OPENMP
  int effective_ncores = ncores;
#else
  int effective_ncores = 1;
#endif
  
  // Setting one seed per engine (based on the original)
  for (int i = 1; i < effective_ncores; ++i) {
    
    engines.push_back(std::mt19937());
    size_t seed_i =
      static_cast<size_t>(
        std::floor(
          static_cast<double>(std::numeric_limits<size_t>::max()) *
            dunif(engines[0])
        )
      );
    
    engines[0+1].seed(seed_i);
    
  }
  
  // Figuring out how many replicates ------------------------------------------
  std::vector< size_t > nreplicates(effective_ncores, 0);
  std::vector< size_t > nreplicates_csum(effective_ncores, 0);
  size_t sums = 0u;
  for (int i = 0; i < effective_ncores; ++i)
  {
    nreplicates[i] = static_cast<size_t>(
      std::floor(n/effective_ncores)
    );
    
    // This takes the cumsum
    nreplicates_csum[i] = sums;
    
    sums += nreplicates[i];
    
  }
  
  if (sums < n)
    nreplicates[effective_ncores - 1] += (n - sums);
  
  // Making room ---------------------------------------------------------------
  std::vector< std::vector< double > > res(effective_ncores);
  for (int i = 0; i < effective_ncores; ++i)
    res[i].resize(nreplicates[i]);
  
  
  // Running the experiment ----------------------------------------------------
#pragma omp parallel shared(res, engines, nreplicates) firstprivate(dunif) default(none)
  {
    
    // Getting the thread number
    auto iam = omp_get_thread_num();
    
    for (int i = 0; i < nreplicates[iam]; i++)
      res[iam][i] = dunif(engines[iam]);
    
  }
  
  return res;

}

/***R

ans <- parallel_rand(1000, 4, 22)

res <- microbenchmark::microbenchmark(
  parallel_rand(100000, 4, 22),
  parallel_rand(100000, 2, 22),
  parallel_rand(100000, 1, 22)
)

print(res, unit = "relative")

*/

