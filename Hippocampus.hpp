#ifndef HIPPO_HPP_
#define HIPPO_HPP_

#include <vector>
#include "EnthorhinalCortex.hpp"
#include "DG.hpp"
#include "CA1.hpp"
#include "CA1_Perceptron.hpp"
#include "CA3.hpp"
#include "Math.hpp"

class Hippocampus {
	protected:
		std::vector<double> hippocampus_input;
		std::vector<std::vector<double> > hippocampus_output;
		EnthorhinalCortex *enthorhinal_cortex;
                DG *dg;
                CA3 *ca3;
		
                double diff_DG_CA3_CS;
                double diff_DG_CA3_US;
                std::vector<std::vector<double> > DG_output;
                std::vector<std::vector<double> > CA3_outpout;
                
                //parameters for evaluation of the models
                
                std::vector<double> table_CS_HD; //table of hamilton distances  for CS
                std::vector<double> table_US_HD; //table of hamilton distances  for US
                
                unsigned int nb_errors_remind_CS;
                unsigned int nb_errors_prediction;
                unsigned int nb_success_remind_CS;
                unsigned int nb_success_prediction;
                unsigned int nb_erreur_prediction_2; 
                unsigned int nb_erreur_prediction_CS2; 

                Math math_tools;

	public:
		Hippocampus(unsigned int nb_neurons_input, unsigned int nb_neurons_output);
                ~Hippocampus();
                
		virtual void process(const std::vector<double> & input)=0;
                std::vector<std::vector<double> > get_hippocampus_output();
		void display_CA3_Matrix_properties(double nb_vectors);
          
                std::vector<std::vector<double> > get_CA3_output();
                std::vector<std::vector<double> > get_DG_output();
                bool get_EC_store();
                double get_nb_diff_DG_CA3_CS();
                double get_nb_diff_DG_CA3_US();
                
                void raz_nb_diff_DG_CA3_CS();
                void raz_nb_diff_DG_CA3_US();
                
                void launch_process(double nb_CS_vectors, 
                                double nb_US_vectors,
                                double CS_Size,
                                double nb_unit_activ_per_CS,
                                std::vector<std::vector<double> >& random_vectors_for_learning,
                                std::vector<std::vector<double> >& random_CSs,
                                std::vector<std::vector<double> >& random_USs,
                                std::vector<std::vector<double> >& random_disturbed_CSs);
                void display_nb_error_nb_success();
                void control_hippocampus_output(std::vector<double>& original_CS, int number,std::vector<double>& output_CS, std::vector<double>& original_US, std::vector<double>& output_US,std::vector<double> &table_CS_HD, std::vector<double> &table_US_HD);
};

#endif
