#ifndef CA1_Perceptron_HPP_
#define CA1_Perceptron_HPP_
#include <iostream>
#include <vector>
#include "Perceptron.hpp"

class CA1_Perceptron
{   
	private:
		Perceptron* perceptron;
		std::vector<double> output;
	public:
		CA1_Perceptron(unsigned int size, double learning_rate, double perceptron_threshold);
		~CA1_Perceptron();
                
                std::vector<double> process(const std::vector<double> & input, bool learn,
				std::vector<double> wanted_out);
		
};

#endif