# Class-Helper
基于QT C++的跨平台GUI程序，实现公平的课堂氛围

## 开发环境：
开发语言：C++  
开发环境：QT 5.11.1  
数据库：sqlite

## 适用平台
适用平台：`Windows、Linux、Mac Os X`（相应的编译环境编译得到二进制程序即可）  
注：对windows xp的支持需要`QT版本小于QT 5.6.3`

## 功能说明： 
* 信息管理
  * 从excel导入班级信息
  * 查看班级信息
  * 删除班级信息

* 随机打乱全班座位

* 挑选一位同学：
  * 不区分性别
  * 男
  * 女

* 挑选二位同学：
  * 不区分性别
  * 两男
  * 两女
  * 男+女
  
* 整体分组
  * 单人分组
  * 两两分组

## 二进制构建步骤：
#### 1、下载源代码文件夹：
```Bash
wget https://codeload.github.com/oneflyingfish/Class-Helper/zip/master #可通过浏览器下载
unzip Class-Helper-master.zip   #可用其它方式解压
cd ...\ClassHelper
```

#### 2、构建Makefile：
``` Bash
qmake       #需要QT环境支持
```

#### 3、编译release版本：
```Bash
make        #Windows环境make可用nmake替代
```

#### 4、编译debug版本：
```Bash
make debug  #Windows环境make可用nmake替代
```

#### 5、编译debug+release版本：
```Bash
make all    #Windows环境make可用nmake替代
```
#### 6、添加资源文件
将Class-Helper文件夹下的"Icon文件夹"和"ClassInformation.db"拷贝到二进制文件所在目录即可  

注：程序提供了releases版本下载，可前往[下载链接]()

最后，再次感谢西电廉虹老师的信任与支持！！
