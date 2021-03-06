## Описание:

### libdemo: Пример динамической библиотеки из лекций:

**Запуск:**

```
> make
> ./hello
Hello Andrew!
```

-----------------------------------------------------------------------------------

### task1. Создание динамической библиотеки:

В этом задании Вам необходимо создать разделяемую динамическую библиотеку libsolution.so в которой реализовать функцию со следующим прототипом:

```
int stringStat(const char *string, size_t multiplier, int *count);
```

Функция возвращает значение длины строки string, умноженное на multiplier, и увеличивает на 1 значение, на которое указывает count.


**Запуск:**

```
> export LD_LIBRARY_PATH=.
> make exe
> ./solution
[...]
> ldd solution
[...]
libsolution.so => ./libsolution.so (0x00007fd34d302000)
[...]
```

-----------------------------------------------------------------------------------

### task2. Run-time компоновка:

Разработать программу solution, обеспечивающую загрузку динамической библиотеки в режиме исполнения. При запуске, программе передается имя динамической библиотеки, имя функции которая должна быть вызвана, и ее аргумент. Функция в библиотеке принимает на вход int и возвращает int. Результат, возвращаемый функцией должен быть выведен отдельной строкой (оканчиваться символом новой строки \n)  в stdout.

**Пример вызова:**

```
> ./solution libShared.so someSecretFunctionPrototype 8
16
```

В примере, должна быть загружена библиотека libShared.so, в которой вызвана функция someSecretFunctionPrototype с аргументом 8. Результат (16) выведен в stdout.

**Запуск:**

```
> make lib
> make
> ./solution libShared.so multiplier 8
16
> rm libShared.so
> ./solution libShared.so multiplier 8
Library was not loaded
```


-----------------------------------------------------------------------------------

## Полезные ссылки:
1. https://www.opennet.ru/man.shtml?topic=nm&category=1&russian=2
2. https://www.opennet.ru/man.shtml?topic=ld-linux.so&category=8&russian=0
3. https://www.opennet.ru/base/dev/lib_dependence.txt.html
4. https://www.opennet.ru/man.shtml?topic=dlopen&category=3
5. https://www.opennet.ru/man.shtml?topic=dlsym&category=3&russian=0
