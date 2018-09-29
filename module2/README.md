## Описание:

### filedemo: Пример работы с файлами и ссылками на файл из лекции:

**Запуск:**

```
> make
> echo "Hello" > test
> ln test test.hardlink
> ln -s test test.softlink
> ./links test
fd: Success
fd=3
sz=6
> ./links test.hardlink
fd: Success
fd=3
sz=6
> ./links test.softlink
fd: Too many levels of symbolic links
fd=-1
sz=-1
```

-----------------------------------------------------------------------------------

### task1. Подсчет суммарного количества системных вызовов read, write с помощью `strace`:

**Запуск:**

```
> make
> strace -o trace.txt -e trace=read,write ./solution
What is your name? __
Andrew
Hello Andrew
> grep -oE "^(write|read)" trace.txt | wc -l
4
> grep -oE "^(write|read)" trace.txt
read
write
read
write
```

-----------------------------------------------------------------------------------

### task2. Определяет список родителей процесса с идентификатором pid с помощью файловой системы proc:

**Запуск:**

```
> make
> ./solution $(echo $$)
1820
1819
1782
1143
--------
1 (init)
```
-----------------------------------------------------------------------------------

## Дополнительно:

### Создание ссылок на файлы:

```
> echo 'Hello' > test
> stat test
File: 'test'
Size: 6         	Blocks: 8          IO Block: 4096   regular file
Device: 902h/2306d	Inode: 106168796   Links: 2
[...]
> ln test test.hardlink
> stat test.hardlink
File: 'test.hardlink'
Size: 6         	Blocks: 8          IO Block: 4096   regular file
Device: 902h/2306d	Inode: 106168796   Links: 2
[...]
> ln -s test test.softlink
> stat test.softlink
File: 'test.softlink' -> 'test'
Size: 4         	Blocks: 0          IO Block: 4096   symbolic link
Device: 902h/2306d	Inode: 106168798   Links: 1
[...]
> rm test
> cat test.hardlink
Hello
> cat test.softlink
cat: test.softlink: No such file or directory
> echo "Hello, world!" >test
> cat test.softlink
Hello, world!
```

-----------------------------------------------------------------------------------

### Пример работы с файловой системой proc:

#### Имя текущего процесса:
```
> echo $$
1820
> cd /proc/1820
> cat comm
bash
```

#### Текущий каталог текущего процесса:
```
> ls -la cwd
[...] cwd -> /proc/1820
> cd /tmp
> ls -la /proc/1820/cwd
[...] /proc/1820/cwd -> /tmp
```

#### Статистика по текущему процессу:
```
> cd /proc/1820
> cat status
Name:	bash
State:	S (sleeping)
Tgid:	1820
Ngid:	0
Pid:	1820
PPid:	1819
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
[...]
```

#### Информация о ядрах процессора:

```
> cat /proc/cpuinfo
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 61
model name	: Intel(R) Core(TM) i5-5257U CPU @ 2.70GHz
stepping	: 4
cpu MHz		: 2699.998
cache size	: 3072 KB
[...]
```

#### Информация о состоянии памяти:

```
> cat /proc/meminfo
MemTotal:        2048040 kB
MemFree:         1779528 kB
MemAvailable:    1841548 kB
Buffers:           13704 kB
Cached:           177604 kB
SwapCached:            0 kB
[...]
```

#### Идентификатор родителя процесса:
```
> cat /proc/$(echo $$)/status | grep PPid
1819
```

-----------------------------------------------------------------------------------

## Полезные ссылки:
1. https://www.opennet.ru/docs/RUS/zlp/005.html
1. https://linux.die.net/man/2/open
1. https://linux.die.net/man/2/read
1. https://linux.die.net/man/2/write
1. https://linux.die.net/man/2/close
1. https://linux.die.net/man/2/lseek
1. https://linux.die.net/man/2/fcntl
1. https://linux.die.net/man/2/creat
1. https://linux.die.net/man/2/unlink
1. https://linux.die.net/man/1/ltrace
1. https://linux.die.net/man/1/strace
1. https://www.opennet.ru/man.shtml?topic=mount&category=8
