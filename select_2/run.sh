#!/bin/bash

	str=`tty | awk -F"/" '{print $4}'`
	if [ "$str" == "3" ];then
		./demo_client
		echo "i am tty 3"| stdin
	else
		echo "hahahh"
	fi


