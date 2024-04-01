#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <map>
#include <fstream>

#include <json.hpp>

using json = nlohmann::json;

// Singleton class to store env vars
class Config{
    private:
        Config();
        void update_config(const char* env_var);

        // Config vars
        std::map<std::string,std::string> env_vars;

    public:
        static Config& get_config();
        std::string get_env_var(const char* env_var);

};