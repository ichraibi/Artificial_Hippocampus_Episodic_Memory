#include "Hippocampus.hpp"
//#include "MemoryDyn.cpp"
#include "Math.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
using namespace std;

Hippocampus::Hippocampus(unsigned int nb_neurons_input, unsigned int nb_neurons_output) 
{ 
        this->hippocampus_input.resize(nb_neurons_input);
        this->enthorhinal_cortex = new EnthorhinalCortex(nb_neurons_input, nb_neurons_output);
	this->dg = new DG();
        
        double size_CA3_input = nb_neurons_input*(nb_neurons_input-1)/2;
        double size_CA3_output = nb_neurons_output*(nb_neurons_output-1)/2;
        
        this->ca3 = new CA3(size_CA3_input, size_CA3_output);
        this->DG_output.clear();
        this->CA3_outpout.clear() ;
        this->diff_DG_CA3_CS=0.0;
        this->diff_DG_CA3_US=0.0;     
        this->table_CS_HD.clear(); //table of hamilton distances  for CS
        this->table_US_HD.clear(); //table of hamilton distances  for US
        
        this->nb_errors_remind_CS = 0;
        this->nb_errors_prediction = 0;
        this->nb_success_remind_CS = 0;
        this->nb_success_prediction = 0;
        this->nb_erreur_prediction_2 = 0; //table of hamilton distances  for US
        this->nb_erreur_prediction_CS2 = 0; //table of hamilton distances  for US
 
}

Hippocampus::~Hippocampus() 
{    
    delete this->ca3;
    delete this->dg;
    delete this->enthorhinal_cortex;
}



vector<vector<double> > Hippocampus::get_hippocampus_output()
{   
    return this->hippocampus_output  ;  
}

void Hippocampus::display_CA3_Matrix_properties(double nb_vectors)
{

    cout<<" CS_matrix"<<endl;
    vector<vector<double> > CS_matrix = this->ca3->get_CS_matrix();
    double CS_matrix_estimated_learned_pattern = math_tools.get_AM_estimated_nb_learned_pattern(CS_matrix.size());
    cout<<" CS_matrix_estimated_learned_pattern "<< CS_matrix_estimated_learned_pattern<<endl;
    this->math_tools.get_AM_loading_density(15,CS_matrix.size(),nb_vectors);
    
    math_tools.get_matrix_rate_saturation(CS_matrix);
    
    cout<<" "<<endl;
    cout<<" CS_US_matrix"<<endl;
    vector<vector<double> > CS_US_matrix = this->ca3->get_weight_matrix();
    //double CS_US_matrix_estimated_learned_pattern = math_tools.get_HM_estimated_nb_learned_pattern(CS_US_matrix.size(), CS_US_matrix[1].size());
   // cout<<" CS_US_matrix_estimated_learned_pattern "<< CS_US_matrix_estimated_learned_pattern<<endl; -- FALSE
    math_tools.get_HM_loading_density(15,CS_US_matrix.size(),6, CS_US_matrix[1].size(), nb_vectors);
    math_tools.get_matrix_rate_saturation(CS_US_matrix);
    cout<<" "<<endl;
}


vector<vector<double> > Hippocampus::get_CA3_output()
{
    return this->CA3_outpout  ;  
}

vector<vector<double> > Hippocampus::get_DG_output()
{
    return DG_output;
}

bool Hippocampus::get_EC_store()
{
    return this->enthorhinal_cortex->get_store();
}
double Hippocampus::get_nb_diff_DG_CA3_CS()
{
    return diff_DG_CA3_CS; 
}
double Hippocampus::get_nb_diff_DG_CA3_US()
{
    return diff_DG_CA3_US; 
}

void Hippocampus::raz_nb_diff_DG_CA3_CS()
{
    diff_DG_CA3_CS=0;
}

void Hippocampus::raz_nb_diff_DG_CA3_US()
{
     diff_DG_CA3_US=0;
}


