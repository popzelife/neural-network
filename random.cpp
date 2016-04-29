/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 23:39:41 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/14 23:48:12 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/* Initializes variables */
LRandom::LRandom()
{
    //fprintf( stderr, "Creating class LRandom\r" );
}


/* Deallocate */

LRandom::~LRandom()
{
    //fprintf( stderr, "Deleting class LRandom\r" );
}


/* Compute random number from range */

void    LRandom::rand_a_b( int a, int b )
{
    mRandomInt = rand() % ( b - a ) + a;
}

void    LRandom::frand_a_b( float a, float b )
{
    mRandomFloat = ( rand() / (float)RAND_MAX ) * ( b - a ) + a;
}


/* Fill an array to create unique random choice */

void    LRandom::unique_rand_a_b( int a, int b )
{
    int     temp = 0;
    mIntLength = b - a;
    mI = 0;

    mIntArray.resize(mIntLength);
    for( int i = 0; i < mIntLength; i++ )
    {
        mIntArray.at(i) = i + a;
    }

    //Swap between i and mRandomInt
    for( int i = 0; i < mIntLength; i++ )
    {
        rand_a_b( 0, mIntLength );
        temp = mIntArray.at(i);
        mIntArray.at(i) = mIntArray.at(mRandomInt);
        mIntArray.at(mRandomInt) = temp;
    }
}

void    LRandom::unique_frand_a_b( float a, float b )
{
    float   temp = 0.0;
    mFloatLength = b - a;
    mF = 0.0;

    mFloatArray.resize(mFloatLength);
    for( float i = 0.0; i < mFloatLength; i++ )
    {
        mFloatArray.at(i) = i + a;
    }

    //Swap between i and mRandomFloat
    for( float i = 0.0; i < mFloatLength; i++ )
    {
        frand_a_b( 0.0, mFloatLength );
        temp = mFloatArray.at(i);
        mFloatArray.at(i) = mFloatArray.at(mRandomFloat);
        mFloatArray.at(mRandomFloat) = temp;
    }
}


/* Get random number */

int     LRandom::getRandomInt() const
{
    return mRandomInt;
}

float  LRandom::getRandomFloat() const
{
    return mRandomFloat;
}


float  LRandom::getUniqueRandomFloat()
{
    if( mFloatLength - mF == 0.0 )
    {
        mF = 0.0;
    }
    mF++;

    return mFloatArray.at(mFloatLength - mF);
}

int     LRandom::getUniqueRandomInt()
{
    if( mIntLength - mF == 0 )
    {
        mI = 0;
    }
    mI++;

    return mIntArray.at(mIntLength - mI);
}
