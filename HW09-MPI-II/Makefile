OBJS = main.o\
Matrix.o

# CXX=g++
CXX=mpicxx
# OPTION=-O3
OPTION=-O3 -D__MPI

serial: ${OBJS}
	${CXX} ${OPTION} -o main.exe ${OBJS} 
	python make_test.py

.cpp.o:
	${CXX} ${OPTION} -c $< -o $@


clean:
	rm -f *.o *.exe
	rm -rf test test_complex
	rm -rf output