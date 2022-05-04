FROM ubuntu:latest
COPY ./build/bin/* /app/
CMD ["./app/ChatBot -root ./app -cash ./cash"]