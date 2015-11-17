#ifndef EnthorhinalCortex_HPP_
#define EnthorhinalCortex_HPP_

#include <vector>
#include <iostream>
#include <fstream>


class EnthorhinalCortex {
	private:
                std::vector<std::vector<double> > List_of_input;
                unsigned int size_CS;
                unsigned int size_US;
                bool store;

	public:
                EnthorhinalCortex(unsigned int size_CS, unsigned int size_US);
                ~EnthorhinalCortex();
                
                std::vector<std::vector<double> >  process_in(std::vector<double> & _input);
                std::vector<std::vector<double> >  process_out(std::vector<double> & vector_A, std::vector<double> & vector_B);
  
                
                double get_vector_threshold(std::vector<double > &vector);
                bool are_different(std::vector<double> & vector_A, std::vector<double> & vector_B);
              
                
		double get_time_limit();
                void set_time_limit(int _time_limit);
                bool get_store();
                
                void RAZ_List_of_input();
                bool Is_a_CS(std::vector<double> & input);
                bool Is_an_US(std::vector<double> & input);
};

#endif

