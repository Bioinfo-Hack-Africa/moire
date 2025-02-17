#pragma once

#ifndef CHAIN_H_
#define CHAIN_H_

#include "combination_indices_generator.h"
#include "genotyping_data.h"
#include "parameters.h"
#include "prob_any_missing.h"
#include "sampler.h"

#include <Rcpp.h>

class Chain
{
   private:
    GenotypingData genotyping_data;
    Parameters params;
    Sampler sampler;
    probAnyMissingFunctor probAnyMissing_;
    std::vector<double> prVec_{};

    CombinationIndicesGenerator allele_index_generator_;

    void initialize_latent_genotypes();
    void initialize_p();
    void initialize_m();
    void initialize_eps_neg();
    void initialize_eps_pos();
    void initialize_r();
    void initialize_likelihood();

    double calc_transmission_process(
        std::vector<int> const &allele_index_vec,
        std::vector<double> const &allele_frequencies, int coi,
        double relatedness);

    double calc_observation_process(std::vector<int> const &allele_index_vec,
                                    std::vector<int> const &obs_genotype,
                                    double epsilon_neg, double epsilon_pos);

    double calc_genotype_log_pmf(std::vector<int> const &allele_index_vec,
                                 std::vector<int> const &obs_genotype,
                                 double epsilon_pos, double epsilon_neg,
                                 int coi, double relatedness,
                                 std::vector<double> const &allele_frequencies);

    std::vector<double> calc_obs_genotype_lliks(
        std::vector<int> const &obs_genotype,
        std::vector<std::vector<int>> const &true_genotypes, double epsilon_neg,
        double epsilon_pos, int num_genotypes);

    double calculate_llik(int num_samples);
    double calc_old_likelihood();
    double calc_new_likelihood();
    double calc_old_prior();
    double calc_new_prior();
    double calculate_new_posterior();
    double calculate_old_posterior();

    void calculate_genotype_likelihood(int sample_idx, int locux_idx);
    void calculate_eps_neg_likelihood(int sample_idx);
    void calculate_eps_pos_likelihood(int sample_idx);
    void calculate_coi_likelihood(int sample_idx);
    void calculate_mean_coi_likelihood();

    void save_genotype_likelihood(int sample_idx, int locus_idx);
    void save_eps_neg_likelihood(int sample_idx);
    void save_eps_pos_likelihood(int sample_idx);
    void save_coi_likelihood(int sample_idx);
    void save_mean_coi_likelihood();

    void restore_genotype_likelihood(int sample_idx, int locus_idx);
    void restore_eps_neg_likelihood(int sample_idx);
    void restore_eps_pos_likelihood(int sample_idx);
    void restore_coi_likelihood(int sample_idx);
    void restore_mean_coi_likelihood();

   public:
    std::vector<double> genotyping_llik_old{};
    std::vector<double> genotyping_llik_new{};

    std::vector<double> eps_neg_prior_old{};
    std::vector<double> eps_neg_prior_new{};
    std::vector<double> eps_pos_prior_old{};
    std::vector<double> eps_pos_prior_new{};
    std::vector<double> coi_prior_new{};
    std::vector<double> coi_prior_old{};

    double llik;
    double prior;
    double temp;

    // Latent Genotypes
    std::vector<std::vector<std::vector<int>>> latent_genotypes_old{};
    std::vector<std::vector<std::vector<int>>> latent_genotypes_new{};
    std::vector<std::vector<double>> lg_adj_old{};
    std::vector<std::vector<double>> lg_adj_new{};

    // COI
    std::vector<int> m{};
    std::vector<int> m_accept{};
    double mean_coi;
    double mean_coi_var;
    double mean_coi_accept;
    double mean_coi_hyper_prior_old;
    double mean_coi_hyper_prior_new;

    // Relatedness
    std::vector<double> r{};
    std::vector<int> r_accept{};
    std::vector<double> r_var{};

    std::vector<int> m_r_accept{};
    std::vector<double> m_r_var{};

    // Allele Frequencies
    std::vector<std::vector<double>> p{};
    std::vector<double> prop_p{};
    std::vector<std::vector<double>> p_prop_var{};
    std::vector<std::vector<int>> p_accept{};
    std::vector<std::vector<int>> p_attempt{};

    // Epsilon Positive
    // double eps_pos;
    std::vector<double> eps_pos{};
    std::vector<int> eps_pos_accept{};
    std::vector<double> eps_pos_var{};

    // Epsilon Negative
    // double eps_neg;
    std::vector<double> eps_neg{};
    std::vector<int> eps_neg_accept{};
    std::vector<double> eps_neg_var{};

    std::vector<int> sample_accept{};

    Chain(GenotypingData genotyping_data, Parameters params, double temp = 1.0);
    void update_m(int iteration);
    void update_r(int iteration);
    void update_m_r(int iteration);
    void update_p(int iteration);
    void update_eps(int iteration);
    void update_eps_pos(int iteration);
    void update_eps_neg(int iteration);
    void update_samples(int iteration);
    void update_mean_coi(int iteration);
    double get_llik();
    double get_prior();
    double get_posterior();

    void set_llik(double llik);
    void set_temp(double temp);
    double get_temp();
};

#endif  // CHAIN_H_
