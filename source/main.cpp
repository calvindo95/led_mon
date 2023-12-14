#include <iostream>
#include <ostream>
#include <unistd.h>

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
            std::vector<double> vals = cpu.get_per_cpu();

            PostJson pj(cpu.numProcessors, vals);
            pj.post_json();

            usleep(1000000);
        }
    }
    else{
        while(true){
            double cpu_val = cpu.get_cpu();

            PostJson pj(cpu_val);
            pj.post_json();

            usleep(500000);
        }
    }
} 