BUILDER_HOME = ~/work/2401-OVMF
IMG = edk2-2308-app
RUNER_HOME = /Users/visualge/Dropbox/CodeGit/2401-OVMF

#
# The below targets are run in the builder machine.
#

pre:
	mkdir -p build
	cp -r ${BUILDER_HOME}/patch/edk2-2308-app/ build/edk2/

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
	rm -rf ${BUILDER_HOME}/build/edk2-2308-app/MdeModule

cp-from-docker:
	mkdir -p ${BUILDER_HOME}/build/edk2-2308-app		
	docker cp ${IMG}-run:/work/edk2/Build/MdeModule/ ${BUILDER_HOME}/build/edk2-2308-app/MdeModule/

#
# The below targets are run in the runner machine.
#

cp-from-builder:
	mkdir -p ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64
	scp -r zhugy2@zhugy2--nuc:${BUILDER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/*.efi ${RUNER_HOME}/build/edk2-2308-app/MdeModule/DEBUG_GCC5/X64/
