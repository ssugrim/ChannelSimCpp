/* 
 * File:   SampleGenCost.h
 * Author: james
 *
 * Created on October 3, 2015, 11:47 PM
 * 
 * 
 * This class implements sample taking and cost calculations for a single channel.
 * It's current version implemnts the single test. It will need to be modified 
 * to take two sets of threshold lines and do the two-test.
 */

#include "sampleGen.h"
#include "thresholdLines.h"

#ifndef SAMPLEGENCOST_H
#define	SAMPLEGENCOST_H

#define LARGENUMBER 1000000


class sampleGenCost : protected sampleGen {
private:
    std::shared_ptr<thresholdLines> TL;
    int cur_step;
    double step_cost, lambda;
    
public:
    sampleGenCost(std::shared_ptr<thresholdLines>,
            std::shared_ptr<std::mt19937>,
            std::bernoulli_distribution,
            double);
    
    void takeSample(); //This actually updates step_cost
    double getCurCost(); //step_cost + lambda * steps taken.
    int getCurDec(); //What is the current decision?
    int getStep();
    
    ~sampleGenCost();
};

/*TODO:
 *
 * tamkeSample will bump up the sample count by one and then recompute the step_cost
 * getCurCost = step_cost + lambda * cur_step; 
 * constructor should call parent constuctor with args
 */

#endif	/* SAMPLEGENCOST_H */

