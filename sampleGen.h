/* 
 * File:   SampleGen.h
 * Author: james
 *
 * Created on September 27, 2015, 6:29 PM
 * 
 * Generates Samples and statistics from those samples
 */

#ifndef SAMPLEGEN_H
#define	SAMPLEGEN_H
#include <vector>
#include <random>
#include <iostream>
#include <cstdint>
#include <numeric>
#include <memory>




class sampleGen{
private:
    /*
     * storing the history as vector of bools because bernoulli returns a bool
     * and the vector<bool> has some packing efficency. But the interface is 
     * still honored (push back and iterators work)
     */
    std::vector<bool> m_history;
        
    /* C++ scaffolding to support random number generation*/
    std::shared_ptr<std::mt19937> m_gen;
    std::bernoulli_distribution m_samp;
    
    /*Add 50 Samples samples to the history*/
    void genSamples();
    
public:
    
    /* Base Constructor, Builds random number generator objects and sets parameters*/
    sampleGen(std::shared_ptr<std::mt19937>, std::bernoulli_distribution);
    
    ~sampleGen();
    
    /*Computes the sufficent statistic d up to int M */
    int dSum(int);
};

#endif	/* SAMPLEGEN_H */

