#ifndef MOCK_DATA_FETCHER
#define MOCK_DATA_FETCHER

#include <gmock/gmock>
#include <string>

class MockDataFetcher : public IDataFetcher
{
public:
    MOCK_METHOD(std::string fetchData, (const std::string& source), (override));
    MOCK_METHOD(bool canHandle, (const std::string& source), (const, override));
};

#endif  //MOCK_DATA_FETCHER
