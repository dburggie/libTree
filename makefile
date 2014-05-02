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

THDR = ${HDR} ./include/test.h
TST1 = ${DIR}/test.o ${DIR}/tree_init_test.o  ${DIR}/tree_destroy_test.o
TST2 = ${DIR}/tree_splice_test.o ${DIR}/tree_build_test.o
TOBJ = ${TST1} ${TST2}
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



${DIR}/testTree.x: ${TOBJ} ${OBJ}
	${CC} -O0 -o $@ $^



${DIR}/test.o: test/test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_init_test.o: test/tree_init_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_destroy_test.o: test/tree_destroy_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_splice_test.o: test/tree_splice_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_build_test.o: test/tree_build_test.c ${THDR}
	${CC} -O0 -c -o $@ $<