void Hippocampus::launch_process(double nb_CS_vectors, 
                        double nb_US_vectors,
                        double CS_Size,
                        double nb_unit_activ_per_CS,
                        vector<vector<double> >& random_vectors_for_learning,
                        vector<vector<double> >& random_CSs,
                        vector<vector<double> >& random_USs,
                        vector<std::vector<double> >& random_disturbed_CSs) {
   
    table_CS_HD.clear();
    table_CS_HD.resize(nb_CS_vectors);
    table_US_HD.clear();
    table_US_HD.resize(nb_US_vectors);
    
    cout << " LEARNING------------------------------------------------------------------------------------------------------ " << endl;
    for (int i = 0; i < random_vectors_for_learning.size(); i++) 
    {
       // math_tools.display_vector(random_vectors_for_learning[i]);
        this->process(random_vectors_for_learning[i]);
    }
    
    cout << " " << endl;
    cout << "Evaluation performance CA3 : " <<endl;
    cout << "nb_diff_DG_CA3_CS : " << get_nb_diff_DG_CA3_CS() << endl;
    cout << "nb_diff_DG_CA3_US : " << get_nb_diff_DG_CA3_US() << endl;
    
    cout << " " << endl;
    cout << " Model CA3 properties------------------------------------------------------------------------ " << endl;
    display_CA3_Matrix_properties(nb_CS_vectors);
    
    vector<vector<double> > hippo_output;
    cout << " " << endl;
    cout << " Test : recall with intact CS ------------------------------------------------------------- " << endl;
   
    for (int i = 0; i < random_CSs.size(); i++) 
    {
        this->process(random_CSs[i]); //a recall with the same vectors
        hippo_output = get_hippocampus_output();
        control_hippocampus_output(random_CSs[i], i, hippo_output[0], random_USs[i], hippo_output[1],table_CS_HD, table_US_HD);
    }
    display_nb_error_nb_success();

    nb_errors_remind_CS = 0;
    nb_errors_prediction = 0;
    nb_success_remind_CS = 0;
    nb_success_prediction = 0;
    
    table_CS_HD.clear();
    table_CS_HD.resize(nb_CS_vectors);
    table_US_HD.clear();
    table_US_HD.resize(nb_US_vectors);
    nb_erreur_prediction_2 = 0;
    nb_erreur_prediction_CS2 = 0;
    
    cout << " " << endl;
    cout << " Test : recall with disturbed CS ----------------------------------------------------------------------- " << endl;
    double percent_of_distortion=0.2;
    random_disturbed_CSs = math_tools.generate_disturbed_random_vectors(random_CSs,CS_Size, nb_unit_activ_per_CS, percent_of_distortion);
 
    for (int i = 0; i < random_disturbed_CSs.size(); i++) 
    {
        process(random_disturbed_CSs[i]);
        hippo_output = get_hippocampus_output();
        control_hippocampus_output(random_CSs[i], i, hippo_output[0], random_USs[i], hippo_output[1],table_CS_HD, table_US_HD);
    }
    display_nb_error_nb_success();
    
    nb_errors_remind_CS = 0;
    nb_errors_prediction = 0;
    nb_success_remind_CS = 0;
    nb_success_prediction = 0;
    
    table_CS_HD.clear();
    table_CS_HD.resize(nb_CS_vectors);
    table_US_HD.clear();
    table_US_HD.resize(nb_US_vectors);
    nb_erreur_prediction_2 = 0;
    nb_erreur_prediction_CS2 = 0;
    cout << " " << endl;
    cout << " Test : recall with disturbed CS  ----------------------------------------------------------------------- " << endl;
    percent_of_distortion=0.4;
    random_disturbed_CSs = math_tools.generate_disturbed_random_vectors(random_CSs,CS_Size, nb_unit_activ_per_CS, percent_of_distortion);
    for (int i = 0; i < random_disturbed_CSs.size(); i++) 
    {
        process(random_disturbed_CSs[i]);    
        hippo_output = get_hippocampus_output();
        control_hippocampus_output(random_CSs[i], i, hippo_output[0], random_USs[i], hippo_output[1],table_CS_HD, table_US_HD);
    }
    display_nb_error_nb_success();
}

