#!/bin/bash

dir=${PWD##*/}
num=0
if [ $# == $num ]
then 
	content=$(date '+%Y-%m-%d %H:%M:%S')
else
	content=$1
fi

#pull from github
#echo "git clone git@github.com:fengjunpku/"$dir".git"

#add & commit
git add *
git commit -m \"$content\"

#push to github
git push origin master
