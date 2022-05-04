FROM ubuntu:latest
COPY ./build/Release/ /app/
CMD ["./app/ChatBot", "-root" , "./app", "-cash","./cash"]