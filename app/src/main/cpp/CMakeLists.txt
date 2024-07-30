cmake_minimum_required(VERSION 3.18.1) # 表示最低支持的cmake版本
project("voicechange")

# TODO 第一步：导入头文件
include_directories(inc) # CMakeLists.txt 目录下的inc文件夹 放头文件

# TODO 第二步：导入库文件（C++的环境变量）- 最新的方法，以前是 add_xxx（已淘汰）6.0以下才可以
# 环境变量的添加是追加的方式的：%JAVA_HOME%;%ANDROID_HOME%;path1;path2;
# CMAKE_SOURCE_DIR：获得当前CmakeLists.txt的路径
# CMAKE_ANDROID_ARCH_ABI：自动获取 四大平台架构值  也可以在gradle里面进行指定
# 这个set的写法就相当于  path = path + CMAKE_CXX_FLAGS；
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

# 批量导入 所有的C++文件
#file(GLOB allCPP *.c *.h *.cpp)

# TODO 库名的规则： lib + 名称 + .so   (lib .so 系统自动拼接的)
add_library( # Sets the name of the library.
        voicechange  #libvoicechange.so

        SHARED #表示动态库    STATIC 表示静态库

        native-lib.cpp
        # ${allCPP}  # 批量导入
        )

# 相当于 var log-lib = log (liblog.so 库的路径)
find_library( # Sets the name of the path variable.
        m-lib # 变量名

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        # 这里就相当于 定位到ndk的 liblog.so 库的路径
        log  #查找NDK的日志打印库
        )

# TODO 第三步：链接第三方库 到 我们自己的库(libvoicechange.so)里面
target_link_libraries( # Specifies the target library.
        voicechange

        # Links the target library to the log library
        # included in the NDK.
        ${m-lib} # 链接m-lib库 到 我们自己的库(libvoicechange.so)里面
        fmod
        fmodL
        )

