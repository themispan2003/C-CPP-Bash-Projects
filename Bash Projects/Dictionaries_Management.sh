#!/bin/bash
# elegxoyme an o xristis exei dosei orisma
if [ $# -ne 1 ]; then 
  echo "you put few arguments or more than one argument"
  exit 0;
fi
#An den yparxei o katalogos tote dimioyrgoyme ayton kai toys ypokatalogous antistoixa
if [ ! -d "$1" ]; then 
  echo "direcory does not exist"
  echo "i will create it now!"
  mkdir "$1"  
  mkdir "$1"/bdir
  mkdir "$1"/cdir 
else      # an yparxei o katalogos elegxoume gia tin yparxi ypokatalogon 
  echo "$1 exists"  # kai an den yparxoun tous dimiourgoume
  if [ ! -d "$1"/bdir ]; then
    echo "direcory does not exist"
    echo "i will create it now!"
    mkdir "$1"/bdir  
  fi
  if [ ! -d "$1"/cdir ]; then
  echo "direcory does not exist"
  echo "i will create it now!"
  mkdir "$1"/cdir 
  fi
fi
#stin metavliti x apothikeyoume thn timh tou pipe 
#To pipe pernaei tin lista tvn arxion toy katalogou sthn eisodo tou grep gia tin emfanisi ton arxeion pou xekinane apo a-l h A-L
i=0 
for x in $(ls $1 | grep '^[a-lA-L]' ); do
  i=$((i+1))
  #elegxoume an ayto pou apothikeyetai sto x einai katalogos gia na mh metakinithei
  if [ ! -f "$1"/"$x" ]; then    
   echo $i"st file $x is a directory!" 
   continue
  fi
  echo $i"st file of "$1" is $x"
  mv "$1"/$x "$1"/bdir #metakinoume kathe arxeio tou katalogou sto bdir
done
#stin metavliti m apothikeyoume thn timh tou pipe 
#To pipe pernaei tin lista tvn arxion toy katalogou sthn eisodo tou grep gia tin emfanisi ton arxeion pou jekinane apo m-zM-Z
j=0
for m in $(ls $1 | grep '^[m-zM-Z]' ); do
  i=$((i+1)) 
  #elegxoume an ayto pou apothikevetai stin m einai katalogos gia na mh metakinithei
  if [ ! -f "$1"/"$m" ]; then 
    echo $i"st file $mg is a directory!" 
    continue
  fi
  echo $i"st file of "$1" is $m"
  mv "$1"/$m "$1"/cdir # metakinoume kathe arxeio tou katalogou sto cdir
done

amount1=$( ls "$1"/bdir | wc -l)  #apothikeuoyme sto z1 kai sto z2 to plithos ton arxeion tou bdir kai tou cdir
echo "the files of the bdir are $amount1" > num.txt #anakatefthinoume sto num.txt to plithos ton arxeion tou bdir kai tou cdir
amount2=$( ls "$1"/cdir | wc -l)
echo "the files of the cdir are $amount2" >> num.txt
amount3=$((amount1 + amount2))
echo "the files of the cdir and bdir are $amount3" >> num.txt #synoliko plithos arxeiwn twn dyo ypokatalogwn