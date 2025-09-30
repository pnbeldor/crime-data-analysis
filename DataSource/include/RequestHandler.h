/* --- RequestHandler.h --- */

/* ------------------------------------------
Author: Pierre Nicolson Beldor
Date: 9/24/2025
------------------------------------------ */

#ifndef DATA_SOURCE_REQUEST_HANDLER_H
#define DATA_SOURCE_REQUEST_HANDLER_H

#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <string>

class RequestHandler {
public:
    RequestHandler();
    virtual ~RequestHandler();

    std::string execute_request(const std::string url);

    private:
        CURL * m_handle;

};

#endif // DATA_SOURCE_REQUEST_HANDLER_H
