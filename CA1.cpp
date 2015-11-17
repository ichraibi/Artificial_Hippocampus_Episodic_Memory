#include "CA1.hpp"
#include "Perceptron.hpp"
#include "Math.hpp"

void __print_vector(std::vector<double> v, std::ostream& o);

CA1::CA1(unsigned int size_output_US, unsigned int size_input_US,unsigned int size_output_CS,unsigned int size_input_CS) 
{
        //size_output_US: non orthogonalized US
        //size_input_US : size of the orthogonalized US (the same size as CA3 output)
    
        //size_output_CS: non orthogonalized CS
        //size_input_CS : size of the orthogonalized CS (the same size as CA3 output)
	this->output_US.resize(size_output_US, 0.0);
        this->output_CS.resize(size_output_CS, 0.0);
        this->weight_US_matrix = std::vector<std::vector<double> >(size_input_US, std::vector<double>(size_output_US, 0.0));
        this->weight_CS_matrix = std::vector<std::vector<double> >(size_input_CS, std::vector<double>(size_output_CS, 0.0));
        
}

CA1::~CA1() 
{

}

void CA1::process(const std::vector<double> & CA3_output_US, bool learn,
		std::vector<double> & EC_input_US, std::vector<double> CA3_output_CS, std::vector<double> & EC_input_CS) {
 
    //CA3_output_US = CA3 output = the ortogonalized US
    //EC_input_US = the prediction non orthogonalized from EC
    
    //CA3_output_CS  = the original orthogonalized CS associated with the US
    //EC_input_CS = the CS received by the EC, Non orthogonalized
    
   double input_sum;  
   size_t j, i;
   Math mathTools;
   double threshold_US = get_vector_threshold(CA3_output_US);
   double threshold_CS = get_vector_threshold(CA3_output_CS);
   
   if(threshold_CS > 0.0)
   {
            if (learn) {    
                this->learn(CA3_output_CS, EC_input_CS, this->weight_CS_matrix);
            }

            //the remind process is always active
            for (j = 0; j < this->output_CS.size(); j++) {
                input_sum = 0.0;

                for (i = 0; i < CA3_output_CS.size(); i++) {
                    input_sum += this->weight_CS_matrix[i][j] * CA3_output_CS[i];
                }

                double result_Heaviside = mathTools.heaviside(input_sum - threshold_CS);
                this->output_CS[j] += (-this->output_CS[j] + result_Heaviside );

            }
    }
    else {
        for ( j = 0; j < this->output_CS.size(); j++) {
            this->output_CS[j] += (-this->output_CS[j]);
        }
    }
  
   
   
   if (threshold_US > 0.0) {
        //if threshold> 0.0 it means that the input contains data, so process can be launched
       
        if (learn) {    
            this->learn(CA3_output_US, EC_input_US, this->weight_US_matrix);
        }
        
        //the remind process is always active
        for (j = 0; j < this->output_US.size(); j++) {
            input_sum = 0.0;

            for (i = 0; i < CA3_output_US.size(); i++) {
                input_sum += this->weight_US_matrix[i][j] * CA3_output_US[i];
            }

            double result_Heaviside = mathTools.heaviside(input_sum - threshold_US);
            this->output_US[j] += (-this->output_US[j] + result_Heaviside );

        }
        
    }
    else {
        //if threshold<0 0.0 it means that there is no data to learn (the input is empty )
        for ( j = 0; j < this->output_US.size(); j++) {
            this->output_US[j] += (-this->output_US[j]);
        }
        
    }
    
}

void CA1::learn(const std::vector<double> & vector_A , std::vector<double> & vector_B, std::vector<std::vector<double> > & matrix) {
    
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

double CA1::get_vector_threshold(const std::vector<double> & vector){
    double threshold = 0.0;
         
    for (size_t i = 0; i < vector.size(); i++)
    {
            threshold += vector[i];
    }
    
    return threshold;
}


std::vector<double> CA1::get_output_CS()
{
    return this->output_CS;
}

std::vector<double> CA1::get_output_US()
{
    return this->output_US;
}

std::vector<std::vector<double> > CA1::get_weight_CS_matrix() {
    return this->weight_CS_matrix;
}

std::vector<std::vector<double> > CA1::get_weight_US_matrix() {
    return this->weight_US_matrix;
}