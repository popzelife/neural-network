/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 15:31:50 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/25 15:32:44 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/* Default constructor for the Layer */

LNeuralNetwork::LNeuralNetwork()
{
    //fprintf( stderr, "Setting up the neural network\r" );

    srand( time( NULL ) );
    LRandom     random;

    //Default learning rate of a neural network is set to 0.1,
    //which can changed by the setLearningRate(lR) function
    mArrayOfInputs      = {};
    mArrayOfOutputs     = {};
    mLearningRate       = 0.1;
    mRetrainChances     = 0;
    mNetworkError       = 0.0;
    mTrainingError      = 0.0;
    mTrainingCounter    = 0;
}


/* Deallocate memory */

LNeuralNetwork::~LNeuralNetwork()
{
    //fprintf( stderr, "Deleting class LNeuralNetwork\r" );
    freeLayersList();
}


/* Free layers list */

void    LNeuralNetwork::freeLayersList()
{
    for( uint32_t i = 0; i < layersList.size(); i++ )
    {
        layersList.at(i)->freeNeuronsList();
        delete layersList.at(i);
    }
    layersList.clear();
    layersList.shrink_to_fit();
}


/* Add a Layer to the Neural Network */

void    LNeuralNetwork::addLayer( uint32_t numberConnections,
                                  uint64_t numberNeurons )
{
    LLayer* layer = new LLayer( numberConnections, numberNeurons );
    layersList.push_back( layer );
}


/* Return the number of layers in the neural network */

uint32_t    LNeuralNetwork::getLayerCount() const
{
    return (uint32_t)layersList.size();
}


/* Set the learningRate of the neural network */

void    LNeuralNetwork::setLearningRate( float learningRate )
{
    mLearningRate = learningRate;
}


/* Set the inputs of the neural network */
void    LNeuralNetwork::setInputs( std::vector<float> arrayOfInputs )
{
    if( mArrayOfInputs.capacity() < arrayOfInputs.size() )
    {
        mArrayOfInputs.resize( arrayOfInputs.size() );
    }
    mArrayOfInputs = arrayOfInputs;
}


/* Set the inputs of a specified layer */

void    LNeuralNetwork::setLayers( std::vector<float> arrayOfInputs,
                                   uint32_t layerIndex )
{
    if( layerIndex > getLayerCount() -1 )
    {
        fprintf( stderr, "NN Error at setLayers: layerIndex = %d "
                 "exceeded limits = %d\n",  layerIndex, getLayerCount() -1 );
    }
    else
    {
        layersList.at(layerIndex)->setInputs( arrayOfInputs );
    }
}


/* Set the outputs of the neural network */

void    LNeuralNetwork::setOutputs( std::vector<float> arrayOfOutputs )
{
    if( mArrayOfOutputs.capacity() < arrayOfOutputs.size() )
    {
        mArrayOfOutputs.resize( arrayOfOutputs.size() );
    }
    mArrayOfOutputs = arrayOfOutputs;
}


/* Return the outputs of the neural network */

std::vector<float>  LNeuralNetwork::getOutputs() const
{
    return mArrayOfOutputs;
}


/* Process the neural network's input values and convert them to an output
   pattern using all layers in the network */

void    LNeuralNetwork::processInputsToOutputs( std::vector<float>
                                                arrayOfInputs )
{
    setInputs( arrayOfInputs );

    //Check to make sure the number of neural network inputs matches the
    //neuron connection count in the first layer
    if( getLayerCount() > 0 )
    {
        if( mArrayOfInputs.size() != layersList.at(0)->neuronsList.at(0)->
                                                        getConnectionCount() )
        {
            fprintf( stderr, "NN Error at processInputsToOutputs: The number of"
                     " inputs do NOT match the NN\n" );
            exit(-1);
        }
        else
        {
            //The number of inputs are fine : continue
            for( uint32_t i = 0; i < getLayerCount(); i++ )
            {
                //Set the inputs for each layer: The first layer gets it's input
                //data from the NN whereas the 2nd and subsequent layers get
                //their input data from the previous layer's actual output.
                if( i == 0 )
                {
                    setLayers( arrayOfInputs, i );
                }
                else
                {
                    setLayers( layersList.at(i-1)->mActualOutputsList, i );
                }
                //Now that the layer has had it's input values set, it can now
                //process this data, and convert them into an output using the
                //layer's neurons. The outputs will be used as inputs in the
                //next layer (if available).
                layersList.at(i)->processInputsToOutputs();
            }
            //Once all the data has filtered through to the end of network, we
            //can grab the actualOutputs of the last layer.
            //These values become or will be set to the NN output values
            //(arrayOfOutputs), through the setOutputs function call.
            setOutputs(layersList.at( getLayerCount()-1 )->mActualOutputsList);
        }
    }
    else
    {
        fprintf( stderr, "Error: There are no layers in this "
                 "Neural Network\n" );
        exit(-1);
    }
}


/* Train the entire network using an array */

