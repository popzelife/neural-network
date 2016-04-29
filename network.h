/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 15:32:04 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/25 15:32:38 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _NEURAL_NETWORK_H
#define _NEURAL_NETWORK_H

#define TRAINING_SHOW_ERROR_RATIO       1000

/* Neural Network wrapper class */

class LNeuralNetwork
{
    public:
        //Initialize variables
        LNeuralNetwork();
        //Deallocate memory
        ~LNeuralNetwork();


        //Add a Layer to the neural network
        void addLayer( uint32_t numberConnections, uint64_t numberNeurons );
        //Process neural network's input values and convert them to an output
        void processInputsToOutputs( std::vector<float> arrayOfInputs );
        //Train the entire network using an array
        void trainNetwork( std::vector<float> inputslist, std::vector<float>
                           expectedOutputsList );
        //Train the entire network, using an array of input and expected data
        void trainingCycle( std::vector<std::vector<float>> trainingInputList,
                        std::vector<std::vector<float>> trainingExpectedList,
                        bool trainRandomly );
        //Train the network until the Error is below a specific threshold
        void autoTrainNetwork(std::vector<std::vector<float>> trainingInputList,
                        std::vector<std::vector<float>> trainingExpectedList,
                        float trainingErrorTarget, uint64_t cycleLimit );


        //Set the learningRate of the neural network
        void setLearningRate( float learningRate );
        //Set the inputs of the neural network
        void setInputs( std::vector<float> arrayOfInputs );
        //Set the inputs of a specified layer
        void setLayers( std::vector<float> arrayOfInputs, uint32_t layerIndex );
        //Set the outputs of the neural network
        void setOutputs( std::vector<float> arrayOfInputs );


        //Return the number of layers in the neural network
        uint32_t getLayerCount() const;
        //Return the outputs of the neural network
        std::vector<float> getOutputs() const;


        //Free layers list
        void freeLayersList();


    private:
        //Train the network until the Error is below a specific threshold
        void aTN( std::vector<std::vector<float>> trainingInputList,
                  std::vector<std::vector<float>> trainingExpectedList,
                  float trainingErrorTarget, uint64_t cycleLimit );

        //Random class
        LRandom     random;

        //Dynamic array to hold layers
        std::vector<LLayer*>    layersList;

        //Neural Network variables
        std::vector<float>      mArrayOfInputs;
        std::vector<float>      mArrayOfOutputs;

        float                   mLearningRate;
        float                   mNetworkError;
        float                   mTrainingError;

        uint8_t                 mRetrainChances;
        uint64_t                mTrainingCounter;
};

#endif // _NEURAL_NETWORK_H
