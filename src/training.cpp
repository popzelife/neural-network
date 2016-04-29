/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 17:25:57 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/27 17:26:06 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/* Add element to training inputs or outputs.
   If index is not specified then it simply push back ; if index is -2 it
   inserts at the beginning without deleting the first content ; if index is
   greater than the size, or if index is -1 it pushes back ; and if index is
   within content it erases and pastes on the existing content.
   #define TRAINING_ADD_TO_END    -1
   #define TRAINING_ADD_TO_BEGIN  -2 */

bool    LTraining::addToTrainingInputs( std::vector<float> input, long index )
{
    if( index < -2  )
    {
        fprintf( stderr, "Training Error at addToTrainingOutputs: negative "
                 "index set, choose a positive index instead.\n" );
        return false;
    }
    else if( index == TRAINING_ADD_TO_END )
    {
        mTrainingInputs.push_back( input );
    }
    else if( index == TRAINING_ADD_TO_BEGIN )
    {
        mTrainingInputs.insert( mTrainingInputs.begin(), input );
    }
    else
    {
        if( index > (long long)mTrainingInputs.size() )
        {
            mTrainingInputs.push_back( input );
            return true;
        }
        mTrainingInputs.at(index) = input;
    }
    return true;
}

bool    LTraining::addToTrainingOutputs( std::vector<float> output, long index )
{
    if( index < -2  )
    {
        fprintf( stderr, "Training Error at addToTrainingOutputs: negative "
                 "index set, choose a positive index instead.\n" );
        return false;
    }
    else if( index == TRAINING_ADD_TO_END )
    {
        mTrainingOutputs.push_back( output );
    }
    else if( index == TRAINING_ADD_TO_BEGIN )
    {
        mTrainingOutputs.insert( mTrainingOutputs.begin(), output );
    }
    else
    {
        if( index > (long long)mTrainingOutputs.size() )
        {
            mTrainingOutputs.push_back( output );
            return true;
        }
        mTrainingOutputs.at(index) = output;
    }
    return true;
}


/* Create a vector list at once */

void    LTraining::createInputsList( std::vector<std::vector<float>>
                                     inputsList )
{
    if( mTrainingInputs.size() == 0 )
    {
        clearTrainingInputs();
    }
    mTrainingInputs.resize( inputsList.size() );
    for( uint32_t i = 0; i < inputsList.size(); i++ )
    {
        mTrainingInputs.push_back( inputsList.at(i) );
    }
}

void    LTraining::createOutputsList( std::vector<std::vector<float>>
                                      outputsList )
{
    if( mTrainingOutputs.size() == 0 )
    {
        clearTrainingOutputs();
    }
    mTrainingOutputs.resize( outputsList.size() );
    for( uint32_t i = 0; i < outputsList.size(); i++ )
    {
        mTrainingOutputs.push_back( outputsList.at(i) );
    }
}


/* Clear elements from training inputs or outputs */

void    LTraining::clearTrainingInputs()
{
    if( mTrainingInputs.size() != 0 )
    {
        for( uint32_t i = 0; i < mTrainingInputs.size(); i++ )
        {
            mTrainingInputs.at(i).clear();
            mTrainingInputs.at(i).shrink_to_fit();
        }
        mTrainingInputs.clear();
        mTrainingInputs.shrink_to_fit();
    }
}

void    LTraining::clearTrainingOutputs()
{
    if( mTrainingOutputs.size() != 0 )
    {
        for( uint32_t i = 0; i < mTrainingOutputs.size(); i++ )
        {
            mTrainingOutputs.at(i).clear();
            mTrainingOutputs.at(i).shrink_to_fit();
        }
        mTrainingOutputs.clear();
        mTrainingOutputs.shrink_to_fit();
    }
}
