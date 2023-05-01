#include <Rcpp.h>

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector faulty_program(int n) {

    // Here is the faulty line
    NumericVector * x_ptr = new NumericVector(n);
    
    NumericVector res = *x_ptr;
    delete x_ptr;
    
    return res;

}

/***R
# Calling the faulty program
faulty_program(10)
*/