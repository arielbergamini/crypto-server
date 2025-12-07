
#ifndef DB_H
#define DB_H
#include <iostream>

//user type for db insertion
struct User {
    int id;
    std::string email, username, p_hash;
};

//initialize database
bool initDb(const std::string &dbName);

//add user to db
bool addUser(const std::string &username, const std::string &email, const std::string &hash);

//get user by username
bool getUser(const std::string &username, User &user); 

bool authLogin(int userId, const std::string &ipAddr);

#endif