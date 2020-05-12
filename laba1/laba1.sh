#!/bin/bash
# Написать скрипт, находящий все каталоги и подкаталоги начиная с заданного каталога и
# ниже на заданной глубине вложенности (аргументы 1 и 2 командной строки). Скрипт выводит
# результаты в файл (третий аргумент командной строки) в виде полный путь, количество
# файлов в каталоге. На консоль выводится общее число просмотренных каталогов.

ERROR_FILE="/tmp/ERROR.LOG"
exec 4>&2 2>$ERROR_FILE
amount=0
echo "" > $3

path=$(realpath $1)
for i in $(find $path -mindepth $(( $2-1 )) -maxdepth $(( $2-1 )) -depth -type d);
do
    #fullPath=$(realpath $i);
    amFiles=$(find $fullPath -maxdepth 1 -type f| wc -l);
    echo "$i $amFiles" >> $3 
    (( amount++ ))
done

echo "$amount"

exec 2>&4 4>&-
sed "s/.[a-zA-Z ]*:/$(basename $0):/" < $ERROR_FILE 1>&2

rm $ERROR_FILE
