#include <Config.hpp>

Config::Config(){
    update_config("LED_MON_SETTINGS_JSON");
    update_config("LED_MON_SERVER_IP");
    update_config("LED_MON_SERVER_PORT");
    update_config("uSECONDS");
    update_config("PER_CPU");
}

Config& Config::get_config(){
    static Config config;
    return config;
}

void Config::update_config(const char* env_var){
    std::stringstream ss;
    char* buffer = getenv(env_var);

    // Check env vars first --> takes precedent
    if(buffer != NULL){
        try{
            env_vars.insert(std::pair<std::string,std::string>(env_var,buffer));
            return;
        }
        catch(const char* e){
            ss << "ERROR: " << env_var << " - " << e << std::endl;
            std::cout << ss.str() << std::endl;
            return;
        }
    }
    else{
        std::cout << "INFO: " << env_var << " env var is not set, checking json" << std::endl;
        
        std::ifstream ifs;
        ifs.open(get_env_var("LED_MON_SETTINGS_JSON"));

        json j = json::parse(ifs);
        
        ifs.close();

        if (j.contains(env_var)){
            std::cout << "INFO: " << env_var << " found in " << get_env_var("LED_MON_SETTINGS_JSON") << std::endl;

            env_vars.insert(std::pair<std::string,std::string>(env_var,j.at(env_var)));
        }
        else{
            std::cerr << "ERROR: " << env_var << " not found in " << get_env_var("LED_MON_SETTINGS_JSON") << std::endl;
        }
    }
}

std::string Config::get_env_var(const char* env_var){
    std::map<std::string,std::string>::iterator it = env_vars.find(env_var);

    // return empty string if env var not in map
    if(it == env_vars.end()){
        return "";
    }
    return it->second;
}