FROM edk2-2308 as base

#
# Patch files.
#

COPY build/edk2/ /work/edk2/

#
# Build EmulatorPkg
#

WORKDIR /work/edk2
RUN . ./edksetup.sh \
	&& build -p MdeModulePkg/MdeModulePkg.dsc -t GCC5 -a X64
WORKDIR /work/edk2/Build/MdeModule/DEBUG_GCC5/X64

#RUN ./Host
