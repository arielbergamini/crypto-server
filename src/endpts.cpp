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

        if (!body) {
            return crow::response(400, "invalid json");
        }
        if (!body.has("username") || !body.has("password") || !body.has("email")) {
            return crow::response(400, "missing required fields");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();
        std::string email = body["email"].s();

        //2 -- generate hashed password
        std::string hash = "hashed: " + password; //FIXME

        //3 -- insert into users/ 
        if (!addUser(username, email, hash)) {
            return crow::response(500, "failed to register user.");
        }

        //4 -- return password
        crow::json::wvalue res;
        res["status"] = "success";
        res["password"] = "password";
    });
    
    //user authN route
    CROW_ROUTE(app, "/auth_log").methods("POST"_method)([](const crow::request &req) {
        //1 -- lookup user
        auto body = crow::json::load(req.body);
        if (!body || !body.has("username")) {
            return crow::response(400, "missing username");
        }

        std::string username = body["username"].s();

        //check if uid matches via user lookup
        User user;
        if (!getUser(username, user)) {
            return crow::response(404, "user does not exist");
        }

        //2 -- log ip
        std::string ip = req.remote_ip_address;
        if (!authLogin(user.id, ip)) {
            return crow::response(500, "failed to log authN request");
        }

        //3 -- return success json
        crow::json::wvalue res;
        res["status"] = "success";
        return crow::response{res};
    });

    //run the server
    app.port(18080).multithreaded().run();
    
    return 0;
}