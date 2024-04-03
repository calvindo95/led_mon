#include <json.hpp>

using json = nlohmann::json;

class Monitor{
    protected:
        virtual json get_json() = 0;
};