# Spring 2025 CS1C Class Project – 2D Graphics Modeler Inc.
Section: TTh 1:30-3:50pm  
Due Date: 05/01/2025

---

**Contributors:**
- Kevin Azarbal  (kazarbal1@saddleback.edu)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Development Team  
- Gautam Chaudhri (gchaudhri0@ivc.edu)  
  *Sprint 1 Role:* Scrum Master  
  *Sprint 2 Role:* Development Team  
- Aspen Cristobal  (acristobal1@saddleback.edu)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Development Team  
- Tim Nguyen (tnguyen910@ivc.edu)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Scrum Master  
- Luke Ortiz  (lortiz25@saddleback.edu)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Development Team  
- Eric Sears  (esears5@ivc.edu)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Product Owner  
- Name  (email)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Development Team  
- Paul Tripodi (ptripod0@saddleback.edu)  
  *Sprint 1 Role:* Product Owner  
  *Sprint 2 Role:* Development Team  

---

**Description:**

(Project description here)

---

**Qt Setup**
- Download this project onto your machine.
  ```bash
    git clone --recursive https://github.com/GautamChaudhri/CS1C-Class-Project.git
    ```
- Ensure the `crow` and `asio` subfolders in `src/webservice` contain files.
- If they are empty, clone the dependencies using the following commands:
    ```bash
    cd src/webservice
    git clone --recursive https://github.com/crowcpp/crow.git /crow
    git clone --recursive https://github.com/chriskohlhoff/asio.git /asio
    ```
- Install the appropriate Qt version for your OS (macOS/Windows/Linux).
- Open Qt Creator on your machine.
- From the main menu, choose **File → Open File or Project...**.
- Select the `CMakeLists.txt` file located in the **project root folder**.
  - Qt Creator will prompt you to configure a build kit. Select your preferred Qt kit.
  - The whole project, including the frontend, backend, webservice, and database will appear
    and be modifiable in the Qt IDE. All targets can be built and ran from within the IDE.


**Docker Setup for Backend and Webservice (not necessary)**
 - This workflow is optional and best suited for working specifically on the backend and webservice components when not needing to interact with the frontend and Qt's IDE.

1. **Install Docker Desktop** (necessary for automatic install of dependencies):
   - **Windows**: <https://docs.docker.com/desktop/setup/install/windows-install/>
   - **macOS**: <https://docs.docker.com/desktop/setup/install/mac-install/>

2. **Open the project in Microsoft VSCode**.

3. **Install the Dev Containers Extension** in VSCode (search for it in the Extensions tab).

4. Click the "lightning bolt" icon in the bottom-left corner of VSCode and select **“Reopen in Container”**.
   - The first time you do this, it may take **up to 3 minutes** as Docker downloads and configures everything.
   - When it’s done, the integrated terminal will look different, indicating you’re now in the container.

5. **To start the webservice**:
   ```bash
   cd src/webservice
   make
   ./webservice
   ```

6. **To start the backend and test API requests**:
   ```bash
   cd src/backend
   make
   ./MyApp
   ```
   - You should see two JSON outputs in the console, confirming everything is working.

7. **Stop both executables**:
   - Press `Ctrl + C` in each terminal tab.
