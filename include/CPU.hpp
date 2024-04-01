#include <string.h>
#include <iostream>
#include <cstdio>
#include <sys/times.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <unistd.h>
#include <atomic>
#include <thread>

#include <FixedDeque.hpp> // wrapper deque class to calculate rolling average
#include <TSQueue.hpp>

#include <Config.hpp>

class CPU{
    private:
        struct last_values{
            unsigned long long lastTotalUser;
            unsigned long long lastTotalUserLow;
            unsigned long long lastTotalSys;
            unsigned long long lastTotalIdle;
            FixedDeque<double,10> fd;
        };

        std::vector<last_values> vec_lv;
        bool m_flag = false;

        // queue for per cpu
        TSQueue<std::vector<double>> m_que_per_cpu;
        
        // queue for single cpu
        TSQueue<double> m_que_cpu;

        void monitor_cpu();

    public:
        CPU();

        std::vector<double> calc_multi_cpu();
        double calc_cpu();

        void print_multi_cpu();   // prints per core cpu usage
        void print_cpu();       // prints overall cpu usage

        void print_per_cpu();   // prints per core cpu usage
        void print_cpu();       // prints overall cpu usage


        int numProcessors;
};

