#include "sampleGen.h"

sampleGen::sampleGen(std::shared_ptr<std::mt19937> gen ,std::bernoulli_distribution samp){
    m_gen = gen;
    m_samp = samp;
    m_history = std::vector<bool>();
    
    genSamples();
};

sampleGen::~sampleGen(){
   // std::cout << "Destroying samples" <<std::endl;
    
}

void sampleGen::genSamples(){
    
    long unsigned int m = 0;
    
    if (m_history.size() != 0)
        m = m_history.size() + 1;   
    
    long unsigned int lim = m + 50;
    
    //std::cout << "Generating Samples from " << m << std::endl;
    
    for(;m != lim; m++)
        m_history.push_back(m_samp(*m_gen));    
};

int sampleGen::dSum(int N){
 /* Make sure I have enough samples to compute the sum*/   
  while (N > (m_history.size() - 1))
        genSamples();
  
  /*Make iterators range*/
  auto start = m_history.begin();
  auto end = m_history.begin()+N;
  
  return std::accumulate(start,end,0);
};