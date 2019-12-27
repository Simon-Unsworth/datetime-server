FROM gcc:latest

LABEL maintainer="Simon Unsworth simonunsworth@outlook.ie"

EXPOSE 5555

COPY ./src /usr/src/datetime-server

WORKDIR /usr/src/datetime-server

RUN gcc -o server main.c -lpthread

ENTRYPOINT [ "./server" ]