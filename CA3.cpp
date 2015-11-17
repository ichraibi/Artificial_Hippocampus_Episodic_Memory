#include <iostream>
#include <cmath>
#include <cstdlib>

#include "CA3.hpp"
#include "Math.hpp"


CA3::CA3(unsigned int nb_neurons_input, unsigned int nb_neurons_output) {
    
    this->weight_matrix = std::vector<std::vector<double> >(nb_neurons_input, std::vector<double>(nb_neurons_output, 0.0));
    this->CS_matrix = std::vector<std::vector<double> >(nb_neurons_input, std::vector<double>(nb_neurons_input, 0.0));
    this->output_US.resize(nb_neurons_output, 0.0);
    this->output_CS.resize(nb_neurons_input, 0.0);
}

CA3::~CA3() {
 
}
   

void CA3::process(std::vector<std::vector<double> > &List_orthogonalized_vector, bool store, unsigned int size) throw (InputSizeMismatchException){
 //   std::cout <<"CA3 PROCESS ----------------------------------------"<< std::endl ;
    
    Math mathTools;
  
    size_t i, j;
    double input_sum;
    
    std::vector<double> vector_CS = List_orthogonalized_vector[0];//CS
    std::vector<double> vector_US = List_orthogonalized_vector[1];//US or a void vector
  
    //nbre of active neurons in the vector_CS
    double threshold = get_vector_threshold(vector_CS);
  
    
    if (threshold > 0.0) {
        //if threshold> 0.0 it means that the input contains data, so process can be launched
       //we first remember the previous situation similar to the actual
       
        if (store) {    
            //learn of the CS that have an US
            this->learn(vector_CS, vector_CS, this->CS_matrix);
            
        }
        for (j = 0; j < this->output_CS.size(); j++) {
            input_sum = 0.0;

            for (i = 0; i < vector_CS.size(); i++) {
                input_sum += this->CS_matrix[i][j] * vector_CS[i];
            }

            double result_Heaviside = mathTools.heaviside(input_sum - threshold);
            this->output_CS[j] += (-this->output_CS[j] + result_Heaviside );
        }

        //--------------------------------------------------------------------------
        //then we remember the US of that situation
        //question : do I keep the vector_CS even if it is partial or do I use the remembered vector ?
        if (store) {    
            //learn of the association between the CS and the US _ hetero assocative memory
            //std::cout<<" STORAGE PROCESS "<<std::endl;
            this->learn(vector_CS, vector_US, this->weight_matrix);
        }

        for (j = 0; j < this->output_US.size(); j++) {
            input_sum = 0.0;

            for (i = 0; i < vector_CS.size(); i++) {
                input_sum += this->weight_matrix[i][j] * vector_CS[i];
            }

            double result_Heaviside = mathTools.heaviside(input_sum - threshold);
            this->output_US[j] += (-this->output_US[j] + result_Heaviside );
        }

    }
    else {
        //if threshold<0 0.0 it means that there is no data to learn (the input is empty )
        for (j = 0; j < this->output_US.size(); j++) {
            this->output_US[j] += (-this->output_US[j]);
        }
        
        for (j = 0; j < this->output_CS.size(); j++) {
            this->output_CS[j] += (-this->output_CS[j]);
        }
    }
    
}

void CA3::learn(std::vector<double>& vector_A , std::vector<double>& vector_B, std::vector<std::vector<double> > & matrix) {

    size_t i, j;
 
    for (i=0 ; i<vector_A.size(); i++)
    {
        for (j=0 ; j<vector_B.size(); j++)
        {
            if (vector_A[i]*vector_B[j]) {
                matrix[i][j] += vector_A[i]*vector_B[j];
 
                if (matrix[i][j] > 1.0)
                       matrix[i][j] = 1.0;
            }
        }
    }
       
}



std::vector<double> CA3::get_output_US() {
    return this->output_US;
}

std::vector<double> CA3::get_output_CS() {
    return this->output_CS;
}

std::vector<std::vector<double> > CA3::get_weight_matrix() {
    return this->weight_matrix;
}

std::vector<std::vector<double> > CA3::get_CS_matrix() {
    return this->CS_matrix;
}


double CA3::get_vector_threshold(std::vector<double > &vector){
    double threshold = 0.0;
         
    for (size_t i = 0; i < vector.size(); i++)
    {
            threshold += vector[i];
    }
    
    return threshold;
}
