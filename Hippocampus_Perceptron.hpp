#ifndef HIPPOCAMPUS_Perceptron_HPP_
#define HIPPOCAMPUS_Perceptron_HPP_

#include <vector>

#include "EnthorhinalCortex.hpp"
#include "DG.hpp"
#include "CA1.hpp"
#include "CA1_Perceptron.hpp"
#include "CA3.hpp"
#include "Hippocampus.hpp"

class Hippocampus_Perceptron : public Hippocampus {
	protected:
		
                CA1_Perceptron *ca1_perceptron_CS;
                CA1_Perceptron *ca1_perceptron_US;
                double ca1_learning_treshold;
                

	public:
		Hippocampus_Perceptron(unsigned int nb_neurons_input, unsigned int nb_neurons_output,double ca1_learning_rate, double learning_threshold,double perceptron_threshold);
                
                ~Hippocampus_Perceptron();
                
		void process(const std::vector<double> & input);

                double get_ca1_learning_treshold();

};

#endif
