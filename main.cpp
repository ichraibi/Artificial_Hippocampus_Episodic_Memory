extern "C" {
#include <math.h>
}
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <sstream> 
#include "Hippocampus_AM.hpp" 
#include "Hippocampus_Perceptron.hpp" 
#include <iostream>
#include <fstream>
#include "Math.hpp"
using namespace std;

//parameters to set -----------------------------------------
size_t CS_Size = 64;
size_t US_Size = 16;
double similarity_percent = 0.0;
unsigned int nb_CS_vectors = 10;
unsigned int nb_US_vectors = 10;

//parameters for CA1 as a perceptron-------------------------
double Hippo_per_learning_threshold = 1;
double perceptron_learning_threshold = 0.5;
double ca1_learning_rate = 0.001;
double time_constant = 1;

//declaration of variables------------------------------------
std::vector<std::vector<double> > random_vectors_for_learning;
std::vector<std::vector<double> > random_CSs;
std::vector<std::vector<double> > random_USs;
std::vector<std::vector<double> > random_disturbed_CSs;

//initialization-----------------------------------------------
double nb_unit_activ_per_CS = 5;//log(CS_Size) / log(2);
double nb_unit_activ_per_US = 2;//log(US_Size) / log(2);

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " -nbvector <nbVector> -hippotype <hippotype> -logactive <logactive>"<< std::endl;             
    std::cerr << "with <hippotype> : " <<std::endl;
    std::cerr << "- PE for PERCEPTRON"<< std::endl;   
    std::cerr << "- AM for ASSOCIATIVE MEMORY"<< std::endl; 
    std::cerr << "with <logactive> : " <<std::endl;
    std::cerr << "- 1 for true : creation of a file for the logs in Desktop/log/"<< std::endl;   
    std::cerr << "- 0 for false: print in the terminal"<< std::endl;  
}

int main(int argc, char *argv[]) {

   Math math_tools;
   struct tm Today;
   time_t maintenant;

   time(&maintenant);
   Today = *localtime(&maintenant);
    
   if (argc < 7) {
        show_usage(argv[0]);
        return 1;
   }
   
   int nb_vector = -1;
    string hippotype="";
    bool log_activ; 
     
    for (int i = 1; i < argc; i++) {
       string arg = argv[i];
     
       if(arg== "-nbvector")
       {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                nb_vector = atoi(argv[++i]); // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "-nbvector option requires one argument." << std::endl;
                return 1;
            }  
       }else if(arg=="-hippotype"){
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                hippotype = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "-hippotype option requires one argument." << std::endl;
                return 1;
            }
       }else if(arg=="-logactive"){
            if (i + 1 <= argc) { // Make sure we aren't at the end of argv!
                log_activ = atoi(argv[++i]); // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "-logactive option requires one argument." << std::endl;
                return 1;
            }
       }else{ // Uh-oh, there was no argument to the destination option.
             show_usage(argv[0]);
             return 1;
       }
    }

   cout << "nb_vector : "<<nb_vector <<endl;
   cout << "hippotype : "<<hippotype <<endl;
   cout << "logactive : "<<log_activ <<endl;
   
   if(nb_vector ==-1) 
   {
	show_usage(argv[0]);
 	return 1; 
   }
    nb_CS_vectors = nb_vector;
    nb_US_vectors = nb_vector;
     
    double nb_vecteur = nb_CS_vectors + nb_US_vectors;
       
    std::streambuf *coutbuf;
    ostringstream os;
    os << "/home/ichraibi/Desktop/log/test_" << nb_vecteur << "_" << Today.tm_year << "y"<< Today.tm_mon << "m"<< Today.tm_mday << "d" << Today.tm_hour << "h" << Today.tm_min << "min" << Today.tm_sec << "sec.txt"; // ou n'importe quoi d'autre
    std::ofstream out(os.str().c_str());  
    
    if (log_activ==true) 
    { 
        coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    }
    else
    {
        remove(os.str().c_str());
    }

    try {
        // initialization pour hippocampe using CA1 as an heteroassociative memory
        Hippocampus_AM Hippo_AM(CS_Size, US_Size);
        // initialization pour hippocampe using CA1 as a perceptron
        Hippocampus_Perceptron Hippo_perceptron(CS_Size, US_Size, ca1_learning_rate, Hippo_per_learning_threshold, perceptron_learning_threshold);
        
        std::cout<<"taille CS :"<< CS_Size << std::endl;
        std::cout<<"taille US : "<< US_Size << std::endl;
        cout << "nb_unit_activ_per_CS: " << nb_unit_activ_per_CS << std::endl;
        cout << "nb_unit_activ_per_US: " << nb_unit_activ_per_US << std::endl;
      
        random_vectors_for_learning.clear();
         cout << "nb_CS_vectors : " << nb_CS_vectors<< "; nb_US_vectors : " << nb_US_vectors<< "; nb_total_vectors: " << nb_CS_vectors+nb_US_vectors << std::endl;
        random_vectors_for_learning = math_tools.generation_of_random_vectors(random_CSs, random_USs, CS_Size,  US_Size,  nb_CS_vectors+nb_US_vectors ,  nb_unit_activ_per_CS,  nb_unit_activ_per_US);
        
        if (hippotype=="PE")
        {
            std::cout<<"EVALUATION OF THE MODEL WITH CA1 as PERCEPTRON :"<< std::endl;
            Hippo_perceptron.launch_process(nb_CS_vectors, nb_US_vectors, CS_Size,nb_unit_activ_per_CS, random_vectors_for_learning,random_CSs, random_USs, random_disturbed_CSs);
        }
        else
        {
            std::cout<<"EVALUATION OF THE MODEL WITH CA1 as ASSOCIATIVE MEMORY :"<< std::endl;
            Hippo_AM.launch_process(nb_CS_vectors, nb_US_vectors, CS_Size,nb_unit_activ_per_CS, random_vectors_for_learning,random_CSs, random_USs, random_disturbed_CSs);
        }
       
    } catch (std::string error) {
        std::cout << "ERROR: " << error << std::endl;
        if (log_activ==true) {
            std::cout.rdbuf(coutbuf);
        } //reset to standard output again
        return EXIT_FAILURE;
    }

    if (log_activ==true) {
        std::cout.rdbuf(coutbuf);
    } //reset to standard output again
    return EXIT_SUCCESS;

}



