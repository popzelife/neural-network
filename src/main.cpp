/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 14:00:02 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/24 14:00:40 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int main( int argc, char* args[] )
{
    printf("--------------------------------------------\n");
    printf("NEURAL NETWORK: 2 Neurons x 2/1 connections\n");
    printf("--------------------------------------------\n\n");
    std::vector<std::vector<float> >* myTrainingInputs = new std::vector<std::vector<float> >;
    std::vector<std::vector<float> >* myTrainingOutputs = new std::vector<std::vector<float> >;

    std::vector<float> myInputsA = {0,0};
    std::vector<float> myInputsB = {0,1};
    std::vector<float> myInputsC = {1,0};
    std::vector<float> myInputsD = {1,1};
    std::vector<float> myOutputsA = {1};
    std::vector<float> myOutputsB = {0};


    printf("TRAINING DATA\n");
    printf("--------------------------------------------\n");
    myTrainingInputs->push_back(myInputsA);
    myTrainingOutputs->push_back(myOutputsA);
    printf("INPUTS= %f, %f; Expected output = %f\n", myInputsA[0], myInputsA[1], myOutputsA[0]);
    myTrainingInputs->push_back(myInputsB);
    myTrainingOutputs->push_back(myOutputsB);
    printf("INPUTS= %f, %f; Expected output = %f\n", myInputsB[0], myInputsB[1], myOutputsB[0]);
    myTrainingInputs->push_back(myInputsC);
    myTrainingOutputs->push_back(myOutputsB);
    printf("INPUTS= %f, %f; Expected output = %f\n", myInputsC[0], myInputsC[1], myOutputsB[0]);
    myTrainingInputs->push_back(myInputsD);
    myTrainingOutputs->push_back(myOutputsA);
    printf("INPUTS= %f, %f; Expected output = %f\n", myInputsD[0], myInputsD[1], myOutputsA[0]);

    LNeuralNetwork* NN = new LNeuralNetwork;
    NN->addLayer(2,2);
    NN->addLayer(2,1);


    printf("\n--------------------------------------------\n");
    printf("Before Training\n");
    std::vector<float> myInputDataA1 = {0,0};
    NN->processInputsToOutputs(myInputDataA1);
    std::vector<float> myOutputDataA1;
    myOutputDataA1=NN->getOutputs();
    printf("Feed Forward:  INPUT = 0,0; OUTPUT = %f\n", myOutputDataA1.at(0));

    std::vector<float> myInputDataB1={0,1};
    NN->processInputsToOutputs(myInputDataB1);
    std::vector<float> myOutputDataB1;
    myOutputDataB1=NN->getOutputs();
    printf("Feed Forward:  INPUT = 0,1; OUTPUT = %f\n", myOutputDataB1.at(0));

    std::vector<float> myInputDataC1={1,0};
    NN->processInputsToOutputs(myInputDataC1);
    std::vector<float> myOutputDataC1;
    myOutputDataC1=NN->getOutputs();
    printf("Feed Forward:  INPUT = 1,0; OUTPUT = %f\n", myOutputDataC1.at(0));

    std::vector<float> myInputDataD1={1,1};
    NN->processInputsToOutputs(myInputDataD1);
    std::vector<float> myOutputDataD1;
    myOutputDataD1=NN->getOutputs();
    printf("Feed Forward:  INPUT = 1,1; OUTPUT = %f\n", myOutputDataD1.at(0));


    printf("\n");
    printf("--------------------------------------------\n");
    printf("Begin Training #1 with ErrorTarget at 0.05\n\n");
    NN->autoTrainNetwork(*myTrainingInputs,*myTrainingOutputs,0.05,500000);
    printf("\n");
    printf("End Training\n");
    printf("\n");


    printf("--------------------------------------------\n");
    printf("Test the neural network\n");
    std::vector<float> myInputDataA2={0,0};
    NN->processInputsToOutputs(myInputDataA2);
    std::vector<float> myOutputDataA2;
    myOutputDataA2=NN->getOutputs();
    printf("Feed Forward:  INPUT = 0,0; OUTPUT = %f\n", myOutputDataA2.at(0));

    std::vector<float> myInputDataB2={0,1};
    NN->processInputsToOutputs(myInputDataB2);
    std::vector<float> myOutputDataB2;
    myOutputDataB2=NN->getOutputs();
    printf("Feed Forward:  INPUT = 0,1; OUTPUT = %f\n", myOutputDataB2.at(0));

    std::vector<float> myInputDataC2={1,0};
    NN->processInputsToOutputs(myInputDataC2);
    std::vector<float> myOutputDataC2;
    myOutputDataC2=NN->getOutputs();
    printf("Feed Forward:  INPUT = 1,0; OUTPUT = %f\n", myOutputDataC2.at(0));

    std::vector<float> myInputDataD2={1,1};
    NN->processInputsToOutputs(myInputDataD2);
    std::vector<float> myOutputDataD2;
    myOutputDataD2=NN->getOutputs();
    printf("Feed Forward:  INPUT = 1,1; OUTPUT = %f\n", myOutputDataD2.at(0));


    return 0;
}
