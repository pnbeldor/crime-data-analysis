#ifndef MOCK_ABSTRACT_DATA_FETCHER
#define MOCK_ABSTRACT_DATA_FETCHER

#include <gmock/gmock.h>

#include "AbstractDataFetcher.h"

class MockAbstractDataFetcher : public AbstractDataFetcher
{
public:
    MOCK_METHOD(std::string, LoadData, (), overrride);

};

#endif //MOCK_ABSTRACT_DATA_FETCHER