.include <bsd.own.mk>

WARNS?=			0				# 编译语法检查等级: 0～5, 5 最严格

LIB=			gcydds	# 库名称
MKDEBUGLIB:=	no				# 不构建调试库
MKLINT:=		no				# 不进行 lint 检查
MKPICLIB:=		no				# 不编译 PIC 版本库
MKSHLIBOBJS:=	no
MKPICINSTALL:=	no				# 不安装 PIC 版本库
MKPROFILE:=		no				# 不构建性能分析库

INCS=		gcydds.h	# 需要和库一起提供的头文件
INCSDIR=	/usr/include		# 指定头文件的保存路径




DDS_VMAJOR?=	1          # 主版本号
DDS_VMINOR?=	0          # 次版本号
DDS_BUILDTS_STR != date +%s  # build time

DINIX_CFLAGS_SWITCH:=	yes			# 开启自定义配置，走基于NetBSD重建的编译规则 @Added by Shijian.Pang on 2025.03.11

# 编译关联参数 如 编译用到的头文件路径指定 编译优化参数等
CFLAGS+=   -I${.CURDIR} 
# CFLAGS+=   -I${.CURDIR}/../../include/DDS 
CFLAGS+=   -DDDS_VMAJOR=$(DDS_VMAJOR) 
CFLAGS+=   -DDDS_VMINOR=$(DDS_VMINOR) 
CFLAGS+=   -DDDS_BUILDTS_STR="\"$(DDS_BUILDTS_STR)\"" 
CFLAGS+=   -O2 -fPIC   

# 工程源文件 如 .c .cpp
SRCS+=	gcydds.c discovery.c domain_router.c serialization.c transport.c ddscrc16.c


LDSTATIC=	-static		# 静态库方式链接s
LDADD= -lsys


SHLIB_MAJOR=	$(DDS_VMAJOR)	# 库的主版本 最后生成动态库时会紧跟 .so 后缀显示， 如 xxx.so.1
SHLIB_MINOR=	$(DDS_VMINOR)	# 库的副版本 最后生成动态库时会紧跟 .so.1 后缀显示， 如 xxx.so.1.0

.include <dinix.lib.mk>
 