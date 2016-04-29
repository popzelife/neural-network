/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:41:56 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/24 13:42:42 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONNECTION_H
#define _CONNECTION_H

/* Connection wrapper class */

class LConnection
{
    friend class LNeuron;
    friend class LLayer;
    friend class LNeuralNetwork;

    public:
        //Initialize variables
        LConnection();
        LConnection( float weight );
        //Deallocate memory
        ~LConnection();


        //Set the weight of this connection
        void setWeight( float weight);
        //Randomize the weight of this connection
        void randomWeight();
        //Calculate and store the output of this connection
        float computeConnExit( float connEntry );


    private:
        LRandom     random;

        //Synaptic variables
        float       mConnEntry;
        float       mWeight;
        float       mConnExit;
};

#endif // _CONNECTION_H
