#include "router.h"
#include <iostream>
namespace Vilin {

Router::Router()
{}
Router::~Router()
{}

Route::RoutePtr Router::NewRoute()
{   
    auto r = std::make_shared<Route>();
    routes_.push_back(r);

    return r;
}

Route::Handler Router::Match(const HttpRequest& request, std::unordered_map<std::string, std::string>* match_map)
{
    for (auto &r : routes_)
    {
        if (r->Match(request, match_map))
        {
            return r->GetHandler();
        }
    }
    std::cout << "mismatch" << std::endl;
    return nullptr;
}

}