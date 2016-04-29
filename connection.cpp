/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:47:42 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/24 13:47:56 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/* Default constructor for a Connection  */

LConnection::LConnection()
{
    //fprintf( stderr, "Connecting the neuron\r" );

    LRandom     random;

    randomWeight();
    mConnEntry  = 0.0;
    mConnExit   = 0.0;
}


/* Custom weight for this Connection constructor  */

LConnection::LConnection( float weight )
{
    //fprintf( stderr, "Connecting the neuron\r" );

    LRandom     random;

    setWeight( weight );
    mConnEntry  = 0.0;
    mConnExit   = 0.0;
}


/* Deallocate memory */

LConnection::~LConnection()
{
    //fprintf( stderr, "Deleting class LConnection\r" );
}


/* Set the weight of this connection  */

void    LConnection::setWeight( float weight )
{
    mWeight = weight;
}


/* Randomize the weight of this connection
   Can be used to wipe the "memory" of the connection */

void    LConnection::randomWeight()
{
    random.unique_frand_a_b( 0.0, 2.0 );
    setWeight( random.getUniqueRandomFloat() - 1.0 );
}


/* Calculate and store the output of this connection  */

float   LConnection::computeConnExit( float connEntry )
{
    mConnEntry = connEntry;
    mConnExit = mConnEntry * mWeight;
    return mConnExit;
}
