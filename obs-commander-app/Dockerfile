FROM node:latest
EXPOSE 4000

COPY . /home/node/project
WORKDIR /home/node/project
RUN npm install
RUN npm run build
CMD ["node", "./dist/bundle.js"]

