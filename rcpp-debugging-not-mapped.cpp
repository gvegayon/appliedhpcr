#include <Rcpp.h>

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector faulty_program(int n) {

    // Here is the faulty line
    NumericVector * x_ptr;
        
    return *x_ptr;

}

/***R
# Calling the faulty program
faulty_program(10)
*/