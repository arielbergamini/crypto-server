//crow routes, db function calls, & json handling
//
//

#include "crow.h"
#include <stdio.h>
#include <cstdio>

#include "db.h"

int main() {
    crow::SimpleApp app;

    //routes for user registration & authN
    //user registration route
    CROW_ROUTE(app, "/users").methods("POST"_method)([](const crow::request &req) {
        //1 -- parse json
        auto body = crow::json::load(req.body);
        std::string username = body["username"].s();
        std::string password = body["password"].s();
        std::string email = body["email"].s();
        std::string p_hash = body["null"].s(); //temp

        //2 -- generate uuid 
        //3 -- insert into users/ 
        if (!addUser(username, email, p_hash)) {
            return crow::response(500, "failed to register user.");
        }
        //4 -- return password json

        crow::json::wvalue res;
        res["status"] = "success";
        return crow::response{res};
    });
    
    //user authN route
    CROW_ROUTE(app, "/auth_log").methods("POST"_method)([](const crow::request &req) {
        //1 -- lookup user
        auto body = crow::json::load(req.body);
        std::string username = body["username"].s();

        //check if uid matches whats in table based on username
        User user;
        if (!getUser(username, user)) {
            return crow::response(404, "User does not exist");
        }

        //2 -- log ip
        std::string ip = req.remote_ip_address;
        if (!authLogin(user.id, ip)) {
            return crow::response(500, "Failed to authenticate login");
        }

        //3 -- return success json
        crow::json::wvalue res;
        res["status"] = "success";
        return crow::response{res};
    });
    
    return 0;
}