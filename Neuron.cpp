#include "Neuron.hpp"
#include <iostream>

Neuron::Neuron(int _number, double _threshold, double size_weights_list, double learning_rate) {
      
        this->number = _number;
        this->threshold = _threshold;
	this->wheights.resize(size_weights_list);
        this->output_obtained=0.0;
        this->learning_rate =learning_rate ;
}

Neuron::~Neuron() {
    
}

int Neuron::get_number(){
    return  this->number;
}


double Neuron::process(const std::vector<double> & input, bool learn, double wanted_out){
     
    if(learn)
    {
        this->wheights = this->learn(input,wanted_out);
    }
    else
    {
        double input_sum=0.0;
       
        for(int i =0; i<input.size(); i++)
        {
            input_sum += this->wheights[i]* input[i];
        }
        
        this->output_obtained = (input_sum > this->threshold) ? 1 : 0;
    
    }
    
    return this->output_obtained ;
    
}

std::vector<double> Neuron::learn(const std::vector<double> & input, double wanted_out)
{
    
    bool errors = true;
    int  cptrCycle(0);

    
    while (errors) {   //we continue until we have an error


        cptrCycle++;

        double input_sum=0.0;

        for(int i =0; i<input.size(); i++)
        {
            input_sum += this->wheights[i]* input[i];//sum of the weight
        }

        this->output_obtained = (input_sum > this->threshold) ? 1 : 0;

        
        for(std::size_t i =0; i<this->wheights.size(); i++)//modification of the synpatic weight
        {
          this->wheights[i]= this->wheights[i]+ this->learning_rate*(wanted_out - this->output_obtained)*input[i];               
        }
       
        if ((wanted_out - this->output_obtained) ==0)
        {
            errors = false;
        }

      }
   
  // std::cout << "Nb cycle in order to learn : " << cptrCycle << std::endl;
   return this->wheights;
}

 std::vector<double> Neuron::get_weight_matrix(){
    return this->wheights; 
 }