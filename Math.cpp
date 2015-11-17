#include "Math.hpp"
extern "C"{
  #include <math.h>
}
#include <cmath>
using namespace std;

Math::Math(){
    
}

Math::~Math(){
    
}

double Math::heaviside(double x) {
    return x < 0 ? 0 : 1;
}

std::vector<std::vector<double> > Math::get_transposed_matrix(std::vector<std::vector<double>   > original_matrix){
    
    std::vector<std::vector<double>     > transposed_matrix;
    
    transposed_matrix = std::vector<std::vector<double> >(original_matrix.size(), std::vector<double>(original_matrix.size(), 0.0));
            //new std::vector<std::vector<double>>(original_matrix.size(), std::vector<double>(original_matrix.size(), 0.0));

    unsigned int i,j;
    for (i=0; i< original_matrix.size(); i++)
    {
        for (j=0; j< original_matrix.size(); j++)
        {
            transposed_matrix[j][i] = original_matrix[i][j];
        }
    }
   
    return transposed_matrix;
}

std::vector<std::vector<double> > Math::sum_of_matrix(std::vector<std::vector<double>   >& matrix_1, std::vector<std::vector<double> >& matrix_2) {
   
    //we can just do the sum of similar matrix ( same number of line and column)
    size_t i, j,nbre_line, nbre_col;
    std::vector<std::vector<double> > sum_matrix;
    nbre_line = matrix_1.size();
    
    sum_matrix.resize(nbre_line);
    
    for (i=0 ; i<nbre_line; i++)
    {
        
        nbre_col = matrix_1[i].size();
        
        sum_matrix[i].resize(nbre_col);
        for (j=0 ; j<nbre_col; j++)
        {
            sum_matrix[i][j] = matrix_1[i][j]+matrix_2[i][j];
          
        }
    }
    
    return sum_matrix;
 
    
}


void Math::display_matrix(std::vector<std::vector<double> >& matrix)
{
    
    size_t i, j;
    for (i=0; i< matrix.size(); i++)
    {
        std::cout<< i<<" :";
        for (j=0; j< matrix[i].size(); j++)
        {
            std::cout<<" ["<<matrix[i][j]<<"]";
        }
        std::cout<<" "<<std::endl;
    }
}

void Math::display_vector(std::vector<double>& vector)
{
    size_t i;
    std::cout<< " ";
    for (i=0; i< vector.size(); i++)
    {
            std::cout<<" "<<vector[i]<<"";
    }
    std::cout<<" "<<std::endl;
}

double Math::compute_HD(std::vector<double> &original_vector, std::vector<double>& output_vector){
    
    size_t i; 
    double haming_distance =0.0;
    double diff_value=0.0;
    for (i=0; i< original_vector.size(); i++){
        diff_value = original_vector[i] - output_vector[i];
        if(fabs(diff_value)>0) 
            haming_distance++;
    }
    return haming_distance;
}


float Math::compute_average_HD(std::vector<double>& table_HD){
    
    size_t i; 
    float average=0.000;

    for (i=0; i< table_HD.size(); i++){
        average += table_HD[i];
    }

    average = average/table_HD.size(); 
    return average;
 
}

double Math::get_vector_active_unit_nbre(std::vector<double>& a_vector) {
    double nbre_of_activ_unit=0.0 ;
    for(size_t i =0 ; i< a_vector.size() ; i++)
    {
        if (a_vector[i]>0)
            nbre_of_activ_unit++;
    }
  
    return nbre_of_activ_unit;
}

 double Math::get_Matrix_active_unit_nbre(std::vector<std::vector<double> >& matrix)
 {
     double nbre_of_activ_unit=0.0 ;
    for(size_t i =0 ; i< matrix.size() ; i++)
    {
        nbre_of_activ_unit+= get_vector_active_unit_nbre(matrix[i]) ;
    }
  
    return nbre_of_activ_unit;
 }

double Math::get_matrix_rate_saturation(std::vector<std::vector<double> >& matrix)
{
    double nb_unit_activ =get_Matrix_active_unit_nbre(matrix);
 
    double rate_saturation = nb_unit_activ/(matrix.size()*matrix[1].size());
    std::cout<< "Matrix nb_unit_activ : "<<nb_unit_activ << " ; Matrix capacity storage  : "<<matrix.size()*matrix[1].size() << " ; rate_saturation : "<<rate_saturation <<std::endl;
    return rate_saturation;
}


void Math::get_AM_loading_density(double nb_unit_active, double vector_size, double nb_learned_vectors)
{
    double loading_density=0.0;
    
     loading_density = 1 - pow(1- ((nb_unit_active*nb_unit_active)/(vector_size*vector_size)),nb_learned_vectors);
    //p1= 1 - (1-k^2/n^2)^t 
    //where n=size of vectors, k = number of activ units, t= number of learned vectors
     std::cout<< "Auto associative Loading density : "<<loading_density <<std::endl;
}

