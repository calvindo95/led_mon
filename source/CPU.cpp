#include <CPU.hpp>

CPU::CPU(){
    FILE* file_process_cpu;
    struct tms timeSample;
    char line[128];

    // calculate number of process
    file_process_cpu = fopen("/proc/cpuinfo", "r");
    numProcessors = 0;
    while(fgets(line, 128, file_process_cpu) != NULL){
        if (strncmp(line, "processor", 9) == 0) numProcessors++;
    }
    fclose(file_process_cpu);

    // initialize last_values struct for each cpu core
    for(int i = 0; i < numProcessors; i++){
        last_values lv;

        lv.lastTotalUser = 0.0;
        lv.lastTotalUserLow = 0.0;
        lv.lastTotalSys = 0.0;
        lv.lastTotalIdle = 0.0;
        lv.fd.push_back(0.0);

        vec_lv.push_back(lv);
    }

    // initialize monitoring thread
    std::thread t1(&CPU::monitor_cpu, this);
    t1.detach();
}

void CPU::monitor_cpu(){
     while(true){
        std::vector<double> cpu_vals = calc_per_cpu();
        if(m_flag){
            m_que.push(cpu_vals);
            m_flag = false;
        }
        usleep(200000);
    }
}

void CPU::print_per_cpu(){
    std::vector<double> cpu_vals = calc_per_cpu();

    for(int i = 0; i < cpu_vals.size(); i++){
        std::cout << cpu_vals[i] << std::endl;
    }
}

std::vector<double> CPU::get_per_cpu(){
    m_flag = true;
    return m_que.pop();
}

std::vector<double> CPU::calc_per_cpu(){
    std::vector<double> cpu_vals;
    std::ifstream file("/proc/stat");
    std::string proc_stat_line;
    while(std::getline(file, proc_stat_line)){
        for(int i = 0; i < numProcessors; i++){

            std::stringstream ss;
            ss << "cpu" << i << " ";

            // iterate each line in /proc/stats
            if(proc_stat_line.find(ss.str()) != std::string::npos){
                unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;
                double percent;

                std::string temp_str;
                std::istringstream iss(proc_stat_line);
                iss >> temp_str >> totalUser >> totalUserLow >> totalSys >> totalIdle;

                if (totalUser < vec_lv[i].lastTotalUser || totalUserLow < vec_lv[i].lastTotalUserLow ||
                    totalSys < vec_lv[i].lastTotalSys || totalIdle < vec_lv[i].lastTotalIdle){
                    //Overflow detection. Just skip this value.
                    percent = -1.0;
                }
                else{
                    total = (totalUser - vec_lv[i].lastTotalUser) + (totalUserLow - vec_lv[i].lastTotalUserLow) + (totalSys - vec_lv[i].lastTotalSys);
                    percent = total;
                    total += (totalIdle - vec_lv[i].lastTotalIdle);
                    percent /= total;
                    percent *= 100;

                    vec_lv[i].fd.push_back(percent);
                    cpu_vals.push_back(vec_lv[i].fd.get_avg());
                }

                vec_lv[i].lastTotalUser = totalUser;
                vec_lv[i].lastTotalUserLow = totalUserLow;
                vec_lv[i].lastTotalSys = totalSys;
                vec_lv[i].lastTotalIdle = totalIdle;
            }
        }
    }
    return cpu_vals;
}

void CPU::print_cpu(){
    double cpu_val = calc_cpu();

    std::cout << cpu_val << std::endl;
}

double CPU::calc_cpu(){
    std::ifstream file("/proc/stat");
    std::string proc_stat_line;
    std::string temp_str;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;
    double percent;

    std::getline(file, proc_stat_line);

    std::istringstream iss(proc_stat_line);
    iss >> temp_str >> totalUser >> totalUserLow >> totalSys >> totalIdle;

    if (totalUser < vec_lv[0].lastTotalUser || totalUserLow < vec_lv[0].lastTotalUserLow ||
        totalSys < vec_lv[0].lastTotalSys || totalIdle < vec_lv[0].lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - vec_lv[0].lastTotalUser) + (totalUserLow - vec_lv[0].lastTotalUserLow) + (totalSys - vec_lv[0].lastTotalSys);
        percent = total;
        total += (totalIdle - vec_lv[0].lastTotalIdle);
        percent /= total;
        percent *= 100;

        vec_lv[0].fd.push_back(percent);
    }

    vec_lv[0].lastTotalUser = totalUser;
    vec_lv[0].lastTotalUserLow = totalUserLow;
    vec_lv[0].lastTotalSys = totalSys;
    vec_lv[0].lastTotalIdle = totalIdle;

    return vec_lv[0].fd.get_avg();
}

extern "C"{
    CPU cpu;
    CPU* create_CPU(){
        return new CPU;
    }

    void delete_CPU(CPU* cpu){
        delete cpu;
    }

    void print_CPU(){
        cpu.print_cpu();
    } 

    void print_Per_CPU(){
        cpu.print_per_cpu();
    }

    double* calc_Per_CPU(int size){
        // Convert vector to array
        std::vector<double> tmp_vec = cpu.calc_per_cpu();
        double* d_arr = new double[size];

        std::copy(tmp_vec.begin(), tmp_vec.end(), d_arr);

        return d_arr;
    }

    void delete_Per_CPU(double* obj){
        delete obj;
    }

    double calc_CPU(){
        double d_tmp = cpu.calc_cpu();
        return d_tmp;
    }

    int get_Num_CPU(){
        return cpu.numProcessors;
    }
}