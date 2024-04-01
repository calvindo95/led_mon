#include <iostream>
#include <ostream>
#include <unistd.h>
#include <chrono>

#include <CPU.hpp>
#include <PostJson.hpp>

int main()
{
    Config& config = Config::get_config();
    CPU cpu;
    
    bool per_cpu;
    std::istringstream(config.get_env_var("PER_CPU")) >> std::boolalpha >> per_cpu;

    // if multi or single cpu
    if(per_cpu){
        while(true){
            std::vector<double> vals = cpu.calc_multi_cpu();

            PostJson pj(cpu.numProcessors, vals);
            pj.post_json();

            usleep(200000);
        }
    }
    else{
        double cpu_val;
        while(true){
            cpu_val = cpu.calc_cpu();

            PostJson pj(cpu_val);
            pj.post_json();
            
            usleep(100000);
        }
    }
} 