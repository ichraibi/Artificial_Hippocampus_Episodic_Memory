#ifndef NEURON_HPP
#define	NEURON_HPP

#include <vector>

class Neuron
{   
	private:
		double threshold;
		int number;
		std::vector<double> wheights;
                double output_obtained;
                double learning_rate;
                
	public:
		Neuron(int number, double threshold, double size_weights_list, double learning_rate);
		~Neuron();
		int get_number();
                double process(const std::vector<double> & input, bool learn, double wanted_out);
                std::vector<double> learn(const std::vector<double> & input, double wanted_out);
                 std::vector<double> get_weight_matrix();
                
};

#endif	

