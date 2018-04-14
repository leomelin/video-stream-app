FROM gradle:latest
EXPOSE 9000

USER root
COPY . /home/gradle/project
WORKDIR /home/gradle/project
CMD ["gradle", "run"]
