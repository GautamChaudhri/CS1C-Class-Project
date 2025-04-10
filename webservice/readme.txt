Crow Guide

Check to see if asio and crow subfolders are empty (they probably are on the first pull)

If empty, run these two commands
    git clone --recursive https://github.com/crowcpp/crow.git webservice/crow
    git clone --recursive https://github.com/chriskohlhoff/asio.git webservice/asio

They should now be populated with files

Next, run make and run the generated executable ./crow_service

Go to the following link in your web browser to ensure there is a message saying "Hello, Crow!"
    localhost:8080/



If there is an error under #include <crow.h> and/or <crow/json.h>, that is only from intellisense
because VS code doesn't know where those files are. Make should still work and the binary should still
execute. You can tell intellisense where the files are by doing the following:
    1) Open command palette in vs code
    2) Search and select Edit Configurations (UI)
    3) Add the following two lines  in your include path
        webservice/crow/include/
        webservice/asio/asio/include/

This is not absolutely necessary but works if you don't wanna see the error


//Cheat sheet
crow::json::wvalue::list() list     *creates a json array
list.add(item)                      *adds an item to the json array
list.dump()                         *converts json array into string
crow::json::load(string)            *parses string data and outputs data into json
