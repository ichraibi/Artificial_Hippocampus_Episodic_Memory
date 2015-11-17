# Artificial_Hippocampus_Episodic_Memory
Creation of an Artificial Hippocampus with an Episodic Memory


Program developed with:
- C++
- Netbeans 7.4
- Ubuntu 12.04

Context of the project :
This work was done during the Internship of the second year of Master in Cognitive Science with the Mnemosyne Project-Team of Inria.
It purpose is to compare two models for CA1, a cerebral area, which play a role into the episodic memory.

Purpose of the program:
  The implementation of an artificial hippocampus using an auto and hetero-associative Memories for CA3 and CA1.

  It's modules are :
	- Enthorhinal cortex 
	- Gyrus Dente 
	- CA3
	- CA1

The model can be launch with CA1 as Perceptrons or CA1 as associatives memories.
The purpose is to be able to compare the performances of the model with the two CA1.

the command in ordre to launch the program is :
    ./main -nbvector <nbVector> -hippotype <hippotype> -logactive <logactive>"
     with <hippotype> : 
    - PE for PERCEPTRON
    - AM for ASSOCIATIVE MEMORY
    with <logactive> : 
    - 1 for true : creation of a file for the logs in Desktop/log/" 
    - 0 for false: print in the terminal

Please see the file "lignecommande.sh" for examples.

In order to learn more abour the project, please read in the following order :
- IkramCK-Pre MemoireMaster2ScienceCo 2013-2014_French.pdf
- IkramCK- Mémoire_French.pdf
