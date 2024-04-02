#include <ProcessLoop.hpp>

ProcessLoop::ProcessLoop(){
    // init
}

void ProcessLoop::process(){
    // logic to retrieve hardware data and post json
    while(true){
        PostJson pj;

        if(m_cpu_mon){
            json j_cpu;
            
            if(m_cpu.is_multi_cpu()){
                j_cpu.update(m_cpu.get_json(m_cpu.calc_multi_cpu()));
            }
            else{
                j_cpu.update(m_cpu.get_json(m_cpu.calc_cpu()));
            }

            pj.update_json(j_cpu);
        }

        if(m_mem_mon){
            // Need to implement memory monitoring
        }
        
        pj.post_json();
        usleep(std::stoi(m_config.get_env_var("uSECONDS")));
    }
}

void ProcessLoop::start(){
    process();
}

void ProcessLoop::enable_cpu_mon(){
    m_cpu_mon = true;
}

void ProcessLoop::disable_cpu_mon(){
    m_cpu_mon = false;
}

void ProcessLoop::enable_mem_mon(){
    m_mem_mon = true;
}

void ProcessLoop::disable_mem_mon(){
    m_mem_mon = false;
}
    