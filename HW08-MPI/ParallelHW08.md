# 并行程序设计 Homework 8

使用
```bash
make clean ; make ; mpirun --allow-run-as-root -np 4 ./main.exe [--print_mpi_log]
```
运行程序，若指定`--print_mpi_log`，将每个节点的日志输出到不同文件中
