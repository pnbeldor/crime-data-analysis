#ifndef __UTILS_H__
#define __UTILS_H__


#include <string>
#include <utility>
#include <vector>

#include "simdjson.h"

class Utils
{
public:
    Utils();
    ~Utils();

    std::vector<std::vector<std::string>> ParseCSVData(const std::string& data_str);
    std::vector<std::string> ParseCSVDataLine(const std::string& dataLine);
    std::string ParseElement(const simdjson::dom::element& element);

    template <typename T1, typename T2>
    std::vector<std::pair<T1, T2>> ZipVectors(const std::vector<T1>& vec1, const std::vector<T2>& vec2)
    {
        std::vector<std::pair<T1, T2>> zippedResult;

        //Determine the minimum size to avoid out-of-bound access
        size_t minSize = std::min(vec1.size(), vec2.size());

        for (size_t i = 0; i < minSize; i++)
        {
            zippedResult.push_back({vec1[i], vec2[i]});
        }

        return zippedResult;
    }

private:

};

#endif  //__UTILS_H__