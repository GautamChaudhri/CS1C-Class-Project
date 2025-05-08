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
- Brian Su  (bsu9@ivc.edu)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Development Team  
- Paul Tripodi (ptripod0@saddleback.edu)  
  *Sprint 1 Role:* Product Owner  
  *Sprint 2 Role:* Development Team  
- Placeholder (email)  
  *Sprint 1 Role:* Development Team  
  *Sprint 2 Role:* Development Team 

---

**Description:**

2D Graphics Modeler Inc. is a **C++17 cross‑platform desktop application** that lets users create, view, and manipulate a rich variety of 2D geometric shapes through an intuitive GUI, a robust in‑memory backend logic layer, and a lightweight HTTP webservice for persistence.

The project is organized with a clear separation of concerns:

- **Frontend Logic** – the Qt 6‑based GUI handles all rendering, user input, interactive canvas operations (zoom, pan, drag‑and‑drop), and a live property editor with full undo/redo support.
- **Backend Logic** – an in‑memory management layer that maintains and validates shape, user, and testimonial data, formats data for the frontend, and orchestrates all CRUD operations by communicating with the webservice.
- **Webservice** – a Crow + Asio micro‑framework HTTP server that hydrates the backend on startup by loading JSON files, exposes secure CRUD endpoints for shapes, users, and testimonials, and writes changes back to JSON for durable storage. It can run natively or within Docker.

### Key Features
- **Shape Creation & Editing** – draw and customize Lines, Polylines, Polygons, Rectangles, Squares, Ellipses, Circles, and Text with full control over pen, brush, and text properties.
- **Interactive UI** – a dynamic canvas for manipulation, a tree‑view properties panel, and a sortable shape report table for quick overviews by ID, area, or perimeter.
- **User Account Management** – guest and registered user roles, secure registration and login dialogs, and optional admin privileges for managing data.
- **Testimonial System** – prompt users for feedback, collect testimonials, and provide moderation controls with opt‑out preferences.
- **Persistence & Sync** – backend logic forwards all changes to the Crow webservice, which persists to JSON files and reloads on application launch.
- **JSON Import/Export** – full project snapshots can be saved or loaded as human‑readable JSON for easy sharing and version control.
- **Modular Architecture** – distinct frontend, backend, and webservice modules for maintainability and extensibility.
- **Cross‑Platform Compatibility** – runs seamlessly on macOS, Windows, and Linux.
- **Dockerized Deployment** – the webservice can be launched in a Docker container for consistent, simplified setup.


### Technology Stack

| Layer            | Framework / Library                          | Purpose                                                                                 |
|------------------|----------------------------------------------|-----------------------------------------------------------------------------------------|
| Frontend (UI)    | **Qt 6**                                     | Rendering, user input, interactive canvas operations, live property editor, undo/redo   |
| Backend Logic    | Custom C++ modules                           | In-memory management of shapes, users, and testimonials; data validation and formatting |
| Webservice       | **Crow** + **Asio**                          | HTTP API for persistence; hydrates backend on startup and exposes CRUD JSON endpoints   |
| Storage          | File-based JSON files                        | Durable storage for shapes, users, and testimonials                                     |
| Parser           | Custom hand-rolled JSON parser               | Serialize/deserialize JSON without external libraries                                   |
| Build System     | **CMake**                                    | Cross-platform build configuration and compilation                                      |
| Containerisation | **Docker**, **devcontainers-cli**            | Containerized deployment for the webservice and development environments                |

The project therefore showcases an end‑to‑end **C++17** solution—from GUI to web service to database — suitable both for classroom instruction and as a portfolio‑ready demonstration of modern C++ practices.

---

***Directory Map***

| Item                                    | File Path                                                                   |
|-----------------------------------------|-----------------------------------------------------------------------------|
| 1. Project Source Code                  | `src`                                                                       |
| 2. File References & Line Numbers       | `docs/deliverables.txt`                                                     |
| 3. Extra Credit Submissions             | See entries 11–13 in `docs/deliverables.txt`                                |
| 4. Agile Documentation                  | `docs/agile`                                                                |
| 5. Doxygen Documentation (Web)          | `docs/doxygen/html/index.html`                                              |
| 6. Doxygen Documentation (PDF)          | `docs/doxygen/latex/refman.pdf`                                             |
| 7. Valgrind Memory Leak Check           | `vector-driver`                                                             |
| 8. Whitebox Testing                     | `whitebox-testing`                                                          |
| 9. UML Diagrams                         | `docs/uml`, `docs/doxygen/html/index.html`, `docs/doxygen/latex/refman.pdf` |

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


**Webservice Setup**
To ensure data persistence across executions, the HTTP webservice (built with the Crow framework) must be running before launching the application:
   - **Via Qt**  
    Follow the **Qt Setup** steps above, then build and run the `webservice` target.
   - **Via Docker**  
    Refer to `webservice-dockerized/README.md` for Docker launch instructions.
 

**Development Setup for Backend and Webservice using Dev Containers (not necessary)**
 - This workflow is optional and best suited for working specifically on the backend and webservice components when not needing to interact with the frontend and Qt's IDE.

1. **Install Docker Desktop** (necessary for automatic install of dependencies):
   - **Windows**: <https://docs.docker.com/desktop/setup/install/windows-install/>
   - **macOS**: <https://docs.docker.com/desktop/setup/install/mac-install/>

2. **Open the project in Microsoft VSCode**.

3. **Install the Dev Containers Extension** in VSCode (search for it in the Extensions tab).

4. Click the "lightning bolt" icon in the bottom-left corner of VSCode and select **“Reopen in Container”**.
   - The first time you do this, it may take **up to 3 minutes** as Docker downloads and configures everything.
   - When it’s done, the integrated terminal will look different, indicating you’re now in the container.

5. **To start the webservice from within the dev container for simplicity**:
   ```bash
   cd src/webservice
   make
   ./webservice
   ```