void Math::get_HM_loading_density(double input_vector_nb_unit_active, double input_vector_size, double output_vector_nb_unit_active, double output_vector_size, double nb_learned_vectors)
{
    double loading_density=0.0;
    loading_density = 1 - pow(1- ((input_vector_nb_unit_active* output_vector_nb_unit_active)/(input_vector_size, output_vector_size)),nb_learned_vectors);
    //p1= 1 - (1-k^2/n^2)^t 
     //where n=size of vectors, k = number of activ units, t= number of learned vectors
     std::cout<< "Hetero associative Loading density : "<<loading_density <<std::endl;
}

double Math::get_AM_estimated_nb_learned_pattern(double input_vector_size)
{
    double estimated_nb_learned_pattern=0.0;
    estimated_nb_learned_pattern= pow(input_vector_size/(log(input_vector_size)/log(2)), 2);
    return estimated_nb_learned_pattern;
}

double Math::get_HM_estimated_nb_learned_pattern(double input_vector_size, double output_vector_size)
{
    double estimated_nb_learned_pattern=0.0;
    
    estimated_nb_learned_pattern= pow(((input_vector_size*output_vector_size)/((log(input_vector_size)/log(2))*(log(output_vector_size)/log(2)))), 2);
    return estimated_nb_learned_pattern;
}

void Math::display_matrix_properties(std::vector<std::vector<double> >& matrix)
{
    
    
}

bool Math::control_vectors(std::vector<double>& original, std::vector<double>& output)
{

    bool vector_ok = false;
   
    double a_hamming_distance = compute_HD(original,output);
    if (a_hamming_distance == 0) {
        vector_ok = true;
    }
 
    return vector_ok;

}

std::vector<double> Math::compute_haming_distance(std::vector<double>& original_vector, std::vector<double>& output_vector, int number, std::vector<double>& table_HD) {

    int i;

    double diff_value = 0.0;
    for (i = 0; i < original_vector.size(); i++) {
        diff_value = original_vector[i] - output_vector[i];

        if (fabs(diff_value) > 0) {
            table_HD[number]++;

        }
    }
    return table_HD;
}

void Math::generate_random_vector(std::vector<double> &a_vector, int vector_size, int nb_unit_active) {
    std::vector<int> indexs;
    for (int i = 0; i < vector_size; i++) {
        indexs.push_back(i);
    }
    int activ_unit = 0;
    while (activ_unit < nb_unit_active) {
       // srand(time(NULL)); //reinitialisation of the seed of the random
        unsigned int r0 = (rand() % indexs.size());
        int index = indexs[r0];

        a_vector[index] = 1.0;
        activ_unit++;

        indexs.erase(indexs.begin() + r0);
    }
    
}

std::vector<std::vector<double> > Math::generation_of_random_vectors(std::vector<std::vector<double> >& random_CSs,std::vector<std::vector<double> >& random_USs, double CS_Size, double US_Size, unsigned int nb_total_vectors, double nb_unit_activ_per_CS, double nb_unit_activ_per_US) {
    cout << "Generation RANDOM VECTORS " << std::endl;
    std::vector<std::vector<double> > liste_vectors;
    std::vector<double> a_vector;
    unsigned int nb_unit_active = 0;

    liste_vectors.clear();
    random_CSs.clear();
    random_USs.clear();

   // unsigned int nb_total_vectors = nb_CS_vectors + nb_US_vectors;
   
   for (int i = 0; i < nb_total_vectors; i++) {

        if (i % 2 == 0) {
            //creation of the CS 
            a_vector.clear();
            a_vector.resize(CS_Size);
            nb_unit_active = 0;
            generate_random_vector(a_vector, CS_Size, nb_unit_activ_per_CS);

            random_CSs.push_back(a_vector);

        } else {
            //creation of the US 
            a_vector.clear();
            a_vector.resize(US_Size);
            generate_random_vector(a_vector, US_Size, nb_unit_activ_per_US);
          

            random_USs.push_back(a_vector);
        }
        liste_vectors.push_back(a_vector);

    }
   
    return liste_vectors;

}

std::vector<std::vector<double> > Math::generate_disturbed_random_vectors(std::vector<std::vector<double> > & random_vectors, int vector_size, int nb_unit_active, double percent_of_distortion)
{
    std::vector<std::vector<double> > random_modified_CSs;
    random_modified_CSs.clear();
   
  
    double nbre_of_disturb_unit = round(percent_of_distortion*nb_unit_active);
    std::cout << "percent of distorsion: " << percent_of_distortion<< " - nbre_of_disturb_unit : " << nbre_of_disturb_unit << std::endl;
    unsigned int num_unit= (rand() % vector_size);
 
    for (int i=0; i< random_vectors.size(); i++)
    {
        std::vector<double> a_vector = random_vectors[i];
        double nb_change = 0.0;
     
        while (nb_change < nbre_of_disturb_unit) {
            num_unit = (rand() % vector_size);
            if (num_unit < vector_size) {
                if (a_vector[num_unit] != 0) {
                    a_vector[num_unit] = 0;
                    nb_change++;
                }
            }
        }
        random_modified_CSs.push_back(a_vector);
    }
 
    return random_modified_CSs;
}