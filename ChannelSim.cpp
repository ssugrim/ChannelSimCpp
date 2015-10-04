#include "ChannelSim.h"

/*Reslts of type 1 expirment*/
struct exp1_res {
    int steps, dec;
    
    /*simple constucotor for initilization*/
    exp1_res(int s, int d):steps(s),dec(d){};
};

/* Experiment type 1:
 * This experiment can be used to tune the Threshold Line parameters. We  
 * choose parameters until we get the result of a large number of runs to 
 * to have the worst case E(n) we want. We can also identify bias in the 
 * Test by seeing if it assigns the center of the indifference region to 
 * Hypothesis 1 as often as it does Hypothesis 0. This is done by summing 
 * the decisions. If the test is biased then over a large number of runs it 
 * will drift
*/
exp1_res exp1(
    std::shared_ptr<std::mt19937> gen, //The "Randomness" generator
    std::shared_ptr<thresholdLines> TL, //Threshold lines
    std::bernoulli_distribution dis //Turns randomenss in Bernoulli dist
    )
{ 
    
        // Create a new Set of samples from the Bernoulli distribution
        sampleGen chan = sampleGen(gen,dis); 
        
        //Tracking Variables
        int time_ind = 0;
        int cur_sum = chan.dSum(time_ind);
        int cur_steps = TL->stepToComp(cur_sum, time_ind);
    
        //Sample until we no longer need steps to go
        //while ( cur_steps > 0 ) {
        while ( TL->compare(cur_sum, time_ind) == 0 ) {
            time_ind++;
            cur_sum = chan.dSum(time_ind);
          //  cur_steps = TL.stepToComp(cur_sum, time_ind);
        };
        
        return exp1_res(time_ind, TL->compare(cur_sum, time_ind));
};

struct exp2_res{

    exp2_res(){};
};

exp2_res exp2 (
    std::shared_ptr<std::mt19937> gen, //gen and TL should be common to all expirments
    std::shared_ptr<thresholdLines> TL, 
    std::uniform_real_distribution<double> dis //For picking parameters
    )
{
    /*TODO: Check to make sure uniform's range is correct?*/
    
    std::vector<sampleGen> channels;
    for (int i = 0; i != CHANNELS; i++){
        double p = dis(*gen);       
        std::bernoulli_distribution ber_dis(p);
        channels.push_back(sampleGen(gen,ber_dis));
    };
    return exp2_res();
};

int main(){
    /*Only need one TL object, so pass it around as a shared pointer*/
    auto TL = std::make_shared<thresholdLines> (0.02,0.02,0.2313,0.17); // Avg Steps: 671 Run Drift: 84 - less that 1% drift.
    
    /*used to seed Mersenne Twister*/
    std::random_device rd;
    
    /*Only need onf MT object, thus ...*/
    auto gen = std::make_shared<std::mt19937>(rd()); //This is the "Randomness". Many functions will use this pointer.
    
    /*Distribution objects I may use*/
    std::uniform_real_distribution<double> uni_dis(0, 1); 
    std::bernoulli_distribution ber_dis(0.2);    
    
    std::vector<int> steps_run;
    std::vector<int> dec_run;
    exp1_res res{0,0};
    
    
    
    for( int run = 0; run != RUNS; run++){
        res = exp1(gen, TL, ber_dis);
        steps_run.push_back(res.steps);
        dec_run.push_back(res.dec);
    };
    
    double mean_steps = std::accumulate(steps_run.begin(),steps_run.end(),0) / RUNS;
    double sum_dec = std::accumulate(dec_run.begin(),dec_run.end(),0);
    
    std::cout << "Avg Steps: " << mean_steps << " Run Drift: " << sum_dec << std::endl;
};