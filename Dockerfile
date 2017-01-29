# install git for cloning the repo, python and build-essential 
# for compiling node-serialport on the BeagleBone
RUN apt-get update && apt-get install git python build-essential

# Defines our working directory in container
WORKDIR /usr/src/app

# clone the node-bus-pirate repo and install its dependencies via npm
RUN git clone https://github.com/nodebotanist/node-bus-pirate.git ./
RUN JOBS=MAX npm install --production --dev --unsafe-perm && npm cache clean && rm -rf /tmp/*

# next we install the modules needed for our testing server
RUN JOBS=MAX npm install express simple-git && npm cache clean && rm -rf /tmp/*

# Enable systemd init system in container
ENV INITSYSTEM on

# These commands enable us to use our USB serial ports
RUN udevd --daemon && udevadm trigger

# Copy our working directory files over to the container
COPY . ./

# server.js will run when container starts up on the device
CMD ["node", "server.js"]