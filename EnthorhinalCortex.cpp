#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <sys/timeb.h>

//#include "MemoryDyn.hpp"
#include "EnthorhinalCortex.hpp"
#include "Math.hpp"


EnthorhinalCortex::EnthorhinalCortex(unsigned int size_CS, unsigned int size_US) {
    this->List_of_input = std::vector<std::vector<double> >(0, std::vector<double>(0, 0.0));
    this->size_CS = size_CS;
    this->size_US = size_US;
    this->store = false;
}

EnthorhinalCortex::~EnthorhinalCortex() {
    
}
  
//incomplete
std::vector<std::vector<double> > EnthorhinalCortex::process_in(std::vector<double> & _input) {
    
//  std::cout<<"EnthorhinalCortex : PROCESS ----------------------------------------" <<std::endl;
    
    std::vector<std::vector<double> > list_of_associated_input = std::vector<std::vector<double> >(0, std::vector<double>(0, 0.0)); 
       
    //std::cout<<"Au debut du process List_of_input.size() : "<< this->List_of_input.size() <<std::endl;
    
    std::vector<double> void_US;
    void_US.resize(this->size_US,0.0);

    
    switch (this->List_of_input.size())
        {
           case 0:
                  this->store = false;
                  this->List_of_input.push_back(_input);
                  list_of_associated_input.resize(this->List_of_input.size());
                  list_of_associated_input = this->List_of_input;
                  list_of_associated_input.push_back(void_US);
                  break;
           
           case 1:
               
               if(Is_an_US(_input)==true){
                //  std::cout<<"CS et US "<<std::endl;
                  this->store = true;
                  this->List_of_input.push_back(_input);  
                  list_of_associated_input.resize(this->List_of_input.size());
                  list_of_associated_input = this->List_of_input;
  
                  RAZ_List_of_input();
               }else{    
                  RAZ_List_of_input();
                  this->List_of_input.push_back(_input);
                  list_of_associated_input.resize(this->List_of_input.size());
                  list_of_associated_input = this->List_of_input;
                  list_of_associated_input.push_back(void_US);
               } 
                                  
               break;
           
            default: 
               printf("FAIL : nbre of input incorrect : %d \n",this->List_of_input.size());
               RAZ_List_of_input();
    
               break;
        }
 
    return list_of_associated_input;
}

std::vector<std::vector<double> >  EnthorhinalCortex::process_out(std::vector<double> & vector_CS, std::vector<double> & vector_US){
    std::vector<std::vector<double> > vectors;
    
 //   std::cout<<"Rget_vector_threshold(vector_CS): "<<get_vector_threshold(vector_CS)<<std::endl;
    
    if (get_vector_threshold(vector_CS)!= 0)
    {
        //it means that the initial vector was already stored 
        //or that it look like a pattern aleardy stored
//        std::cout<<"RAZ _ LIST OF INPUT "<<std::endl;
//        std::cout<<" "<<std::endl;
        RAZ_List_of_input();
    }

    vectors.clear();
    vectors.push_back(vector_CS);//the original CS
    vectors.push_back(vector_US);//the prediction
    
    return vectors;
}

double EnthorhinalCortex::get_vector_threshold(std::vector<double > &vector){
    double threshold = 0.0;
         
    for (size_t i = 0; i < vector.size(); i++)
    {
            threshold += vector[i];
    }
    
    return threshold;
}


bool EnthorhinalCortex::get_store(){
    return this->store;
}

void EnthorhinalCortex::RAZ_List_of_input(){
    this->List_of_input.clear();
}

 bool EnthorhinalCortex::Is_a_CS(std::vector<double> & input){
     if (this->size_CS == input.size())
         return true;
     else
         return false;
 }


 
 bool EnthorhinalCortex::Is_an_US(std::vector<double> & input){
     if (this->size_US == input.size())
         return true;
     else
         return false;
 }

 
 bool EnthorhinalCortex::are_different(std::vector<double> & vector_A, std::vector<double> & vector_B){
     
     bool are_different = false;
     
     if (vector_A.size() != vector_B.size())
     {
         are_different= true;
     }
     else
     {
        for(size_t i=0; i< vector_A.size();i++)
        {
            if(vector_A[i] != vector_B[i])
            {    
                are_different= true;
                break;
            }
        }
     }
     
     return are_different;
 }
