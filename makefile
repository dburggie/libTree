# Compilation Settings
CINC = -I ./include
CDEF = -DTREE_DEBUG
CFLAGS = -Wall
COPT = ${CFLAGS} ${CDEF} ${CINC}
CC = gcc ${COPT}



# Targets
DIR = ./build
HDR = ./include/Tree.h
OBJ = ${DIR}/Tree.o
TOBJ = ${DIR}/testTree.o
TEXE = ${DIR}/testTree.x



############### BUILD RULES ###############

all: ${DIR} ${OBJ}



${DIR}:
	mkdir -p ${DIR}



${DIR}/Tree.o: src/Tree.c ${HDR}
	${CC} -c -o $@ $<



clean:
	@echo
	@echo "cleaning build directory"
	rm -rf ${OBJ}
	rm -rf ${TOBJ} ${TEXE}
	@echo



############### TEST SUITE ###############

test: ${DIR} ${TEXE}
	@echo
	@echo "running Tree tests:"
	@echo
	@./${DIR}/testTree.x
	@echo



${DIR}/testTree.x: ${DIR}/testTree.o ${OBJ}
	${CC} -o $@ $^



${DIR}/testTree.o: test/testTree.c test/test.h ${HDR}
	${CC} -c -o $@ $<









