/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 19:25:43 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/24 19:25:56 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LAYER_H
#define _LAYER_H

/* Layer wrapper class */

class LLayer
{
    friend class LNeuralNetwork;

    public:
        //Initialize variables
        LLayer( uint32_t numberConnections, uint64_t numberNeurons );
        //Deallocate memory
        ~LLayer();


        //Add an input or output neuron to this layer
        void addNeuron( LNeuron* xNeuron );
        //Increase the layerError by a certain count */
        void increaseLayerErrorBy( float layerError );
        //Convert all neuron input values into neuron output values in the layer
        void processInputsToOutputs();
        //Train the layer to adjust connection weights and biases of the neurons
        void trainLayer( float learningRate );


        //Set the entire expectedOutputsList in one go
        void setExpectedOutputs( std::vector<float> expectedOutputsList );
        //Set the learning rate of the layer
        void setLearningRate( float learningRate );
        //Set the inputs of this layer
        void setInputs( std::vector<float> inputsList );
        //Set the error of this layer
        void setLayerError( float layerError );
        //Calculate and set the deltaError of each neuron in the layer
        void setDeltaError( std::vector<float> expectedOutputstList );


        //Get the number of neurons in this layer
        uint64_t getNeuronCount() const;
        //Get the error of this layer
        float getLayerError() const;


        //Clear all values from the expectedOutputs list
        void clearExpectedOutputs();
        //Free layers list
        void freeNeuronsList();


    private:
        //Dynamic array to hold neurons
        std::vector<LNeuron*>   neuronsList;

        //Layer variables
        std::vector<float>      mInputsList; //The layer inputs
        std::vector<float>      mActualOutputsList;
        std::vector<float>      mExpectedOutputsList;

        float                   mLayerError;
        float                   mLearningRate;
};

#endif // _LAYER_H
