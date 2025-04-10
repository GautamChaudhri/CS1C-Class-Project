qt-backend guide 

The easiest way to interact with the backend is to do the following:
    1) Install Docker Desktop on your machine. Using this to open the project will automatically
        install all required dependencies and fix any #include errors as well.
        For Windows: https://docs.docker.com/desktop/setup/install/windows-install/ 
        For MacOS: https://docs.docker.com/desktop/setup/install/mac-install/

    2) Open up the project in Microsoft VSCode. 

    3) Search for and install the Dev Containers Extension in VSCode

    4) Click the little lightning bolt icon on the bottom left of VSCode and select
        "Reopen in Container" from the drop down menu. When you do that, it could take up 
        to 3 minutes for the project to open the very first time. When its done, take a look
        at the terminal and if it looks different then the project is now open in docker.

    5) Pull the crow-webservice branch. If you have not yet pulled it on your machine,
        run the following two commands:
        git fetch origin crow-webservice
        git checkout -b crow-webservice origin/crow-webservice 
    
    6) Check the asio and crow subfolders in webservice. If they are empty,
        run the following two commands:
        git clone --recursive https://github.com/crowcpp/crow.git webservice/crow
        git clone --recursive https://github.com/chriskohlhoff/asio.git webservice/asio
    
    7) Open a terminal and do the following to start the webservice:
        cd webservice 
        make
        ./webservice

    8) Open another new terminal and do the following to start the backend and print the 
        results from 2 API requests:
        cd qt-backend
        make
        ./MyApp

    9) If you see two json outputs in the console, everything went successfully
    
    10) Remember to hit Ctrl + C in both terminals when you are done to quit out of both executables.