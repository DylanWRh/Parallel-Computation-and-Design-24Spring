# 并行程序设计 Homework 7

使用
```bash
make clean ; make ; ./main.exe
```
运行程序

`make`将运行以下步骤
- 执行`make_test.py`生成测试例子，为在`./test`目录下的若干`*.in`文件
- 编译C++代码并链接矩阵运算库，生成可执行文件`main.exe`

`main.exe`包含以下步骤
- 运行三重`for`循环写的矩阵乘法
- 运行调用BLAS进行的矩阵乘法
- 运行调用LAPACKE进行的特征值分解
- 输出结果到`./test/*.out`中
- 统计时间并打印

运行环境为Bohrium上的2核机器，用时如下
```
CLASS NAME                                FUNCTION     CALLS         TIME (s)
    LAPACK                     Eigval, (1000,1000)         1    2.7079999e+00
    LAPACK                           Eigval, (3,3)         1    0.0000000e+00
    LAPACK                       Eigval, (100,100)         1    3.0000000e-03
      BLAS       MatMul, (1000,1000) * (1000,1000)         1    8.3700001e-01
      BLAS           MatMul, (100,100) * (100,100)         1    1.0000000e-03
      BLAS                   MatMul, (3,3) * (3,3)         1    0.0000000e+00
    Matrix       MatMul, (1000,1000) * (1000,1000)         1    8.0139999e+00
    Matrix           MatMul, (100,100) * (100,100)         1    4.9999999e-03
    Matrix                   MatMul, (3,3) * (3,3)         1    0.0000000e+00
```
