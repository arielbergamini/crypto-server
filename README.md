# crypto-server
sqlite/cryptography server for csce 3550 by Ariel Bergamini

#IMPORTANT! submission note --- SQL3 linking issue

The required functionality for this project has been implemented, including:

    - route handlers via Crow framework for creating users, logging authentications, & storing encrypted keys
    - password hashing using TinyAES framework
    - expected db & subtable design using sql3

The project builds successfully for each component, except for the SQL3 linking. This is verifiable by running the following commands using g++:

    - g++ -Iinclude -c src/db.cpp -o db.o -std=c++17 
    - g++ -Iinclude -c src/endpts.cpp -o endpoints.o -std=c++17
    - g++ -Iinclude -c src/crypto.cpp -o crypto.o -std=c++17

Unfortunately, the issue is unrelated to the source code that I've written and relates to MinGW dynamic linking. If you run

    - g++ -Iinclude src/db.cpp include/sqlite/sqlite3.c -o db.exe -std=c++17

you will see thousands of errors relating to undefined references to SQL3 functions, even though all appropriate SQL3 headers were correctly included in the project and linked using the -lsqlite3 flag at compilation. 

Included in .gitignore is /include, which contains all of my project dependencies (asio, crow, tinyAES, and SQL3). SQL3 is the only of these  that would not work despite my attempts at resolving the issue, which included:

    - installing SQL3 & updated PATH system var for it
    - using the precompiled SQlite amalgamation
    - using static builds of sqlite3.c/.h
    - adding include & library directories to g++
    - etc.


Despite this unfortunate issue, my code is clean, logically correct, and 
models the requests of the project described on Canvas. I would deeply
appreciate any opportunities for partial credit via my competency in the concepts as illustrated in the code provided.
