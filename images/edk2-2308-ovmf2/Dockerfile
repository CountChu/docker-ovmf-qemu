FROM edk2-2308 as base

#
# Install QEMU 
#

#RUN apt install qemu -y
#RUN apt install qemu-kvm -y
#RUN apt install libvirt-daemon-system -y 
#RUN apt install libvirt-clients -y
#RUN apt install virt-manager -y

#
# Patch files.
#

COPY build/edk2/ /work/edk2/

#
# Build OvmfPkg
#

WORKDIR /work/edk2
RUN . ./edksetup.sh \
	&& build -p OvmfPkg/OvmfPkgX64.dsc -t GCC5 -a X64
WORKDIR /work/edk2/Build/OvmfX64/DEBUG_GCC5/FV
