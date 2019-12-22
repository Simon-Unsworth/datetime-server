FROM gcc:latest

COPY ./src /usr/src/datetime-server

WORKDIR /usr/src/datetime-server

RUN gcc -o server main.c

CMD ["./server"]