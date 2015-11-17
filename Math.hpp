#ifndef MATH_HPP_
#define MATH_HPP_

#include <vector>
#include "algorithm"
#include <iostream>
#include <fstream>

class Math
{   
	private: 
		
	public:
            Math();
            ~Math();
            double heaviside(double x);
            std::vector<std::vector<double>     > get_transposed_matrix(std::vector<std::vector<double>   > original_matrix);
            std::vector<std::vector<double>     > sum_of_matrix(std::vector<std::vector<double> >& matrix_1, std::vector<std::vector<double>   >& matrix_2);  
            void display_matrix(std::vector<std::vector<double>     > & Matrix);
            void display_vector(std::vector<double> & Vector);
            double compute_HD(std::vector<double>& original_CS, std::vector<double>& output_CS);
            float compute_average_HD(std::vector<double>& table_HD);
            
            double get_vector_active_unit_nbre(std::vector<double>& a_vector);
            double get_Matrix_active_unit_nbre(std::vector<std::vector<double> >& matrix);
            
            double get_matrix_rate_saturation(std::vector<std::vector<double> >& matrix);
            void get_AM_loading_density(double nb_unit_active, double vector_size, double nb_learned_vectors);//AM = autoassociative memory
            void get_HM_loading_density(double input_vector_nb_unit_active, double input_vector_size, double output_vector_nb_unit_active, double output_vector_size, double nb_learned_vectors);//HM = heteroassociative memory
            double get_AM_estimated_nb_learned_pattern(double input_vector_size);
            double get_HM_estimated_nb_learned_pattern(double input_vector_size, double output_vector_size);
            void display_matrix_properties(std::vector<std::vector<double> >& matrix);
            bool control_vectors(std::vector<double>& original, std::vector<double>& output);
            std::vector<double> compute_haming_distance(std::vector<double>& original_vector, std::vector<double>& output_vector, int number, std::vector<double>& table_HD) ;
            void generate_random_vector(std::vector<double> &a_vector, int vector_size, int nb_unit_active);
            std::vector<std::vector<double> > generation_of_random_vectors(std::vector<std::vector<double> >& random_CSs,std::vector<std::vector<double> >& random_USs, double CS_size, double US_size, unsigned int nb_total_vectors, double nb_unit_activ_per_CS, double nb_unit_activ_per_US);
            std::vector<std::vector<double> > generate_disturbed_random_vectors(std::vector<std::vector<double> > & random_vectors, int vector_size, int nb_unit_active, double percent_of_distortion);
};

#endif
