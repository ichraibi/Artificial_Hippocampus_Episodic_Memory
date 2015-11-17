#include "Hippocampus_Perceptron.hpp"
//#include "MemoryDyn.cpp"

#include "Math.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cmath>

Hippocampus_Perceptron::Hippocampus_Perceptron(unsigned int nb_neurons_input, unsigned int nb_neurons_output, double ca1_learning_rate, double learning_treshold, double perceptron_threshold) : 
        Hippocampus(nb_neurons_input, nb_neurons_output)
{ 
    this->ca1_learning_treshold = learning_treshold;
    //CA1 using the perceptron
    this->ca1_perceptron_CS = new CA1_Perceptron(nb_neurons_input, ca1_learning_rate, perceptron_threshold);
    this->ca1_perceptron_US = new CA1_Perceptron(nb_neurons_output, ca1_learning_rate, perceptron_threshold);      
}

Hippocampus_Perceptron::~Hippocampus_Perceptron()
{

    delete this->ca1_perceptron_CS;
    delete this->ca1_perceptron_US;
}

//process with CA1 as a perceptron
void Hippocampus_Perceptron::process(const std::vector<double> & input) {
        //std::cout<<"process fils"<< std::endl;
        size_t i, size_l, size_ortho_input;        
        size_ortho_input=0;
        this->hippocampus_output.clear();
        this->hippocampus_input= input;
        std::vector<std::vector<double> > list_of_associated_inputs = std::vector<std::vector<double> >(0, std::vector<double>(0, 0.0));
        list_of_associated_inputs = this->enthorhinal_cortex->process_in(this->hippocampus_input);      
        bool store =  this->enthorhinal_cortex->get_store();     
        
        size_l = list_of_associated_inputs.size();
        if (size_l==2)
        {
            DG_output.clear();       
            for (i=0; i< size_l ;i++)
            {
                std::vector<double> an_input = list_of_associated_inputs[i];
                this->dg->process(an_input);
                std::vector<double> an_input_orthogonalized = this->dg->get_output();
                if (size_ortho_input< an_input_orthogonalized.size())
                        size_ortho_input = an_input_orthogonalized.size();
                                
                DG_output.push_back(an_input_orthogonalized);
            
                an_input.clear();
                an_input_orthogonalized.clear();
            }
            
            this->ca3->process(DG_output, store, size_ortho_input);
            
            std::vector<double> input_CS = list_of_associated_inputs[0];
            std::vector<double> input_US = list_of_associated_inputs[1];
            
            Math math_tools;
           
            std::vector<double> CA3_output_CS = this->ca3->get_output_CS();
            std::vector<double> CA3_output_US = this->ca3->get_output_US();
            //evaluation of CA3 capacity
            if(store)
            {
                if (math_tools.control_vectors(DG_output[0], CA3_output_CS)==0)
                {
                    diff_DG_CA3_CS++;
                }
                if(math_tools.control_vectors(DG_output[1], CA3_output_US)==0)
                {
                    diff_DG_CA3_US++;
                }
            }
         
            //CA1 using a perceptron
            std::vector<double> CA1_output_CS =  this->ca1_perceptron_CS->process(CA3_output_CS, store, input_CS);
            std::vector<double> CA1_output_US =  this->ca1_perceptron_US->process(CA3_output_US, store, input_US);
          
            this->hippocampus_output= this->enthorhinal_cortex->process_out(CA1_output_CS,CA1_output_US);         
            double threshold = 0.0;
         
            for (i = 0; i < this->hippocampus_output[1].size(); i++)
            {
                    threshold += this->hippocampus_output[1][i];
            }

        } 
}


double Hippocampus_Perceptron::get_ca1_learning_treshold() {
    return this->ca1_learning_treshold;
}
