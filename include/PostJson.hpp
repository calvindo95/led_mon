#include <json.hpp>
#include <curl/curl.h>

#include <Config.hpp>

using json = nlohmann::json;

class PostJson{
    private:
    int m_num_processors;
    double m_cpu_val;
    json m_json;

    void parse_json();

    public:
    PostJson(int num_processors, double cpu_val);
    void post_json();
};