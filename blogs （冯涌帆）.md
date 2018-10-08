# SoftwareClass
Team Blogs
根据老师给出的步骤，我先安装了Visual C++ 2010 express （指学习版），然后下载了要用的gdal文件
打开VC++2010后，首先创建控制台项目，然后在firstDemo.cpp里先把引用头文件的代码敲进去，因为此时还没有把gdal的头文件拷到项目目录里，所以提示错误，我把头文件拷进去之后，又添加了项目的主要代码。

![Image text](https://github.com/lovelyfanzi/information/blob/master/so.png?raw=true)

但是依旧不能运行。
将gdal的三种文件都移到项目目录里之后，还要添加一段代码
#pragma comment(lib, "gdal_i.lib")
之后我的项目还是一直出错，检查后发现代码中的trees.jpg我没有添加到项目文件夹里，添加之后程序就能正常运行了。

![Image text](https://github.com/lovelyfanzi/information/blob/master/fo.png?raw=true)

我所选用的那张图片就是老师示范中的那张tree.jpg

![Image text](https://github.com/lovelyfanzi/information/blob/master/trees.jpg?raw=true)

在实验过程中其实我还遇到了蛮多问题，首先就是一开始vs环境总是出问题，后来经过同学调整之后总算可以用了。其实编译过程过程中的问题倒还不多，只是因为几个gdal文件放的位置不对而导致了好几次出错。而且VC++反应比较慢，有时已经改完了但是编译还是出错，只有重新打开之后才能改正。
比较困扰我的还是写md文件的时候，一开始我将图片存在本地，md文件里插入图片之后，上传到github里就看不到了。老师说的新浪图床的用法也没弄明白，结果就自己上网搜了一下，最后找到了在Github的md文件中显示图片的方法，就是先将图片上传到我自己的库里，然后把图片的网址复制，直接在md文件里引用。
这次实验总的来说做的还是很开心的，特别是通过自己的努力能解决过程中遇到问题时，就会有很大的成就感。

