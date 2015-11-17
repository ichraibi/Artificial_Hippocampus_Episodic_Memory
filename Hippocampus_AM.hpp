#ifndef HIPPOCAMPUS_AM_HPP_
#define HIPPOCAMPUS_AM_HPP_

#include <vector>
//#include "MemoryDyn.hpp"
#include "EnthorhinalCortex.hpp"
#include "DG.hpp"
#include "CA1.hpp"
#include "CA1_Perceptron.hpp"
#include "CA3.hpp"
#include "Hippocampus.hpp"

class Hippocampus_AM : public Hippocampus {
	protected :
		CA1 *ca1;
                
	public :
		Hippocampus_AM(unsigned int nb_neurons_input, unsigned int nb_neurons_output);
                ~Hippocampus_AM();
		void process(const std::vector<double> & input);
                void display_CA1_Matrix_properties(double nb_vectors);
              
               
                
};

#endif
