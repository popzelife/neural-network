/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 17:23:45 by qfremeau          #+#    #+#             */
/*   Updated: 2016/04/27 17:25:16 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TRAINING_H
#define _TRAINING_H

#define TRAINING_ADD_TO_END         -1
#define TRAINING_ADD_TO_BEGIN       -2

/* Training wrapper class */

class LTraining
{
    public:
        LTraining();
        ~LTraining();


        //Add element to training inputs or outputs
        bool addToTrainingInputs( std::vector<float> input, long index
                                  = TRAINING_ADD_TO_END );
        bool addToTrainingOutputs( std::vector<float> output, long index
                                   = TRAINING_ADD_TO_END );
        //Create a vector list at once
        void createInputsList( std::vector<std::vector<float>> inputsList );
        void createOutputsList( std::vector<std::vector<float>> outputsList );


        //Clear elements from training inputs or outputs
        void clearTrainingInputs();
        void clearTrainingOutputs();


    private:
        //Dynamic lists for training functions
        std::vector<std::vector<float>>     mTrainingInputs;
        std::vector<std::vector<float>>     mTrainingOutputs;
};

#endif // _TRAINING_H
