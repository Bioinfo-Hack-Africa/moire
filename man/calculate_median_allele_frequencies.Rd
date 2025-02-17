% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/summary.R
\name{calculate_median_allele_frequencies}
\alias{calculate_median_allele_frequencies}
\title{Calculate the geometric median of the posterior distribution of allele
frequencies}
\usage{
calculate_median_allele_frequencies(mcmc_results, merge_chains = TRUE)
}
\arguments{
\item{mcmc_results}{Result of calling run_mcmc()}

\item{merge_chains}{boolean indicating that all chain results should be merged}
}
\description{
Calculate the geometric median of the posterior distribution of allele
frequencies
}
\details{
Returns the geometric median of the posterior distribution, defined
as the point minimizing the L2 distance from each sampled point.
}
