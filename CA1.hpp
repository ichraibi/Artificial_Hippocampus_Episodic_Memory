#ifndef CA1_HPP_
#define CA1_HPP_

#include <vector>
#include <iostream>
#include <fstream>
#include "Perceptron.hpp"

class CA1
{   
	private:
		std::vector<double> output_US;//the prediction 
                std::vector<double> output_CS;//the original CS non orthogonalized
                std::vector<std::vector<double> > weight_US_matrix;
                std::vector<std::vector<double> > weight_CS_matrix;

	public:
                CA1(unsigned int size_output_US, unsigned int size_input_US,
                                unsigned int size_output_CS,unsigned int size_input_CS); 
                ~CA1();
                
		void process(const std::vector<double> & input, bool learn,
				std::vector<double> & wanted_out, std::vector<double>  input_CS, std::vector<double> & wanted_CS);
		double get_vector_threshold(const std::vector<double> & vector);
                void learn(const std::vector<double>& vector_A , std::vector<double> & vector_B, std::vector<std::vector<double> > & matrix);
                
		std::vector<double> get_output_CS();
                std::vector<double> get_output_US();
                std::vector<std::vector<double> > get_weight_US_matrix();
                std::vector<std::vector<double> > get_weight_CS_matrix() ; 
};

#endif
