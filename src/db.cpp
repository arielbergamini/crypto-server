//sqlite db
#include <stdio.h>
#include <iostream>
#include <string>

#include "sqlite3.h"

using namespace std;

int main (int argc, char* argv[]) {

    sqlite3 * db;
    //user table
    std::string sql =  "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE, "
        "password_hash TEXT NOT NULL,"
        "email TEXT UNIQUE,"
        "date_registered TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        "last_login TIMESTAMP);";

    //auth logs table
    std::string sql2 = "CREATE TABLE IF NOT EXISTS auth_logs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "request_ip TEXT NOT NULL, "
        "request_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "user_id INTEGER,"
        "FOREIGN KEY(user_id) REFERENCES users(id);";
        
    int exit = 0;
    exit = sqlite3_open("airs.db", &db);
    char* msgErr;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &msgErr);

    if (exit != SQLITE_OK) {
        std::cerr << "Error creating table user, auth_logs" << std::endl;
        sqlite3_free(msgErr);
    } else {
        std::cout << "Table users, auth_logs created successfully" << std::endl;
        sqlite3_close(db);
    }

    return 0;
}