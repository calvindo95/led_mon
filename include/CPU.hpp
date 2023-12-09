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

class CPU{
    private:
        struct last_values{
            unsigned long long lastTotalUser;
            unsigned long long lastTotalUserLow;
            unsigned long long lastTotalSys;
            unsigned long long lastTotalIdle;
            FixedDeque<double,5> fd;
        };

        std::vector<last_values> vec_lv;

        bool m_flag = false;
        TSQueue<std::vector<double>> m_que;
        std::mutex m_mutex;
        std::condition_variable m_cond;

        void monitor_cpu();

    public:
        CPU();

        std::vector<double> calc_per_cpu();
        std::vector<double> get_per_cpu();

        double get_cpu u();

        void print_per_cpu();   // prints per core cpu usage
        void print_cpu();       // prints overall cpu usage


        int numProcessors;
};

