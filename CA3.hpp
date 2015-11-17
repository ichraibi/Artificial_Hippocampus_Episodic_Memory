#ifndef CA3_HPP_
#define CA3_HPP_

#include <vector>


class InputSizeMismatchException 
{ 
	public:
		unsigned int expected;
		unsigned int received;

		InputSizeMismatchException(unsigned int e, unsigned int r) : expected(e), received(r) { }
};

class CA3 {
	private:          
		std::vector<std::vector<double> > weight_matrix;
                std::vector<std::vector<double> > CS_matrix;
		std::vector<double> output_US;//the prediction
                std::vector<double> output_CS;//the most similar CS already stored
                
		
	public:
                CA3(unsigned int nb_neurons_input,unsigned int nb_neurons_output) ;
                ~CA3();
                
                void process(std::vector<std::vector<double> > &List_orthogonalized_vector, bool store, unsigned int size)throw (InputSizeMismatchException) ;
                void learn(std::vector<double>& vector_A, std::vector<double>& vector_B, std::vector<std::vector<double> > & matrix);   

		std::vector<double> get_output_US();
                std::vector<double> get_output_CS();
                
                double get_vector_threshold(std::vector<double > &vector);
                std::vector<std::vector<double> > get_weight_matrix();
                std::vector<std::vector<double> > get_CS_matrix() ; 
 };

#endif

