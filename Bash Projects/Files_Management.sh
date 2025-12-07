#!/bin/bash
# synartish dimioyrgias 
function create() {
  echo "give the file you want to write"
  read file      
  if [  -f "$file" ]; then #an to arxeio yparxei tote mas dixnei minima
    echo  "This file exists! We wil add information to this"
  else # allios dimiourgei
    touch $file
    echo "file creation is complete"
  fi 
  echo  "If you want to stop writing, press ctrl + d!"
  echo  "Give details (code name surname id degree department): "
  cat >> $file #anakateythinsh ths eisodou apo to terminal ws exodos sto arxeio
  echo  "registration is complete"
}
# synartish dimioyrgias prosthikis 
function add() {
  echo "give the file you want to write"
  read file
  if [  -f "$file" ]; then #an to arxeio yparxei tote mas dixnei minima
    echo "This file exists! We wil add information to this"
  else
    touch $file # allios dimiourgh
    echo "file creation is complete"
  fi
  echo "Give details (code name surname id degree department): "
  echo "Press control + d to finish!"
  cat >> $file #anakateythinsh ths eisodou apo to terminal ws exodos sto arxeio
  echo "registration is complete"
}
# synartish anazitisis
function search() { 
  echo "Put file you want to search student with am:" #diavasma arxeiou pou tha anazitisoume
  read file2
  while [ ! -f "$file2" ]; do #oso den yparxei to arxeio emfanizei minima
    echo "There is no such file, try again!"
    read file2
  done
    echo "Give an am: " # dinoume arithmo mitroou
    read am 
    z=$(echo "$am" | grep '^[0-9]*$' | grep '^.\{6\}$') # apothikeuoume se mia metavliti z thn exodo ths solinoshs gia na kanoyme elegxo egkirotitas
    if [ "$am" = "$z" ] && [ "$am" != " " ]; then
      zr2=$(awk '{print $4}' $file2 | grep $am) 
      zr3=$(awk '{print $0}' $file2 | grep $am) #an h exodos einai to am simainei tote am=z oti einai egkyro kai an  vrethei stin 4h stilh toy arxeiou tote  zr2=am kai emfanizei ta stoixeia toy foitth
      if [ "$am" = "$zr2" ]; then
        echo "A student with this am: $am exists in this file"
        echo $zr3
      else 
        echo "A student with this am does not exist in this file"
      fi
    else
    echo "AM must contain 6 numbers only! try again!"
    fi

}

function show() {
  echo "Give me the file to show the statistics:"
  read file
  while [ ! -f "$file" ]; do
    echo "There is no such file, try again!"
    read file
  done
  temp=() #arxikopoihsh toy pinaka temp
  myArray=($(awk '{print $6}' $file | sort))  #pername tis times tis 6hs sthlhs taxinomimenes ston pinaka myarray
  myArray2=($(awk '{print $6}' $file))
  count=0 
  #programma poy afairei ta koina stoixeia apo ton pinaka myarray,          dhmiourgontas ton temp xwris ta duplicates
  for (( i=0; i<${#myArray[@]}; i++ )) do 
      for (( j=0; j<$count; j++ )) do 
          if [ "${myArray[i]}" = "${temp[j]}" ]; then
              break
          fi
      done
      if [ "$j" = "$count" ]; then 
               temp[count]=${myArray[i]}
               count=$((count+1))
      fi      
    done 

  for value in "${temp[@]}"; do #kathe fora poy emfanizei stoixeio toy temp sto myarray2 afksanei to count kata 1
    for value1 in "${myArray2[@]}"; do
      if [ "$value1" = "$value" ]; then
        countr=$((countr+1))
      fi
    done
     echo "$value: $countr"
     countr=0
  done
}
  
choice=0
while [ "$choice" != "5" ]; do #oso to choice den einai 0 enfanizei to menu
  
  echo "1. File Creation." 
  echo "2. Addition."
  echo "3. Search."
  echo "4. Show details."
  echo "5. Exit."
  echo "Make a choice: "
  read choice
  case $choice in
         "1") 
            create 
          ;;
          "2") 
             add 
          ;;
          "3") 
            search
          ;;
          "4") 
            show 
          ;;
          "5") 
             echo "Exit"            
          ;; 
          *) 
            echo "Illegal choice";;  
      esac
      echo
done 
exit 0; 