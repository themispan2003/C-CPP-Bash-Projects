#!/bin/bash 

if test $# != 1; then #	Check the arguments
	echo "give the arguments"
	exit 1
fi 

if [ ! -d ~/Desktop/$1 ]; then #check the path of the students projects directory
	echo "the directory does not exist"
	exit 1
fi

if [ ! -f ~/Desktop/grades.txt ]; then #check the path of grades.txt file
	echo "the file does not exist, we create it."
	touch ~/Desktop/grades.txt
else
	echo "the file grades.txt exists, we remove it and we recreate it."
	rm ~/Desktop/grades.txt
	touch ~/Desktop/grades.txt
fi

for s in $(ls $1)
do 
 z=0
 x=0   #for every sub_dictionary s of students_projects
 y=0
 v1=$(grep "20" $1/$s/project1.c)
 if [ "$v1" != "" ]; then 	#if v1 = 20 then projects1 grade = 30 else zero
 	z=30
 else
 	z=0
 fi
 v2=$(grep "10" $1/$s/project2.c)
 if [ "$v2" != "" ]; then 	#if v2 = 10 then projects1 grade = 70 else zero
 	y=70
 else
 	y=0
 fi
 x=$(($z + $y))
 cat $1/$s/report.txt >> grades.txt   #Put students details to grades.txt file
 echo " project1 = $z project2 = $y total_grade = $x" >> grades.txt #Put students grades1 to grades.txt file
done 

echo "Do you want to organise projects?[y/n]" 
read answer
if [ $answer = 'n' ]; then
	echo "exit!"
	exit 1 
elif [ $answer = 'y' ]; then
	if  [ ! -d ~/Desktop/organised ]; then
	 mkdir ~/Desktop/organised
	 echo 'organised created, continue'
	fi
else 
	echo 'Wrong input!'
	echo 'exit!'
	exit 1
fi

for s in $(ls $1)   #for every sub_dictionary of students_projects§s§
do
 kl=$(cat $1/$s/report.txt)   #kl saves the students details 
 kl1=$(echo "$kl" | tr ' ' '_')  #kl1 saves the students details with _
 kl2=$(echo $kl1"_project1")  #kl3 and kl2 save the names we want
 kl3=$(echo $kl1"_project2")
 cp $1/$s/project1.c ~/Desktop/organised/$kl2 #copy of projects to organised directory of desktop
 cp $1/$s/project2.c ~/Desktop/organised/$kl3
done
