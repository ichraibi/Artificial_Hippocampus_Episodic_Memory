#include "Hippocampus_AM.hpp"
//#include "MemoryDyn.cpp"
#include "Math.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

Hippocampus_AM::Hippocampus_AM(unsigned int nb_neurons_input, unsigned int nb_neurons_output) :
        Hippocampus(nb_neurons_input, nb_neurons_output)
{ 
    //AM = Associative Memory
     //CA1 with an heteroassociative memory
    
     this->ca1 = new CA1(nb_neurons_output,nb_neurons_output*(nb_neurons_output-1)/2, nb_neurons_input, nb_neurons_input*(nb_neurons_input-1)/2 ); 
}

Hippocampus_AM::~Hippocampus_AM() 
{
    
    delete this->ca1;
    
}

void Hippocampus_AM::process(const std::vector<double> & input) {
        Math math_tools;
    
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
            std::vector<double> CA3_output_CS = this->ca3->get_output_CS();
            std::vector<double> CA3_output_US = this->ca3->get_output_US();
            
            //evaluation of CA3 capacity
            if(store)
            {
                if (math_tools.control_vectors(DG_output[0], CA3_output_CS)==0)
                {
                    this->diff_DG_CA3_CS++;
                }
               
                if(math_tools.control_vectors(DG_output[1], CA3_output_US)==0)
                {
                    this->diff_DG_CA3_US++;
                }
            }
            
            this->ca1->process(this->ca3->get_output_US(), store, input_US, this->ca3->get_output_CS(), input_CS);
            std::vector<double> CA1_output_CS = this->ca1->get_output_CS();
            std::vector<double> CA1_output_US = this->ca1->get_output_US(); 
            
            this->hippocampus_output= this->enthorhinal_cortex->process_out(CA1_output_CS,CA1_output_US);
            double threshold = 0.0;
         
            for (i = 0; i < this->hippocampus_output[1].size(); i++)
            {
                    threshold += this->hippocampus_output[1][i];
            }
   
        } 
}


void Hippocampus_AM::display_CA1_Matrix_properties(double nb_vectors)
{
    Math math_tools;
    std::cout<<" MATRIX of CA1 ---------------------------------------------------------------------------------------"<<std::endl;
    std::cout<<" CSs_matrix"<<std::endl;
    std::vector<std::vector<double> > CSs_matrix = this->ca1->get_weight_CS_matrix();
    double CSs_matrix_estimated_learned_pattern = math_tools.get_HM_estimated_nb_learned_pattern(CSs_matrix.size(), CSs_matrix[1].size());
  //  std::cout<<" CSs_matrix_estimated_learned_pattern "<< CSs_matrix_estimated_learned_pattern<<std::endl;
    math_tools.get_HM_loading_density(15,CSs_matrix.size(),6, CSs_matrix[1].size(),nb_vectors);
    math_tools.get_matrix_rate_saturation(CSs_matrix);
    
    std::cout<<" "<<std::endl;
    std::cout<<" USs_matrix"<<std::endl;
    std::vector<std::vector<double> > USs_matrix = this->ca1->get_weight_US_matrix();
    double USs_matrix_estimated_learned_pattern = math_tools.get_HM_estimated_nb_learned_pattern(USs_matrix.size(), USs_matrix[1].size());
//    std::cout<<" USs_matrix_estimated_learned_pattern "<< USs_matrix_estimated_learned_pattern<<std::endl;
    math_tools.get_HM_loading_density(6,USs_matrix.size(),4, USs_matrix[1].size(), nb_vectors);
    math_tools.get_matrix_rate_saturation(USs_matrix);
    std::cout<<" "<<std::endl;
}
