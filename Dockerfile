# stage 1: build project
FROM ubuntu:latest as build
WORKDIR /

# install packages
COPY install_requirements.sh .
RUN ./install_requirements.sh

# copy project and build script
COPY build.sh build.sh
COPY server.cpp server.cpp
COPY /tests ./tests
COPY CMakeLists.txt CMakeLists.txt
COPY main.cpp main.cpp
COPY /include ./include
COPY /src ./src/

# build project
RUN ./build.sh --test
RUN ./build.sh

# stage 2: run project
FROM ubuntu:latest
WORKDIR /

# copy executables and libraries
COPY --from=build /bin ./bin/
COPY --from=build /lib ./lib/

# entrypoint
CMD ["./bin/server.out"]
CMD ["./bin/exe.out"]