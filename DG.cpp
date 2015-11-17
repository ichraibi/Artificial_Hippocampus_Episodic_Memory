#include "DG.hpp"

DG::DG(){
	
}

DG::~DG(){

}


void DG::process(const std::vector<double> & input) {
  //  std::cout << " DG- Process -------------------- "<< std :: endl; 
    unsigned int i, j, input_size;
    unsigned int k = 0;
    input_size = input.size();
    
    unsigned int DG_size = input_size*(input_size-1)/2;
    //std::cout << "DG_size : "<< DG_size << std :: endl;
    this->_output.resize(DG_size, 0.0);

    for ( i = 0; i < input_size ; i++) 
    {
	for (j = i+1; j < input_size ; j++) 
        {
                if (input[i]==1 && input[j]==1)
                        this->_output[k]=1;
                else
                        this->_output[k]=0;

                k++;
	}
    }
     
   
    
}

std::vector<double> DG::get_output() {
	return this->_output;
}

void DG::raz() {
	unsigned int i;
	for (i = 0; i < this->_output.size(); i++) {
		this->_output[i] = 0.0;
	}
}


