APP=linked_list_testcase
GTEST_DIR=${HOME}/Study/EmbedProg/googleTest/googletest/googletest/

FILES = linked_list.c
OBJ_FILES = $(patsubst %.c, %.o, $(FILES))
HEADER = linked_list.h
COPTS=-fprofile-arcs -ftest-coverage
COV_OUTPUT=./cov_output

${APP}: Gtest_main.o ${APP}.o libgtest.a $(OBJ_FILES)
	g++ -isystem ${GTEST_DIR}/include -pthread -o ${APP} Gtest_main.o ${APP}.o $(OBJ_FILES) libgtest.a --coverage
	
Gtest_main.o:Gtest_main.c 
	g++ -isystem ${GTEST_DIR}/include -pthread -c Gtest_main.c 

${APP}.o:  ${APP}.c 
	g++ -isystem ${GTEST_DIR}/include -pthread -c ${APP}.c

$(OBJ_FILES): $(FILES) $(HEADER)
	g++ --coverage -c -o $@ $<

libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

release:
	rm -f *.o *.a $(APP)

test:	$(APP).c
	./$(APP)

report:
	lcov -rc lcov_branch_coverage=1 -c -i -d . -o .coverage.base
	lcov -rc lcov_branch_coverage=1 -c -d . -o .coverage.run
	lcov -rc lcov_branch_coverage=1 -d . -a .coverage.base -a .coverage.run -o .coverage.total
	genhtml --branch-coverage -o ${COV_OUTPUT} .coverage.total
	rm -f .coverage.base .coverage.run .coverage.tota