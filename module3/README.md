## Описание:

### clonedemo: Пример вызова функции `clone` с флагом `CLONE_PARENT` (родитель нового потомка будет таким же как и у вызывающего процесса) из лекций:

**Узнаем PID текущего процесса**
```
> echo $$
1
```

**Запуск:**
```
> make
> ./a.out > /dev/null &
[1] 16969
```

**Родитель и потомок имеют одного и того же родителя:**
```
> echo $$
2068
> pstree 2068
bash───2*[a.out]
```

-----------------------------------------------------------------------------------

### forkdemo: Пример вызова функции `fork`:

**Запуск:**
```
> make
> ./a.out
P: Это процесс родитель! Мой PID: 28471
C: Это процесс потомок! Мой PID: 28472
C: Мой родитель PID: 28471
P: PID потомка: 28472
P: PID родителя: 2068
P: Ждем когда потомок вызовет exit
P: Выход!
```

-----------------------------------------------------------------------------------

### task1. Поиск ppid c использованием procfs:

Разработать программу solution, которая осуществляет поиск родительского PID текущего процесса в файловой системе proc и выводит найденное значение на консоль. Результат, возвращаемый функций должен быть выведен отдельной строкой (должен оканчиваться символом перевода строки \n) в stdio.

**Пример вызова:**
```
./solution
13221
```

**Запуск:**
```
> make
> echo $$
2068
> ./solution
2068
```

-----------------------------------------------------------------------------------
   
### task2. Подсчет числа процессов с заданным именем:

Разработать программу solution, которая осуществляет поиск и подсчет числа процессов с именем genenv в системе Linux на которой выполняется программа.

**Пример вызова:**
```
./solution
113
```

**Запуск:**
```
> make
> for (( c=1; c<=5; c++ )) do ./genenv & done
> pstree -p
[...]
bash(2068)─┬─genenv(28019)
           ├─genenv(28020)
           ├─genenv(28021)
           ├─genenv(28022)
           ├─genenv(28023)
           └─pstree(28306)
[...]
> ./solution
> 5
```

-----------------------------------------------------------------------------------

### task3. Поиск пути к init по заданному pid:

Разработать программу solution, которая по заданному pid, осуществляет поиск пути в дереве процессов до процесса с идентификатором 1 (init). Для каждого найденного процесса печатается в отдельной строке его идентификатор.

**Пример вызова:**
```
./solution 1766
1766
1299
465
1
```

**Запуск:**
```
> make
> ./solution $(echo $$)
2068
2067
2028
1161
1
```

-----------------------------------------------------------------------------------

### task4. Подсчет процессов в поддереве:

Разработать программу solution, которая по заданному pid, осуществляет поиск всех потомков процесса с этим идентификатором и выводит их количество (включая процесс с заданным pid).
	
**Пример вызова:**
```
./solution 1233
76
```

**Запуск:**
```
> make
> ./solution 1
37
```

-----------------------------------------------------------------------------------

### task5. Создание демона:

Разработать программу solution, которая при запуске себя "демонизирует" и остается в памяти. Перед закрытием стандартного потока вывода stdout унаследованного от родителя, программа должна вывести в него Pid процесса-демона.

**Пример вызова:**
```
./solution
13221
```

**Запуск:**
```
> make
> ./solution
28490
> pstree -p
systemd(1)─┬─[...]
           ├─solution(28490)
> kill 2
```

-----------------------------------------------------------------------------------

## Дополнительно:

### Дерево процессов:

```
> pstree
systemd─┬─agetty
        ├─atd
        ├─cron
        ├─dbus-daemon
        ├─haveged
        ├─lvmetad
        ├─mdadm
        ├─mysqld───31*[{mysqld}]
        ├─nginx───8*[nginx]
        ├─php-fpm7.0───3*[php-fpm7.0]
        ├─redis-server───3*[{redis-server}]
        ├─rsyslogd─┬─{in:imklog}
        │          ├─{in:imuxsock}
        │          └─{rs:main Q:Reg}
        ├─sshd───sshd───sshd───bash───pstree
        ├─supervisord───long.sh───sleep
        ├─systemd───(sd-pam)
        ├─systemd-journal
        ├─systemd-logind
        ├─systemd-timesyn───{sd-resolve}
        └─systemd-udevd
```

### Процессы запущенные из текущей командной оболочки:

```
> less .bash_history &
> less .bash_logout &
> pstree -p
[...]
├─sshd(32731)───sshd(24673)───sshd(24690)───bash(24691)─┬─less(24747)
│                                                       ├─less(24758)
│                                                       └─pstree(24769)
[...]
```
-----------------------------------------------------------------------------------

## Полезные ссылки:
1. https://www.opennet.ru/man.shtml?topic=pstree&category=1&russian=0
1. https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=fork&category=2
1. https://www.opennet.ru/man.shtml?topic=exec&category=3&russian=0
1. https://www.opennet.ru/man.shtml?topic=clone&category=2&russian=0
1. https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=execve&category=2
1. https://www.opennet.ru/man.shtml?topic=wait&category=2&russian=0
1. https://www.opennet.ru/man.shtml?topic=setsid&category=2&russian=0