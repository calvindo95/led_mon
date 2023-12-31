#include <PostJson.hpp>

PostJson::PostJson(int num_processors, double cpu_val):m_num_processors(num_processors), m_cpu_val(cpu_val){
    parse_json();
}

void PostJson::parse_json(){
    m_json["cpuNum"] = m_num_processors;
    m_json["cpu"] = m_cpu_val;

    std::cout << m_json.dump() << std::endl;
}

void PostJson::post_json(){
    CURL *curl;
    CURLcode res;

    Config& config = Config::get_config();

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl){
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::stringstream ss;
        ss << "http://" << config.get_env_var("HTTP_SERVER_IP") << ":" << config.get_env_var("HTTP_SERVER_PORT");
        
        curl_easy_setopt(curl, CURLOPT_URL, ss.str().c_str());
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, m_json.dump().c_str());

        res = curl_easy_perform(curl);

        if(res != CURLE_OK){
            std::cerr << "curl_easy_perform failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}