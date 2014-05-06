# Compilation Settings
CINC = -I ./include
CDEF = -DTREE_DEBUG
CFLAGS = -Wall
COPT = ${CFLAGS} ${CDEF} ${CINC}
CC = gcc ${COPT}



# Targets
DIR = ./build
HDR = ./include/Tree.h ./include/TreePrivate.h
OBJ1 = ${DIR}/Tree.o ${DIR}/tree_build.o ${DIR}/tree_destroy.o
OBJ2 = ${DIR}/tree_getByIndex.o ${DIR}/tree_splay.o ${DIR}/tree_splice.o
OBJ3 = ${DIR}/tree_splayIndex.o ${DIR}/tree_insertByIndex.o
OBJ4 = ${DIR}/tree_getRoot.o ${DIR}/tree_balance.o
OBJ = ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4}

THDR = ${HDR} ./include/test.h
TST1 = ${DIR}/test.o ${DIR}/tree_init_test.o  ${DIR}/tree_destroy_test.o
TST2 = ${DIR}/tree_splice_test.o ${DIR}/tree_build_test.o
TST3 = ${DIR}/tree_getByIndex_test.o ${DIR}/tree_splay_test.o
TST4 = ${DIR}/tree_splayIndex_test.o ${DIR}/tree_getRoot_test.o
TOBJ = ${TST1} ${TST2} ${TST3} ${TST4}
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

${DIR}/tree_build.o: src/tree_build.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_destroy.o: src/tree_destroy.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_getByIndex.o: src/tree_getByIndex.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_splay.o: src/tree_splay.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_splice.o: src/tree_splice.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_splayIndex.o: src/tree_splayIndex.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_insertByIndex.o: src/tree_insertByIndex.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_getRoot.o: src/tree_getRoot.c ${HDR}
	${CC} -c -o $@ $<

${DIR}/tree_balance.o: src/tree_balance.c ${HDR}
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

${DIR}/tree_init_test.o: test/tree_init_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_destroy_test.o: test/tree_destroy_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_splice_test.o: test/tree_splice_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_build_test.o: test/tree_build_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_getByIndex_test.o: test/tree_getByIndex_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_splay_test.o: test/tree_splay_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_splayIndex_test.o: test/tree_splayIndex_test.c ${THDR}
	${CC} -O0 -c -o $@ $<

${DIR}/tree_getRoot_test.o: test/tree_getRoot_test.c ${THDR}
	${CC} -O0 -c -o $@ $<




