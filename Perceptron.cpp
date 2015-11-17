#include "Perceptron.hpp"

Perceptron::Perceptron(unsigned int nb_neurons, double learning_rate, double threshold) {
    
    this->learning_rate = learning_rate;
    
    this->nb_neurons = nb_neurons;
  
    for(int i =0; i<nb_neurons; i++)
    {
        double size = nb_neurons*(nb_neurons-1)/2;//size of inputs of every neuron;
        Neuron * a_neuron =  new Neuron(i , threshold, size, learning_rate);
        this->list_neurons.push_back(a_neuron);
    }
 
    this->output.resize(nb_neurons, 0.0);
}

Perceptron::~Perceptron() {
    for(int i =0; i< this->list_neurons.size(); i++)
    {
        Neuron * a_neuron =   this->list_neurons[i];
        delete a_neuron;
        
    }
     this->list_neurons.clear();
}

std::vector<double> Perceptron::process(const std::vector<double> & input, bool learn, std::vector<double> wanted_out) {
   
  
    for(int i =0; i<this->list_neurons.size(); i++)
    {
  
        Neuron* a_neuron = this->list_neurons[i];
        this->output[i] = a_neuron->process(input, learn, wanted_out[i]);
 
    }
    return this->output;
}