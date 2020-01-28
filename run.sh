#!/bin/bash

exit_status=`make`

Files=("$@")

if ! [ $? -eq 0 ]
then
    echo "sth went wrong!!!!"
else
    if  [ $# -eq 0 ]
    then 
        echo "you dident put any argument!!!!"
    else
        for (( i=0 ; i < $# ; i++ ))
        do
            res=`./a.out ${Files[$i]}`
            echo $res
            sleep 6
        done
    fi
fi

