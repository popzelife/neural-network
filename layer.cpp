/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 19:25:20 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/24 19:26:01 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/* Default constructor for the Layer */

LLayer::LLayer( uint32_t numberConnections, uint64_t numberNeurons )
{
    //fprintf( stderr, "Getting a layer of neurons\r" );

    mInputsList             = {};
    mActualOutputsList      = {};
    mExpectedOutputsList    = {};
    mLayerError             = 0.0;
    mLearningRate           = 0.0;

    //Add all the neurons and mActualOutputs to the layer
    for( uint64_t i = 0; i < numberNeurons; i++ )
    {
        LNeuron* neuron = new LNeuron( numberConnections );
        addNeuron( neuron );
    }
}


/* Deallocate memory */

LLayer::~LLayer()
{
    //fprintf( stderr, "Deleting class LLayer\r" );
    freeNeuronsList();
}


/* Free layers list */

void    LLayer::freeNeuronsList()
{
    for( uint64_t i = 0; i < neuronsList.size(); i++ )
    {
        neuronsList.at(i)->freeConnectionsList();
        delete neuronsList.at(i);
    }
    neuronsList.clear();
    neuronsList.shrink_to_fit();
}


/* Add an input or output Neuron to this Layer */

void    LLayer::addNeuron( LNeuron* xNeuron )
{
    neuronsList.push_back( xNeuron );
}


/* Get the number of neurons in this layer */

uint64_t     LLayer::getNeuronCount() const
{
    return neuronsList.size();
}


/* Set the entire expectedOutputsList in one go */

void    LLayer::setExpectedOutputs( std::vector<float> expectedOutputsList )
{
    mExpectedOutputsList = expectedOutputsList;
}


/* Clear all values from the expectedOutputs list */

void    LLayer::clearExpectedOutputs()
{
    mExpectedOutputsList.clear();
    mExpectedOutputsList.shrink_to_fit();
}


/* Set the learning rate of the layer */

void    LLayer::setLearningRate( float learningRate )
{
    mLearningRate = learningRate;
}


/* Function to set the inputs of this layer */

void    LLayer::setInputs( std::vector<float> inputsList )
{
    mInputsList = inputsList;
}


/* Convert all the neuron input values into neuron output values in this layer,
   through a special activation function */

void    LLayer::processInputsToOutputs()
{
    //NeuronCount is used a couple of times in this function
    uint64_t neuronCount = getNeuronCount();

    //Make sure that there are neurons in this layer to process the inputs
    if( neuronCount > 0 )
    {
        //Make sure that number of inputs matches number of Neuron Connections
        if( mInputsList.size() != neuronsList.at(0)->getConnectionCount() )
        {
            fprintf( stderr, "Error in Layer at processInputsToOutputs: "
                     "The number of inputs do not match the number of Neuron "
                     "connections in this layer\n" );
            exit(-1);
        }
        else
        {
            //The number of inputs are fine : continue.
            //Calculate ActualOutputList of each neuron in this layer, based
            //on their layer InputsList(which were previously calculated).
            //Add the value to the layer's ActualOutputsList
            if( mActualOutputsList.capacity() < neuronCount )
            {
                mActualOutputsList.resize( neuronCount );
            }
            for( uint64_t i = 0; i < neuronCount; i++ )
            {
                //float temp = neuronsList[i]->computeNeuronOutput( mInputsList );
                //printf("Winston\n");
                mActualOutputsList.at(i) = neuronsList.at(i)->
                                            computeNeuronOutput( mInputsList );
            }
        }
    }
    else
    {
        fprintf( stderr, "Error in Layer at processInputsToOutputs: There are"
                 " no Neurons in this layer\n" );
        exit(-1);
    }
}


/* Get the error of this layer */

float   LLayer::getLayerError() const
{
    return mLayerError;
}


/* Set the error of this layer */

void    LLayer::setLayerError( float layerError )
{
    mLayerError = layerError;
}


/* Increase the layerError by a certain count */

void    LLayer::increaseLayerErrorBy( float layerError )
{
    mLayerError += layerError;
}


/* Calculate and set the deltaError of each neuron in the layer */

void    LLayer::setDeltaError( std::vector<float> expectedOutputsList )
{
    setExpectedOutputs( expectedOutputsList );
    uint64_t neuronCount = getNeuronCount();

    //Reset the layer error to 0 before cycling through each neuron
    setLayerError( 0.0 );
    for( uint64_t i = 0; i < neuronCount; i++)
    {
        neuronsList.at(i)->mDeltaError = mActualOutputsList.at(i) * ( 1 -
                    mActualOutputsList.at(i) ) * ( mExpectedOutputsList.at(i) -
                    mActualOutputsList.at(i) );

       //Increase the layer Error by the absolute difference between
       //the calculated value (mActualOutputsList) and the expected
       //value (mExpectedOutputstList)
       increaseLayerErrorBy( std::abs( mExpectedOutputsList.at(i) -
                                  mActualOutputsList.at(i) ) );
    }
}


/* Train the layer : which uses a training set to adjust the connection weights
   and biases of the neurons in this layer */

void    LLayer::trainLayer( float learningRate )
{
    setLearningRate( learningRate );
    uint64_t neuronCount = getNeuronCount();

    for( uint64_t i = 0; i < neuronCount; i++ )
    {
        //Update the bias for neuron[i]
        neuronsList[i]->mBias += ( mLearningRate * 1
                                   * neuronsList.at(i)->mDeltaError );

        //Update the weight of each connection for neuronsList[i]
        for( uint64_t j = 0; j < neuronsList.at(i)->getConnectionCount(); j++ )
        {
            neuronsList[i]->connectionsList.at(j)->mWeight += ( mLearningRate *
                        neuronsList.at(i)->connectionsList.at(j)->mConnEntry *
                        neuronsList.at(i)->mDeltaError );
        }
    }
}
