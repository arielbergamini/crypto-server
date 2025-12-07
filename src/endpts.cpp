#include "crow.h"
#include <stdio.h>
#include <cstdio>


int main() {
    crow::SimpleApp app;

    //crow routes for user registration & authN
    //register route
    CROW_ROUTE(app, "/users").methods("POST"_method)([](const crow::request &req) {
        //parse json - generate uuid - argon2 - insert into users/ - return password
        crow::json::wvalue err;
        err["error"] = "failed to regoster user.";
    });
    
    //authN route
    CROW_ROUTE(app, "/auth_log").methods("POST"_method)([](const crow::request &req) {
        //lookup user - log ip - return success json
        crow::json::wvalue err;
        err["error"] = "failed to authenticate user.";
    });
    
    return 0;
}