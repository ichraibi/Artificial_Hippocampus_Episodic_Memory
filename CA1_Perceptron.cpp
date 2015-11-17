#include "CA1_Perceptron.hpp"
#include "Perceptron.hpp"

#include <vector>
#include <iostream>

CA1_Perceptron::CA1_Perceptron(unsigned int size, double learning_rate, double perceptron_threshold)
{
	this->perceptron = new Perceptron(size, learning_rate, perceptron_threshold);
	this->output.resize(size, 0.0);
        
}

CA1_Perceptron::~CA1_Perceptron() 
{
    delete this->perceptron;
}

std::vector<double> CA1_Perceptron::process(const std::vector<double> & input, bool learn, std::vector<double>  wanted_out)
{
       this->output=this->perceptron->process(input,learn, wanted_out);
        return this->output;
}

