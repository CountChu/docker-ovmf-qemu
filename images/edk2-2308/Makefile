BUILDER_HOME = ~/work/2401-OVMF
IMG = edk2-2308

#
# The below targets are run in the builder machine.
#

pre:
	mkdir -p build
	cp -r ${BUILDER_HOME}/external/edk2/ build/edk2/

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
