#!/bin/bash

i=0
while :
do
str=`netstat -na | grep '8001' | grep 'TIME_WAIT' | awk '{print $6}'`
	if [ "$str" == "TIME_WAIT" ];then
	   let i++
	   sleep 1;
   else
         break;
   fi
done

echo "$i"


