FROM gradle:latest
EXPOSE 9000

COPY . /home/gradle/project
WORKDIR /home/gradle/project
CMD ["gradle", "run"]
