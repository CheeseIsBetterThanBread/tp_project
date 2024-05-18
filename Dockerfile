# stage 1: build project
FROM ubuntu:latest as build
WORKDIR /

# install packages
COPY scripts/install_requirements.sh .
RUN ./install_requirements.sh

# copy project and scripts
COPY scripts/build.sh build.sh
COPY scripts/run.sh run.sh
COPY server.cpp server.cpp
COPY /tests ./tests
COPY CMakeLists.txt CMakeLists.txt
COPY main.cpp main.cpp
COPY /include ./include
COPY /src ./src/

# build project
RUN ./build.sh

# stage 2: run project
FROM ubuntu:latest
WORKDIR /

# copy executables, libraries and run script
COPY --from=build run.sh run.sh
COPY --from=build /logging ./logging/
COPY --from=build /bin ./bin/
COPY --from=build /lib ./lib/

# entrypoint
CMD ["./run.sh"]