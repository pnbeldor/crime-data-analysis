/* --- RequestHandler.cpp --- */

/* ------------------------------------------
author: Pnbeldor
date: 9/24/2025
------------------------------------------ */

#include "RequestHandler.h"

#include <iostream>

// Callback function for libcurl
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

RequestHandler::RequestHandler() {
    this->m_handle = curl_easy_init();
    curl_easy_setopt(this->m_handle, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(this->m_handle, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(this->m_handle, CURLOPT_FOLLOWLOCATION, 1L);
}

RequestHandler::~RequestHandler() {
    curl_easy_cleanup(this->m_handle);
    this->m_handle = NULL;
}

std::string RequestHandler::execute_request(std::string url)
{
    CURLcode res_code;
    curl_easy_setopt(this->m_handle, CURLOPT_URL, url.c_str());
    std::unique_ptr<std::string> httpData(new std::string());
    curl_easy_setopt(this->m_handle, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(this->m_handle, CURLOPT_WRITEDATA, httpData.get());
    
    res_code = curl_easy_perform(this->m_handle);

    long http_code = 0;
    curl_easy_getinfo(this->m_handle, CURLINFO_RESPONSE_CODE, &http_code);

    if (res_code != CURLE_OK || http_code != 200)
    {
        std::cout << "Curl request failed: " << std::string(curl_easy_strerror(res_code)) << "\n";
        std::cout << "http code is: " << http_code << "\n";
        std::cout << "Invalid request: " << url << std::endl;
        std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
    }

    return *httpData.get();
}
