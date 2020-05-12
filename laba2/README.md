# hardLinks-osisp-lab2

Написать программу, находящую в заданном каталоге (первый аргумент командной строки) и всех его подкаталогах все файлы заданного расширения и создающий для каждого найденного файла жесткую ссылку в заданном каталоге. Расширение файла и каталог для жестких ссылок задаются в качестве второго и третьего аргументов командной строки.

how to use:

compile main.c with gcc:

gcc main.c -o main.exe


launch with 3 parameters:

$1 - source directory to find

$2 - extension to find (format: .*ext*, example extension sh: .sh)

$3 - directory to save hard links (ATTENTION: write full path, without ~, ., etc)

./main.exe $1 $2 $3


example:

./main.exe /etc .sh /home/parallels
