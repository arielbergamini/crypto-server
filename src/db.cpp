//sqlite db
#include <stdio.h>
#include <iostream>
#include <string>

#include "db.h"
#include "sqlite3.h"

using namespace std;

//add user to appropriate table
bool addUser(const string &username, const string &email, const string &hash) {
    sqlite3* db;
    sqlite3_open("airs.db", &db);

    const char* sql =
        "INSERT INTO usrs (username, hash, email) "
        "VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) { //error handling
        std::cerr << "prepare failed\n";
        sqlite3_close(db);
        return false;
    }

    //bind entered text to table cell
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (rc == SQLITE_DONE) {return true;}
    return false;
};

//get user from table, used to verify if user exists
bool getUser(const string &username) {
    sqlite3* db;
    sqlite3_open("airs.db", &db);

    const char* sql =
        "SELECT id FROM users WHERE username = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    bool found = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return found;
};

//log auth attempts
bool authLogin(int userId, const string &ipAddr) {
    sqlite3* db;
    sqlite3_open("airs.db", &db);

    const char* sql =
        "INSERT INTO auth_logs (request_ip, user_id) VALUES (?, ?);";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, ipAddr.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, userId);

    int rc = sqlite3_step(stmt);
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return rc == SQLITE_DONE;
};


int main (int argc, char* argv[]) {

    sqlite3 * db;

    //users
    std::string sql =  
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash TEXT NOT NULL,"
        "email TEXT UNIQUE,"
        "date_registered TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "last_login TIMESTAMP"
        ");";

    //keys
    std::string sql2 =
        "CREATE TABLE IF NOT EXISTS keys ("
        "kid INTEGER PRIMARY KEY AUTOINCREMENT,"
        "key BLOB NOT NULL,"
        "exp INTEGER NOT NULL"
        ");";

    //auth logs
    std::string sql3 =
        "CREATE TABLE IF NOT EXISTS auth_logs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "request_ip TEXT NOT NULL,"
        "request_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "user_id INTEGER,"
        "FOREIGN KEY(user_id) REFERENCES users(id)"
        ");";

        
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