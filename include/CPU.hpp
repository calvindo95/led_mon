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
#include <json.hpp>

#include <Monitor.hpp>

using json = nlohmann::json;

class CPU: public Monitor{
    private:
        struct last_values{
            unsigned long long lastTotalUser;
            unsigned long long lastTotalUserLow;
            unsigned long long lastTotalSys;
            unsigned long long lastTotalIdle;
            FixedDeque<double,10> fd;
        };

        Config& m_config = Config::get_config();
        std::vector<last_values> vec_lv;
        bool m_is_multi_cpu = false;

    public:
        CPU();

        // These 3 variables/functions need to be moved to private once I figure out extern C stuff
        // Or I remove extern C entirely and remove python lib
        int m_num_processors;
        std::vector<double> calc_multi_cpu();
        double calc_cpu();

        void print_multi_cpu();   // prints per core cpu usage
        void print_cpu();       // prints overall cpu usage

        bool is_multi_cpu();
        
        json get_json();
};

