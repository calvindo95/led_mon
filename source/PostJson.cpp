#include <PostJson.hpp>

PostJson::PostJson(){}

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

// Will update/insert json object into PostJson json object
void PostJson::update_json(json j){
    m_json.update(j);
}