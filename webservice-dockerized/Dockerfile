FROM fedora:latest
LABEL org.opencontainers.image.source="https://github.com/GautamChaudhri/CS1C-Class-Project"

#install dependencies
RUN sudo dnf install -y git make g++ nano && sudo dnf update -y && dnf clean all

#copy over webservice.cpp and Makefile along with local copies of crow and asio
WORKDIR /webservice
COPY . /webservice

#create database directory and empty JSON files
RUN mkdir -p /webservice/database \
    && touch /webservice/database/shapes.json \
    && touch /webservice/database/render_area.json \
    && touch /webservice/database/users.json \
    && touch /webservice/database/testimonials.json

#install more dependencies
RUN mkdir /webservice/crow \
   && git clone --recursive https://github.com/crowcpp/crow.git /webservice/crow
RUN mkdir /webservice/asio \
   && git clone --recursive https://github.com/chriskohlhoff/asio.git /webservice/asio

#expose the necessary port and start the binary
EXPOSE 8080

RUN make
CMD ["./webservice"]
