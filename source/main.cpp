#include <iostream>
#include <ostream>
#include <unistd.h>
#include <chrono>

#include <ProcessLoop.hpp>

int main()
{
    ProcessLoop pl;
    pl.enable_cpu_mon();

    pl.start();
} 