#ifndef DG_HPP_
#define DG_HPP_

#include <vector>

class DG
{   
	private: 
		
		std::vector<double> _output;
                //std::vector<std::vector<double> > CS_matrix;
	public:
		DG();
                ~DG();
                
		void process(const std::vector<double> & input);
		std::vector<double> get_output();
		void raz();
                double get_Time_Constant();
          
                
};

#endif
