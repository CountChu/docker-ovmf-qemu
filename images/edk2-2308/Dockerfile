FROM ubuntu:20.04 as base

#
# Prepare EDK2
#

WORKDIR /work
COPY build/edk2/ edk2/

#
# Install Python3
#

RUN apt-get update
RUN apt install python3 -y
RUN apt install python3-pip -y
RUN apt install python3-distutils -y

#
# Install prerequisite packages
#

RUN apt install build-essential uuid-dev iasl git gcc -y

#
# Install NASM
#

RUN apt install wget -y
RUN wget https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/linux/nasm-2.15.05-0.fc31.x86_64.rpm -O/tmp/nasm-2.15.05-0.fc31.x86_64.rpm
RUN DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends tzdata
RUN apt-get install -y wget alien
RUN alien /tmp/nasm-2.15.05-0.fc31.x86_64.rpm -i
RUN rm -f /tmp/nasm-2.15.05-0.fc31.x86_64.rpm

#
# Install VIM
#

RUN apt install vim -y

#
# Build EDK2 tool chain
#

RUN ln -s /usr/bin/python3 /usr/bin/python 
WORKDIR /work/edk2
RUN make -C BaseTools





