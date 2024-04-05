OBJS = Matrix.o\
MatrixReader.o\
StringUtils.o\
Timer.o\
main.o\

CXX=g++
LDFLAGS=-lblas
OPTION=-O3

serial: ${OBJS}
	${CXX} ${OPTION} -o main.exe ${OBJS} $(LDFLAGS)
	python make_test.py

.cpp.o:
	${CXX} ${OPTION} -c $< -o $@


clean:
	rm -f *.o *.exe
	rm -rf test