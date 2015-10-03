#include "thresholdLines.h"

thresholdLines::thresholdLines(double ALPHA,
        double BETA, double PONE, double PZERO){
    
    /*Take in constants*/
    m_ALPHA = ALPHA;
    m_BETA = BETA;
    m_PONE = PONE;
    m_PZERO = PZERO;
    m_upperLine = std::vector<double>();
    m_lowerLine = std::vector<double>();
  
     /*Prime the vectors with 500 elements*/
    calcNextset();
};

void thresholdLines::calcNextset()
{
    /* It should always be the case that upperLine and lowerLine have the 
     * same number of elements
     */
    
    long unsigned int m = 0;
    
    if (m_upperLine.size() != 0)
        m = m_upperLine.size() + 1;
    
    long unsigned int lim = m + 500;
    
    std::cout << "Adding threshold indicies: " <<  m << std::endl;
    
    /* Compute constants*/
    double C1 = (1 - m_PZERO) / (1 - m_PONE);
    double C2 = (1 - m_PONE) / (1 - m_PZERO);
    double C3 = m_PONE / m_PZERO;
    double denom = std::log(C3) - std::log(C2);
    double slope = std::log(C1) / denom;
    double lower_b = std::log(m_BETA / (1 - m_ALPHA)) / denom;
    double upper_b = std::log((1 - m_BETA) / m_ALPHA) / denom;
    
    /*Next 500 Points in the line*/
    for (;m != lim; m++){
        m_upperLine.push_back((m * slope) + upper_b);
        m_lowerLine.push_back((m * slope) + lower_b);
    };
    
};

int thresholdLines::compare(int value, int m){
    /*Do we need more Line?*/
    while (m > (m_upperLine.size() - 1))
        calcNextset();
    
    //std::cout << "Values Compared are: " <<  m_upperLine[m] << " " << value << " " << m_lowerLine[m] << " for index: " << m << std::endl;
     
    if (value > m_upperLine[m]) //upper crossing
        return 1; 
    else if (value < m_lowerLine[m]) //lower crossing
        return -1;
    else    //in the middle
        return 0; 
};

void thresholdLines::printLines(int N){
    for(int i = 0; i < N; i++){
        std::cout << i << " , " << m_lowerLine[i] << " , " << m_upperLine[i] << std::endl;
    }
};

int thresholdLines::stepToComp(int cur_pos, int cur_step){
    int lim = EXTRAPEND;    
    
    int go_up = cur_pos; //getting ones from the rest of the flips
    int go_down = cur_pos; //getting zeros from the the rest of the flips
        
    for(int m = 0; m < lim; m++){
        if (compare(go_up,m + cur_step) > 0)
            return m;
        if (compare(go_down,m + cur_step)< 0)
            return m;
        
        //Make the up variable climb
        go_up++;
    }
    
    /* Failed to find the value before we ran out of extrapolation points.*/
    return -1;
};