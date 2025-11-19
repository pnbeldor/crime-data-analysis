/* --- URLDataLaoader.cpp --- */

/* ------------------------------------------
author: Pnbeldor
date: 9/24/2025
------------------------------------------ */

#include "URLDataLoader.h"

#include <iostream>

URLDataLoader::URLDataLoader()
{
    // Constructor
}

URLDataLoader::~URLDataLoader()
{
    // Destructor
}

std::string URLDataLoader::FetchData()
{
    return "URL Data fetched";
}

bool URLDataLoader::canHandle(const std::string& source) const
{
    if (source.empty())
        return false;

    return true;
}