void Hippocampus::control_hippocampus_output(vector<double>& original_CS, int number,vector<double>& output_CS, vector<double>& original_US, vector<double>& output_US,vector<double> &table_CS_HD, vector<double> &table_US_HD) {
    
    double threshold_US = 0.0;
    double threshold_CS = 0.0;
    bool CS_OK = false;
    bool CS_OK_2 = false;
    bool US_OK = false;
    bool US_OK_2 = false;
    Math math_tools;
    table_CS_HD = math_tools.compute_haming_distance(original_CS, output_CS, number, table_CS_HD);
    if (table_CS_HD[number] == 0) 
    {
        CS_OK = true;
    }
  
    (CS_OK == true) ? nb_success_remind_CS++ : nb_errors_remind_CS++;

    //verification of the prediction
    table_US_HD = math_tools.compute_haming_distance(original_US, output_US, number, table_US_HD);
   
    if (table_US_HD[number] == 0) 
    {
        US_OK = true;
    }
    (US_OK == true) ? nb_success_prediction++ : nb_errors_prediction++;
 

    //vérification CS
    for (int i = 0; i < output_CS.size(); i++) 
    {
        threshold_CS += output_CS[i];
    }

    if (threshold_CS > 0 && original_CS == output_CS) 
    {
        CS_OK_2 = true;
    } else {
        nb_erreur_prediction_CS2++;
    }

  /*  std::cout << "original_CS : ";
    for (int i = 0; i < original_CS.size(); i++) 
    {
        std::cout << " " << original_CS[i];
    }
    std::cout << " " << std::endl;

    std::cout << "output_CS : ";
    for (int i = 0; i < output_CS.size(); i++) 
    {
        std::cout << " " << output_CS[i];
    }
    std::cout << " " << std::endl;
    std::cout << "CS_OK HD : " << CS_OK << "  - CS_OK code if : " << CS_OK_2 << std::endl;
*/

    for (int i = 0; i < output_US.size(); i++) {
        threshold_US += output_US[i];
    }

    if (threshold_US > 0 && original_US == output_US) 
    {
        US_OK_2 = true;
    } 
    else 
    {
        nb_erreur_prediction_2++;
    }

 /*   std::cout << "Original_US : ";
    for (int i = 0; i < original_US.size(); i++) 
    {
        std::cout << " " << original_US[i];
    }
    std::cout << " " << std::endl;

    std::cout << "output_US : ";
    for (int i = 0; i < output_US.size(); i++) 
    {
        std::cout << " " << output_US[i];
    }
    std::cout << " " << std::endl;

    std::cout << "US_OK HD : " << US_OK << "  - US_OK code if : " << US_OK_2 << std::endl;
  * */
  
}

void Hippocampus::display_nb_error_nb_success() {
    cout << " " << endl;
    cout << "nb_success_remind_CS: " << nb_success_remind_CS << endl;
    cout << "nb_errors_remind_CS: " << nb_errors_remind_CS << endl;
    cout << "nb_erreur_prediction_CS2: " << nb_erreur_prediction_CS2 << endl;
    cout << " " << endl;
    cout << "nb_success_predicion: " << nb_success_prediction << endl;
    cout << "nb_errors_prediction: " << nb_errors_prediction << endl;
    cout << "erreur prédiction 2: " << nb_erreur_prediction_2 << endl;
    cout << " " << endl;
    cout << "Average distance hamilton CS: " << math_tools.compute_average_HD(table_CS_HD) << endl;
    cout << "Average distance hamilton US: " << math_tools.compute_average_HD(table_US_HD) << endl;
}
