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
        cpu.print_per_cpu();
        usleep(200000);
    }
} 