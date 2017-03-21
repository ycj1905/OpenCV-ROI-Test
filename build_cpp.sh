#file name: build_cpp.sh
#g++ -o test_3 test_3.cpp `pkg-config opencv --cflags --libs`
#chmod 755 build_cpp#

#!/bin/sh
if [ $# -gt 0 ] ; then
	base=`basename $1 .cpp`
	echo "compiling $base"
	g++ -o $base  $base.cpp `pkg-config opencv --cflags --libs` 
else
	 echo "Error, please supply a *.cpp file name !"
fi
