# Whitebox Testing Driver

This directory contains the whitebox testing harness for the 2D Graphics Modeler project. It leverages the Team-Alphawolves development container to ensure a consistent build environment.

## Prerequisites

Before running the tests, ensure you have the Team-Alphawolves dev container configured:
(The following copy and pasted from the README of the final group project)

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


## Setup & Usage

1. **Build and Run Tests**  
   ```bash
   make
   ./hwgp02
   ```

## Notes

- The provided `Makefile` includes Qt paths that are specific to the dev container environment.  
- If you prefer to build outside the container, adjust the Qt include and library paths in the `Makefile` to match your local setup.

---