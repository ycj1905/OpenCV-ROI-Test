#
#file name: transfer.sh
#sudo ./transfer.sh ~/opencv_2.4.11/samples/c/fruits.jpg
#
#

#!/bin/sh
if [ $# -gt 0 ] ; then

	echo "transfering $1"

        sudo scp $1 root@192.168.7.2:~/chen1
else
	 echo "Error, please supply a file name to be transferred !"
fi









B
C
C

