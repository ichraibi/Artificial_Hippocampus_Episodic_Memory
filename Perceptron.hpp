#ifndef PERCEPTRON_HPP_
#define PERCEPTRON_HPP_

#include <vector>
#include <iostream>


#include "Neuron.hpp"

class Perceptron
{   
	private:
            int nb_neurons;
            double learning_rate;
            std::vector<Neuron*> list_neurons;
            std::vector<double> output;
            
	public:
            Perceptron(unsigned int nb_neurons, double learning_rate, double threshold);
            ~Perceptron();
            std::vector<double> process(const std::vector<double> & input, bool learn, std::vector<double> wanted_out);
                
                
                
};

#endif
