laba1: 
9. Написать скрипт, находящий все каталоги и подкаталоги начиная с заданного каталога и ниже на заданной глубине вложенности (аргументы 1 и 2 командной строки). Скрипт выводит результаты в файл (третий аргумент командной строки) в виде полный путь, количество файлов в каталоге. На консоль выводится общее число просмотренных каталогов.

laba2:
9. Написать программу, находящую в заданном каталоге (первый аргумент командной строки) и всех его подкаталогах все файлы заданного расширения и создающий для каждого найденного файла жесткую ссылку в заданном каталоге. Расширение файла и каталог для жестких ссылок задаются в качестве второго и третьего аргументов командной строки.

laba3: 
9. Написать программу шифрации всех файлов заданного каталога и его подкаталогов. Пользователь задаёт имя каталога. Главный процесс открывает каталоги и запускает для каждого файла каталога и отдельный процесс шифрации. Каждый процесс выводит на экран свой pid, полный путь к файлу, общее число зашифрованных байт. Шифрация по алгоритму сложения по модулю 2 бит исходного файла и файла ключа. Число одновременно работающих процессов не должно превышать N (вводится пользователем). Проверить работу программы для каталога /etc.

laba4:
Таблица 1: вариант №1.
1->2 
2->(3,4) 
4->5 
3->6 
6->7 
7->8
Таблица 2: вариант №5.
1->(2,3,4,5) SIGUSR1 
5->(6,7,8) SIGUSR1 
8->1 SIGUSR1
Создать дерево процессов согласно указанного варианта индивиду-ального задания.
Процессы непрерывно обмениваются сигналами согласно индивиду-альному варианту. Каждый процесс при получении или посылке сигнала выводит на консоль информацию в следующем виде:
N pid ppid послал/получил USR1/USR2 текущее время (мксек) где N-номер сына.
Процесс 1, после получения 101 –го по счету сигнала SIGUSR, посы-лает сыновьям сигнал SIGTERM и ожидает завершения всех сыновей, после чего завершается сам. Процесс 0 ожидает завершения работы процесса 1 по-сле чего завершается сам. Сыновья, получив сигнал SIGTERM, завершают работу с выводом на консоль сообщения вида:
pid ppid завершил работу после X-го сигнала SIGUSR1 и Y-го сигнала SIGUSR2.
где X, Y – количество посланных за все время работы данным сыном сигналов SIGUSR1 и SIGUSR2.


