# Compilation Settings
CINC = -I ./include
CDEF = -DSPLAYTREE_DEBUG
CFLAGS = -Wall
COPT = ${CFLAGS} ${CDEF} ${CINC}
CC = gcc ${COPT}



# Targets
DIR = ./build
HDR = ./include/SplayTree.h
OBJ = ${DIR}/SplayTree.o
TOBJ = ${DIR}/testSplayTree.o
TEXE = ${DIR}/testSplayTree.x



############### BUILD RULES ###############

all: ${DIR} ${OBJ}



${DIR}:
	mkdir -p ${DIR}



${DIR}/SplayTree.o: src/SplayTree.c ${HDR}
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
	@echo "running SplayTree tests:"
	@echo
	@./${DIR}/testSplayTree.x
	@echo



${DIR}/testSplayTree.x: ${DIR}/testSplayTree.o ${OBJ}
	${CC} -o $@ $^



${DIR}/testSplayTree.o: test/testSplayTree.c test/test.h ${HDR}
	${CC} -c -o $@ $<









