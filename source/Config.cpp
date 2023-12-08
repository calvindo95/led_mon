#include <Config.hpp>

Config::Config(){
    update_config("HTTP_SERVER_IP");
    update_config("HTTP_SERVER_PORT");
    update_config("uSECONDS");
}

Config& Config::get_config(){
    static Config config;
    return config;
}

void Config::update_config(const char* env_var){
    std::stringstream ss;
    char* buffer = getenv(env_var);

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

    ss << "ERROR: " << env_var << " is not set" << std::endl;
    std::cout << ss.str() << std::endl;
}

std::string Config::get_env_var(const char* env_var){
    std::map<std::string,std::string>::iterator it = env_vars.find(env_var);

    // return empty string if env var not in map
    if(it == env_vars.end()){
        return "";
    }
    return it->second;
}