void    LNeuralNetwork::trainNetwork( std::vector<float> inputsList,
                                      std::vector<float> expectedOutputsList )
{
    //Populate the ENTIRE network by processing the inputData
    processInputsToOutputs( inputsList );

    //Train each layer - from back to front (back propagation)
    for( double i = getLayerCount() - 1; i > -1; i-- )
    {
        if( i == getLayerCount() - 1 )
        {
            layersList.at(i)->setDeltaError( expectedOutputsList );
            layersList.at(i)->trainLayer( mLearningRate );
            mNetworkError = layersList.at(i)->getLayerError();
        }
        else
        {
            //Calculate the expected value for each neuron in this layer
            //(eg hidden layer)
            for( uint64_t j = 0; j < layersList.at(i)->getNeuronCount(); j++ )
            {
                //Reset the delta error of this neuron to zero
                layersList.at(i)->neuronsList.at(j)->mDeltaError = 0;
                //The delta error of a hidden layer neuron is equal to the sum
                //of the product of the connection.weight and error of the
                //neurons in the next layer(eg output Layer).
                //Connection#1 of each neuron in the output layer connect with
                //Neuron#1 in the hidden layer.
                for( uint64_t k = 0; k < layersList.at(i+1)->getNeuronCount();
                     k++ )
                {
                    layersList.at(i)->neuronsList[j]->mDeltaError +=
                        ( layersList.at(i+1)->neuronsList.at(k)->
                        connectionsList.at(j)->mWeight * layersList.at(i+1)->
                        neuronsList.at(k)->mDeltaError );
                }
                //Now that we have the sum of Errors x weights attached to this
                //neuron, we must multiply it by the derivative of the
                //activation function.
                layersList.at(i)->neuronsList.at(j)->mDeltaError *= (
                    layersList.at(i)->neuronsList.at(j)->mNeuronOutputValue *
                    ( 1 - layersList.at(i)->neuronsList.at(j)->
                    mNeuronOutputValue ) );
            }
            //Then we have all the necessary fields populated, we can now train
            //this hidden layer and then clear the Expected outputs, ready for
            //the next round
            layersList.at(i)->trainLayer( mLearningRate );
            layersList.at(i)->clearExpectedOutputs();
        }
    }
}


/* Train the entire network, using an array of input and expected data
   within a list of array */

void    LNeuralNetwork::trainingCycle( std::vector<std::vector<float> >
                        trainingInputList, std::vector<std::vector<float> >
                        trainingExpectedList, bool trainRandomly )
{
    uint32_t         dataIndex;

    //Re-initialize the training Error with every cycle
    mTrainingError = 0;

    //Cycle through the training data either randomly or sequentially
    for( uint32_t i = 0; i < trainingInputList.size(); i++ )
    {
        if( trainRandomly )
        {
            random.unique_rand_a_b( 0, trainingInputList.size() );
            dataIndex = random.getUniqueRandomInt();
        }
        else
        {
            dataIndex = i;
        }
        trainNetwork( trainingInputList.at(dataIndex),
                      trainingExpectedList.at(dataIndex) );

        //Use the networkError variable which is calculated at the end of each
        //individual training session to calculate the entire trainingError
        mTrainingError += std::abs( mNetworkError );
    }
}


/* Train the network until the Error is below a specific threshold */

void    LNeuralNetwork::autoTrainNetwork( std::vector<std::vector<float> >
            trainingInputList, std::vector<std::vector<float> >
            trainingExpectedList, float trainingErrorTarget,
            uint64_t cycleLimit )
{
    mTrainingCounter    = 0;
    mRetrainChances     = 0;
    mTrainingError      = 9999.0;

    aTN( trainingInputList, trainingExpectedList, trainingErrorTarget,
                                                                cycleLimit );

    fprintf( stdout, "CycleLimit has been reached after %llu training. Cycles"
             " have been retrained %hhu times.\nError rate is = %f\n",
             mTrainingCounter, mRetrainChances, mTrainingError );
}


void    LNeuralNetwork::aTN( std::vector<std::vector<float> >
            trainingInputList, std::vector<std::vector<float> >
            trainingExpectedList, float trainingErrorTarget,
            uint64_t cycleLimit )
{
    uint64_t trainingCounter = 0;

    //Cycle through the training data until the trainingError gets below
    //trainingErrorTarget (eg. 0.0005) or the training cycles have exceeded the
    //cycleLimit variable (eg. 10000).
    while( ( trainingCounter < cycleLimit ) &&
           ( mTrainingError > trainingErrorTarget ) )
    {
        if( trainingCounter % TRAINING_SHOW_ERROR_RATIO == 0 )
        {
            fprintf( stdout, "Cycle %2hhu ; Training counter = %12llu && Training"
                     " error = %12f\r", mRetrainChances + 1, trainingCounter,
                     mTrainingError );
        }

        mTrainingError = 0;
        //Cycle through the training data randomly
        trainingCycle( trainingInputList, trainingExpectedList, true );
        //Increment the training counter to prevent endless loop
        trainingCounter++;
    }

    //Due to the random nature in which this neural network is trained. There
    //may be occasions when the training error may drop below the threshold.
    //To check if this is the case, we will go through one more cycle (but
    //sequentially this time), and check the trainingError for that cycle, if
    //the training error is still below the trainingErrorTarget, then we will
    //end the training session. If the training error is above the
    //trainingErrorTarget, we will continue to train. It will do this check a
    //Maximum of 9 times.
    if( trainingCounter < cycleLimit )
    {
        trainingCycle( trainingInputList, trainingExpectedList, false );
        trainingCounter++;

        if( mTrainingError > trainingErrorTarget )
        {
            if( mRetrainChances < 10 )
            {
                mRetrainChances++;
                aTN( trainingInputList, trainingExpectedList,
                     trainingErrorTarget, cycleLimit );
            }
        }
    }
    mTrainingCounter += trainingCounter;
}
