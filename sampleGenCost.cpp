#include "SampleGenCost.h"

sampleGenCost::sampleGenCost(std::shared_ptr<thresholdLines> aTL,
            std::shared_ptr<std::mt19937> gen,
            std::bernoulli_distribution dis,
            double alambda): 
            sampleGen(gen, dis)
{
    TL = aTL;
    lambda = alambda;
    cur_step = 0;
    step_cost = 0;
};

sampleGenCost::~sampleGenCost(){

};

void sampleGenCost::takeSample(){
    cur_step++;
    step_cost = TL->stepToComp(dSum(cur_step),cur_step); //This is the expensive operation, only do it when we actually have to
};

double sampleGenCost::getCurCost(){
    if (getCurDec() == 0)
        return step_cost + (lambda * cur_step); //This is the cheap operation, We'll call this many times
    else
        return LARGENUMBER;
};

int sampleGenCost::getCurDec(){
    return TL->compare(dSum(cur_step),cur_step);
};

int sampleGenCost::getStep(){
  return cur_step;  
};