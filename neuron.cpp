/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neuron.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 15:08:49 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/24 15:08:59 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/* Default constructor for a Neuron */

LNeuron::LNeuron()
{
    //fprintf( stderr, "Creating a neuron\r" );

    LRandom     random;

    mNeuronInputValue   = 0.0;
    mNeuronOutputValue  = 0.0;
    mDeltaError         = 0.0;
    mBias               = 0.0;
}


/* Typical constructor of a Neuron - with random Bias and Connection weights */

LNeuron::LNeuron( uint32_t countConnections )
{
    //fprintf( stderr, "Creating a neuron\r" );

    randomBias();
    mNeuronInputValue   = 0.0;
    mNeuronOutputValue  = 0.0;
    mDeltaError         = 0.0;

    for( uint32_t i = 0; i < countConnections; i++ )
    {
        LConnection* connection = new LConnection();
        addConnection( connection );
    }
}


/* Deallocate memory */

LNeuron::~LNeuron()
{
    //fprintf( stderr, "Deleting class LNeuron\r" );
    freeConnectionsList();
}


/* Safely free the vector list */

void    LNeuron::freeConnectionsList()
{
    for( uint32_t i = 0; i < connectionsList.size(); i++ )
    {
        delete connectionsList[i];
    }
    connectionsList.clear();
    connectionsList.shrink_to_fit();
}


/* Add a connection to this neuron */

void    LNeuron::addConnection( LConnection* connection )
{
    connectionsList.push_back( connection );
}


/* Get the number of connections associated with this neuron */

uint32_t    LNeuron::getConnectionCount() const
{
    return connectionsList.size();
}


/* Set the bias of this neuron */

void    LNeuron::setBias( float bias )
{
    mBias = bias;
}


/* Randomize the bias of this neuron */

void    LNeuron::randomBias()
{
    random.unique_frand_a_b( 0.0, 1.0 );
    setBias( random.getUniqueRandomFloat() );
}


/* Convert the neuronInputValue to an neuronOutputValue
   Make sure the number of connEntryValues matches the number of connections */

float    LNeuron::computeNeuronOutput( std::vector<float> connectEntryValues )
{
    if( connectEntryValues.size() != getConnectionCount() )
    {
        fprintf( stderr, "Neuron Error at computeNeuronOutput(): wrong number"
                 " of connEntryValues\n" );
        exit(-1);
    }

    mNeuronInputValue = 0;

    //First sum all of the weighted connection values (connExit) attached
    //to this neuron
    for( uint32_t i = 0; i < connectionsList.size(); i++ )
    {
        mNeuronInputValue += connectionsList.at(i)->computeConnExit
                                                ( connectEntryValues.at(i) );
    }

    //Add the bias to the neuron's inputValue
    mNeuronInputValue += mBias;

    //Send the inputValue through the activation function to produce the
    //neuron's outputValue
    mNeuronOutputValue = activation( mNeuronInputValue );

    //Return the outputValue
    return mNeuronOutputValue;
}


/* Sigmoid activation function */

float   LNeuron::activation( float x )
{
    float activatedValue = 1 / ( 1 + exp( -1.0 * x ) );
    return activatedValue;
}
