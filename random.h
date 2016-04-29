/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 23:46:44 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/14 23:48:55 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RANDOM_H
#define _RANDOM_H

/* Random wrapper class to generate random methods */

class   LRandom
{
    public:
        //Initializes variables
        LRandom();
        //Deallocate
        ~LRandom();


        //Compute random number from range
        void rand_a_b( int a, int b );
        void frand_a_b( float a, float b );
        //Fill an array to create unique random choice
        void unique_frand_a_b( float a, float b );
        void unique_rand_a_b( int a, int b );


        //Get random int
        int getRandomInt() const;
        int getUniqueRandomInt();
        //Get random float
        float getRandomFloat() const;
        float getUniqueRandomFloat();


    private:
        //Random numbers
        std::vector<float>      mFloatArray;
        std::vector<int>        mIntArray;

        int         mRandomInt;
        float       mRandomFloat;
        int         mIntLength;
        float       mFloatLength;

        int         mI;
        float       mF;
};

#endif // _RANDOM_H
