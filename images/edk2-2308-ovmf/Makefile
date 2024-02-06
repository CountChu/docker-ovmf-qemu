BUILDER_HOME = /home/zhugy2/work/2401-OVMF
IMG = edk2-2308-ovmf
RUNER_HOME = /Users/visualge/Dropbox/CodeGit/2401-OVMF

#
# The below targets are run in the builder machine.
#

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
	rm -rf ${BUILDER_HOME}/build/edk2-2308-ovmf

cp-from-docker:
	mkdir -p ${BUILDER_HOME}/build/edk2-2308-ovmf	
	docker cp ${IMG}-run:/work/edk2/Build/OvmfX64/ ${BUILDER_HOME}/build/edk2-2308-ovmf/OvmfX64/

#
# The below targets are run in the runner machine.
#

cp-from-builder:
	mkdir -p ${RUNER_HOME}/build/edk2-2308-ovmf/OvmfX64/DEBUG_GCC5/FV
	scp -r zhugy2@zhugy2--nuc:${BUILDER_HOME}/build/edk2-2308-ovmf/OvmfX64/DEBUG_GCC5/FV/*.fd ${RUNER_HOME}/build/edk2-2308-ovmf/OvmfX64/DEBUG_GCC5/FV/

run-ovmf:
	qemu-system-x86_64 -drive file=${RUNER_HOME}/build/edk2-2308-ovmf/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw -vga std -net none

pre-esp:
	rm -rf esp
	mkdir esp
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/HelloWorld.efi esp/HelloWorld.efi
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/MpTest.efi esp
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/MpTest2.efi esp
	cp ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/MpTest3.efi esp

run-ovmf-app:
	qemu-system-x86_64 \
	-drive file=${RUNER_HOME}/build/edk2-2308-ovmf/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw \
	-vga std \
	-net none \
	-drive file=fat:rw:esp,index=0,format=vvfat

run-ovmf-2-app:
	qemu-system-x86_64 \
	-drive file=${RUNER_HOME}/build/edk2-2308-ovmf/OvmfX64/DEBUG_GCC5/FV/OVMF.fd,if=pflash,format=raw \
	-vga std \
	-net none \
	-drive file=fat:rw:esp,index=0,format=vvfat \
	-smp 2

