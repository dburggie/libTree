# Compilation Settings
CINC = -I ./include
CDEF = -DTREE_DEBUG
CFLAGS = -Wall
COPT = ${CFLAGS} ${CDEF} ${CINC}
CC = gcc ${COPT}



# Targets
DIR = ./build
HDR = ./include/Tree.h ./include/TreePrivate.h
OBJ1 = ${DIR}/Tree.o ${DIR}/build.o ${DIR}/destroy.o
OBJ2 = ${DIR}/getByIndex.o ${DIR}/splay.o ${DIR}/splice.o
OBJ3 = ${DIR}/splayIndex.o ${DIR}/insertByIndex.o
OBJ4 = ${DIR}/getRoot.o ${DIR}/balance.o ${DIR}/rotate.o
OBJ = ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4}

THDR = ${HDR} ./include/test.h
TST1 = ${DIR}/test.o ${DIR}/init_test.o  ${DIR}/destroy_test.o
TST2 = ${DIR}/splice_test.o ${DIR}/build_test.o
TST3 = ${DIR}/getByIndex_test.o ${DIR}/splay_test.o
TST4 = ${DIR}/splayIndex_test.o ${DIR}/getRoot_test.o
TST5 = ${DIR}/balance_test.o ${DIR}/rotate_test.o
TOBJ = ${TST1} ${TST2} ${TST3} ${TST4} ${TST5}
TEXE = ${DIR}/testTree.x



############### BUILD RULES ###############

all: ${DIR} ${OBJ}

${DIR}:
	mkdir -p ${DIR}

clean:
	@echo
	@echo "cleaning build directory"
	rm -rf ${OBJ}
	rm -rf ${TOBJ} ${TEXE}
	@echo



${DIR}/Tree.o: src/Tree.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/build.o: src/build.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/destroy.o: src/destroy.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/getByIndex.o: src/getByIndex.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/splay.o: src/splay.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/splice.o: src/splice.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/splayIndex.o: src/splayIndex.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/insertByIndex.o: src/insertByIndex.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/getRoot.o: src/getRoot.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/balance.o: src/balance.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/rotate.o: src/rotate.c ${HDR}
	${CC} -c -o $@ $<




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

${DIR}/init_test.o: test/init_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/destroy_test.o: test/destroy_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/splice_test.o: test/splice_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/build_test.o: test/build_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/getByIndex_test.o: test/getByIndex_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/splay_test.o: test/splay_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/splayIndex_test.o: test/splayIndex_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/getRoot_test.o: test/getRoot_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/balance_test.o: test/balance_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/rotate_test.o: test/rotate_test.c ${THDR}
	${CC} -O0 -c -o $@ $<





