#include <iostream>
#include <ostream>
#include <unistd.h>

#include <CPU.hpp>
#include <Config.hpp>

int main()
{
    Config& config = Config::get_config();
    
    CPU cpu;
    
    while(true){
        //cpu.print_per_cpu();
        std::vector<double> vals = cpu.get_per_cpu();
        for(int i = 0; i < vals.size(); i++){
            std::cout << "CPU" << i << ": " << vals[i] << std::endl;
        }
        usleep(250000);
    }
} 