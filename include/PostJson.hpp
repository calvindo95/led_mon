#include <json.hpp>
#include <curl/curl.h>

#include <Config.hpp>

using json = nlohmann::json;

class PostJson{
    private:
    int m_num_processors;
    double m_cpu_val;
    std::vector<double> m_cpu_vals;
    json m_json;

    void parse_json();

    public:
    PostJson(double cpu_val);
    PostJson(int num_processors, std::vector<double> cpu_vals);
    void post_json();
};