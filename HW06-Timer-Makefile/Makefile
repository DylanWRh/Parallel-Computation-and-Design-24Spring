OBJS = Matrix.o\
MatrixReader.o\
StringUtils.o\
Timer.o\
main.o\

CXX=g++

OPTION=-O3

serial: ${OBJS}
	${CXX} ${OPTION} -o main.exe ${OBJS}

.cpp.o:
	${CXX} ${OPTION} -c $< -o $@

clean:
	rm -f *.o *.exe