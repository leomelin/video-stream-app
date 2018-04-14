FROM python:3
EXPOSE 5000

RUN apt-get update -qq && apt-get upgrade -y -qq
COPY . /yt-integration

WORKDIR /yt-integration
RUN pip install -r requirements.txt

CMD python run.py
