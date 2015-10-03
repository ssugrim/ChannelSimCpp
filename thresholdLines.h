/* 
 * File:   thresholdLines.h
 * Author: james
 *
 * Created on September 26, 2015, 6:25 PM
 */


#ifndef THRESHOLDLINES_H
#define	THRESHOLDLINES_H

#define EXTRAPEND 100 //At worst the lines are like 25 steps apart. If we hit this limit something is wrong

#include<vector>
#include<cmath>
#include<iostream>

class thresholdLines{
private:
    std::vector<double> m_upperLine, m_lowerLine;
    double m_ALPHA, m_BETA, m_PONE, m_PZERO;
    
    /* Compute another 500 Points*/
    void calcNextset();
    
public:
    /*Default constructor action is to compute the first 500 points*/
    thresholdLines(double,double,double,double);
    
    ~thresholdLines(){};
    
    /*For a given int return check if it is outsidie the lines
     * return 1 if it is above
     * return 0 if it is in between
     * return -1 if it is below
     */
    int compare(int, int);
    
    /*Compute the number of steps required to reach the end*/
    int stepToComp(int,int);
    
    /*Print out some values for Plotting / refrence*/
    void printLines(int);
};


#endif	/* THRESHOLDLINES_H */

