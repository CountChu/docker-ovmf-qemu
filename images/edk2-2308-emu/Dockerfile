FROM edk2-2308 as base

#
# Install required packages for EmulatorPkg
#

RUN apt install libx11-dev -y
RUN apt install libxext-dev -y

#
# Build EmulatorPkg
#

WORKDIR /work/edk2
RUN . ./edksetup.sh \
	&& build -p EmulatorPkg/EmulatorPkg.dsc -t GCC5 -a X64
WORKDIR /work/edk2/Build/EmulatorX64/DEBUG_GCC5/X64
#RUN ./Host
