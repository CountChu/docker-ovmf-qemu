BUILDER_HOME = /home/zhugy2/work/2401-OVMF
IMG = edk2-2308-ovmf2
RUNER_HOME = /Users/visualge/Dropbox/CodeGit/2401-OVMF

#
# The below targets are run in the builder machine.
#

pre:
	mkdir -p build
	cp -r ${BUILDER_HOME}/patch/edk2-2308-ovmf2/ build/edk2/

d-build: 
	docker build -t ${IMG} .

d-run-d:
	docker run -it -d --name ${IMG}-run ${IMG} 	

d-exec:
	docker exec -it ${IMG}-run bash

d-rm:
	docker stop ${IMG}-run
	docker rm ${IMG}-run

clean:
	rm -rf build
	rm -rf ${BUILDER_HOME}/build/edk2-2308-ovmf2	

cp-from-docker:
	mkdir -p ${BUILDER_HOME}/build/edk2-2308-ovmf2
	docker cp ${IMG}-run:/work/edk2/Build/OvmfX64/ ${BUILDER_HOME}/build/edk2-2308-ovmf2/OvmfX64/

#
# The below targets are run in the runner machine.
#

cp-from-builder:
	mkdir -p ${RUNER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV
	scp -r zhugy2@zhugy2--nuc:${BUILDER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV/*.fd ${RUNER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV/

pre-esp:
	rm -rf esp
	mkdir esp
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/HelloWorld.efi esp/HelloWorld.efi
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/MpTest.efi esp
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/MpTest2.efi esp
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/MpTest3.efi esp

run-ovmf-d:
	qemu-system-x86_64 \
	-drive file=${RUNER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw \
	-vga std \
	-net none \
	-debugcon file:debug.log \
	-global isa-debugcon.iobase=0x402

run-ovmf-2-d:
	qemu-system-x86_64 \
	-drive file=${RUNER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw \
	-vga std \
	-net none \
	-smp 2 \
	-debugcon file:debug.log \
	-global isa-debugcon.iobase=0x402	

run-ovmf-255-d:
	qemu-system-x86_64 \
	-drive file=${RUNER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw \
	-vga std \
	-net none \
	-smp 255 \
	-debugcon file:debug.log \
	-global isa-debugcon.iobase=0x402	

run-ovmf-256-d:
	qemu-system-x86_64 \
	-drive file=${RUNER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw \
	-vga std \
	-net none \
	-smp 256 \
	-debugcon file:debug.log \
	-global isa-debugcon.iobase=0x402		

run-ovmf-app:
	qemu-system-x86_64 \
	-drive file=${RUNER_HOME}/build/edk2-2308-ovmf2/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw \
	-vga std \
	-net none \
	-drive file=fat:rw:esp,index=0,format=vvfat
