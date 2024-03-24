# 并行程序设计 Homework3


## 作业一

### 任务1

用`du`的`-h`显示便于阅读的格式，并用`-d`指定最大深度，得到的结果通过管道利用`sort`进行从大到小的排序，指令为
```bash
du -h -d 1 ./abacus-develop | sort -rh
```

输出为
```
297M    ./abacus-develop
131M    ./abacus-develop/.git
77M     ./abacus-develop/source
66M     ./abacus-develop/tests
14M     ./abacus-develop/examples
11M     ./abacus-develop/tools
660K    ./abacus-develop/docs
356K    ./abacus-develop/toolchain
136K    ./abacus-develop/python
92K     ./abacus-develop/.github
36K     ./abacus-develop/cmake
16K     ./abacus-develop/deps
12K     ./abacus-develop/conda
8.0K    ./abacus-develop/.devcontainer
```
因此最大的文件夹是`.git`

### 任务2

使用`find`的`-name`指定`.cpp`文件进行搜索，并使用`wc -l`统计输出行数，命令为
```bash
find ./abacus-develop -name "*.cpp" | wc -l
```

结果为907

### 任务3

使用`find`的`-size`指定文件大小，由于只需输出文件名，故使用`basename`除去文件名前的路径部分，由于文件过多，所以输出已经重定向到`large_file.txt`文件中
```bash
find ./abacus-develop -size +10k -exec basename '{}' \; > large_file.txt
```

### 任务4

使用`-w`和正则表达式指定`grep`的搜索条件，并使用`-r`递归搜索，作为`awk`的输入，用`END`表示读入最后一行文本后执行，并用`print NR`打印行数
```bash
grep -r -w "write" ./abacus-develop/source/module_io | awk 'END {print NR}'
```
结果为132

### 任务5

与任务3相似，只是将`find -exec`后的语句从`basename`改为`cat`以获取所有`cpp`文件的内容，并利用`wc`打印总行数
```bash
find ./abacus-develop -name '*.cpp' -exec cat '{}' \; | wc -l
```
结果为312330

## 作业二

### 步骤1：功能脚本

在`delete.sh`中实现删除文件的功能

```bash
#!/bin/bash

recycbin=~/recycbin

if [ ! -d $recycbin ]; then
    mkdir -p $recycbin
fi

echo "Running $0 ..."
echo "Moving $# files to recycbin"
mv $* -t $recycbin
exit 0
```

在`clear.sh`中实现清除回收站的功能
```bash
#!/bin/bash

recycbin=~/recycbin

if [ -d $recycbin ]; then
    rm -r "$recycbin"/*
    echo "Recycbin cleared"
else
    echo "Recycbin not found"
fi

exit 0
```

### 步骤2：转化为自定义命令

给脚本添加权限
```bash
chmod +x ~/mycmd/delete.sh
chmod +x ~/mycmd/clear.sh
```

向`.bashrc`添加`alias`
```bash
echo "alias dl='~/mycmd/delete.sh'" >> ~/.bashrc
echo "alias cl='~/mycmd/clear.sh'" >> ~/.bashrc
source ~/.bashrc
```