# Crow Webservice Docker Deployment Guide

> **Note:** If you are still developing the project, running the `webservice` target directly inside Qt is easier and might be more preferable. This Docker setup will be used when the Qt app is complete to run the webservice so it is completely isolated from the app, but it is still a good way to get started with Docker if you want to right now.

## Prerequisite

You need to have Docker Desktop installed on your machine:
- For Windows: https://docs.docker.com/desktop/setup/install/windows-install/ 
- For MacOS:   https://docs.docker.com/desktop/setup/install/mac-install/

## Option 1 (Quickest): Pull the prebuilt container
- Open the terminal anywhere on your machine
- Pull the container
  ```bash
  docker pull ghcr.io/gautamchaudhri/crow-webservice:latest
  ```
- Start the container:
  ```bash
  docker run -p 8080:8080 --name crow-webservice -it ghcr.io/gautamchaudhri/crow-webservice:latest
  ```
- Stop the container:
  In the terminal running the container, press `Ctrl + C`

- Restart the container:
  ```bash
  docker start -ai crow-webservice
  ```
- If you want to delete the container:
  ```bash
  docker rm crow-webservice
  ```

## Option 2: Build the container yourself using the existing Dockerfile
- Open the project in your IDE or text editor.
- Open the terminal
  ```bash
  cd webservice-dockerized
  ```
- Build the container
  ```bash
  docker build -t crow-webservice .
  ```
- Start the container for the first time
  ```bash
  docker run -p 8080:8080 --name crow-webservice -it crow-webservice
  ```
- Stop the container 
  In the terminal running the container, press `Ctrl + C`

- Restart the container after it has already been ran once. This command can be used anywhere in the terminal after it has already ran once using the previous docker run command.
  ```bash
  docker start -ai crow-webservice 
  ```


## Optional: Clean Up Docker Images and Containers

If something goes wrong or you want to start fresh:

- Remove the container:
  ```bash
  docker rm crow-webservice
  ```

- Remove the image:
  ```bash
  docker rmi crow-webservice
  ```

- List all containers:
  ```bash
  docker ps -a
  ```

- List all images:
  ```bash
  docker images
  ```

## FAQ and Troubleshooting

**Q: I get a permissions error on Mac/Windows. What do I do?**  
A: Make sure Docker Desktop is running. You can check its status with:
```bash
docker info
```
If it returns an error or hangs, Docker Desktop is likely not running. Start it manually from your applications menu.

**Q: It says "image not found."**  
A: Make sure you pulled the image with:
```bash
docker pull ghcr.io/gautamchaudhri/crow-webservice:latest
```

**Q: How do I stop the container?**  
A: In the terminal running the container, press `Ctrl + C`.  
To confirm it has stopped:
```bash
docker ps -a
```
Look for `crow-webservice` and check the "STATUS" column.
