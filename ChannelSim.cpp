#include "ChannelSim.h"

int main(){
    thresholdLines TL(0.02,0.02,0.2313,0.17); // Avg Steps: 671 Run Drift: 84 - less that 1% drift.
    std::random_device rd;
    
    
    /* Make a shared pointer for the mersenne twister
     * all gen samples will need one
     */
    auto gen = std::make_shared<std::mt19937>(rd());    
    std::uniform_real_distribution<double> uni_dis(0, 1); 
        
//    Choosing multiple channel sets (will need this later)    
//    std::vector<sampleGen> channels;
//    for (int i = 0; i != CHANNELS; i++){
//        double p = uni_dis(*gen);
//        
//        /* each sample set get's it own bernoulli dist but a copy of the
//         * mersenne twister. 
//         */
//        std::bernoulli_distribution ber_dis(p);
//        channels.push_back(sampleGen(gen,ber_dis));
//    };
    
    
    std::bernoulli_distribution ber_dis(0.2);    
    std::vector<int> steps_run;
    std::vector<int> dec_run;
    
    /* This loop can be used to tune the Threshold Line parameters. We  
     * choose parameters until we get the result of a large number of runs to 
     * to have the worst case E(n) we want. We can also identify bias in the 
     * Test by seeing if it assigns the center of the indifference region to 
     * Hypothesis 1 as often as it does Hypothesis 0. This is done by summing 
     * the decisions. If the test is biased then over a large number of runs it 
     * will drift
    */
    
    for( int run = 0; run != RUNS; run++){
        
        // Create a new Set of samples from the Bernoulli distribution
        sampleGen chan = sampleGen(gen,ber_dis); //What happens to the old one?
        
        //Tracking Variables
        int time_ind = 0;
        int cur_sum = chan.dSum(time_ind);
        int cur_steps = TL.stepToComp(cur_sum, time_ind);
    
        //Sample until we no longer need steps to go
        //while ( cur_steps > 0 ) {
        while ( TL.compare(cur_sum, time_ind) == 0 ) {
            time_ind++;
            cur_sum = chan.dSum(time_ind);
          //  cur_steps = TL.stepToComp(cur_sum, time_ind);
        };
        
        steps_run.push_back(time_ind);
        dec_run.push_back(TL.compare(cur_sum, time_ind));
    };
    
    double mean_steps = std::accumulate(steps_run.begin(),steps_run.end(),0) / RUNS;
    double sum_dec = std::accumulate(dec_run.begin(),dec_run.end(),0);
    
    std::cout << "Avg Steps: " << mean_steps << " Run Drift: " << sum_dec << std::endl;
};

//Single time index, multiple channesl
//for(auto& chan: channels){
//         int cur_sum = chan.dSum(1);
//         int step_tc = TL.stepToComp(cur_sum, 1);
//         std::cout << "\nCurrent sum " << cur_sum << " requires Step to complete " << step_tc << std::endl;
//    }


// OLD Tests
//    std::bernoulli_distribution d1(0.45);    
//    sampleGen s1(sp1,d1);
//    
//    std::bernoulli_distribution d2(0.05);
//        sampleGen s2(sp2,d2);
//    
//    std::bernoulli_distribution d3(0.2);
//    sampleGen s3(sp3,d3);
//    
//    int index = 100;
//    int s1_sum = s1.dSum(index);
//    int s2_sum = s2.dSum(index);
//    int s3_sum = s3.dSum(index);
//    
//    int s1_res = TL.compare(s1_sum,index);
//    int s2_res = TL.compare(s2_sum,index);
//    int s3_res = TL.compare(s3_sum,index);
//    
//    std::cout << "The " << index <<" step for s1 is: " << s1_res << std::endl;    
//    std::cout << "The " << index <<" step for s2 is: " << s2_res << std::endl;
//    std::cout << "The " << index <<" step for s3 is: " << s3_res << std::endl;