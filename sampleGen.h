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

/* This class generates samples from a specific bernoulli distribution. The
 * Internal state can't be alterned by the public methods so it's safe to 
 * pass non-const refrences to these objects.
 */



class sampleGen{
private:
    /*
     * storing the history as vector of bools because bernoulli returns a bool
     * and the vector<bool> has some packing efficency. But the interface is 
     * still honored (push back and iterators work)
     */
    std::vector<bool> m_history;
        
    /* Randomness genetator is the same through out the expirment, gets feed
     * into distubution function object to geneate random values.
     */
    
    std::shared_ptr<std::mt19937> m_gen;
    
    /*Since each set of samples may come from a different parameter set
     * each geneator should have it's own copy of the distribution object
     */
    std::bernoulli_distribution m_samp;
    

protected:
    /*Apparently the good design is you make the implementation details virtual
     * but the interface public and non-virtual. That way the public interface
     * can't be changed, but the implmentation can. This is called the Template
     * Method pattern.
     * 
     * I'm maing this protected because the derived class may have to call it.
     */
    virtual int doDsum(int);

    
    /*Add 50 Samples samples to the history
     *
     * This is virutal in case some later class wants to generate sample differntly.
     */
    virtual void genSamples();
    
    
public:
    
    /* Base Constructor, Builds random number generator objects and sets parameters*/
    sampleGen(std::shared_ptr<std::mt19937>, std::bernoulli_distribution);
    
    virtual ~sampleGen();  //The destructor is empty any way (and my base class is concrete which I'm told is bad)
    
    /*Computes the sufficent statistic d up to int M */
    int dSum(int);
};

#endif	/* SAMPLEGEN_H */

