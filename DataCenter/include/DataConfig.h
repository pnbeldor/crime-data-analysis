#ifndef DATA_CONFIG_H
#define DATA_CONFIG_H

#include <map>
#include <string>

enum class DataFormat {
    JSON,
    CSV
};

enum class DataSource {
    LOCAL_FILE,
    HTTP_REQUEST
};

struct DataConfig {
    DataSource source;
    DataFormat format;
    std::string location; // file path or URL
    std::map<std::string, std::string> options;
};

#endif  //DATA_CONFIG_H
