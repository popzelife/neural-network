/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neuron.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 15:09:30 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/24 15:09:46 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _NEURON_H
#define _NEURON_H

/* Neuron wrapper class */

class LNeuron
{
    friend class LLayer;
    friend class LNeuralNetwork;

    public:
        //Initialize variables
        LNeuron();
        LNeuron( uint32_t countConnections );
        //Deallocate memory
        ~LNeuron();


        //Add a Connection to this neuron
        void addConnection( LConnection* connection );
        //Randomize the bias of this Neuron
        void randomBias();
        //Convert the neuronInputValue to an neuronOutputValue
        float computeNeuronOutput( std::vector<float> connectEntryValues );
        //Sigmoid activation function
        float activation( float x );


        //Set the bias of this neuron
        void setBias( float bias );


        //Get the number of connections associated with this neuron
        uint32_t getConnectionCount() const;
        //Get the bias of this neuron for Layer computing
        float getBias() const;
        //Get the delta error for layer computing
        float getDeltaError() const;


        //Safely free the vector list
        void freeConnectionsList();


    private:
        LRandom     random;

        //Dynamic array to hold connections
        std::vector<LConnection*>   connectionsList;

        //Neuron variables
        float                       mBias;

        float                       mNeuronInputValue;
        float                       mNeuronOutputValue;

        float                       mDeltaError;
};

#endif // _NEURON_H
