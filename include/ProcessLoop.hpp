#include <PostJson.hpp> 
#include <CPU.hpp>

#include <json.hpp>
#include <iostream>

class ProcessLoop{
    private:
        bool m_cpu_mon = false;
        bool m_mem_mon = false;

        Config& m_config = Config::get_config();
        CPU m_cpu;

        void process();

    public:
        ProcessLoop();

        void start();

        void enable_cpu_mon();
        void disable_cpu_mon();

        void enable_mem_mon();
        void disable_mem_mon();
};