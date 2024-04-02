#include <json.hpp>
#include <curl/curl.h>

#include <Config.hpp>

using json = nlohmann::json;

class PostJson{
    private:
    json m_json;

    public:
        PostJson();
        void post_json();
        void update_json(json j);
};