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
            std::vector<double> vals = cpu.get_per_cpu();

            PostJson pj(cpu.numProcessors, vals);
            pj.post_json();

            usleep(1000000);
        }
    }
    else{
        while(true){
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            double cpu_val = cpu.get_cpu();
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
            PostJson pj(cpu_val);
            pj.post_json();
            
            usleep(500000);
        }
    }
} 