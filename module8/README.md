## Описание:

### task1. Разбор аргументов командной строки:

Требуется написать программу solution, выполняющую разбор опций командной строки и выводящую в стандартный поток вывода символ '+', если набор корректен, или '-' в противном случае.

Описание возможных опций:

-q | --query (опциональный, но обязательно требует аргумента)
-i | --longinformationrequest (опциональный)
-v | --version (опциональный)

**Вывод**

Программа выводит символ корректности опций командной строки.

**Пример вызова:**
```
./solution -q 9 --version
+
```

**Запуск:**
```
> make
> ./solution -q 9 --version
+
> ./solution -q 9 --t
-
> ./solution
+
> ./solution --option
-
```

-----------------------------------------------------------------------------------

## Полезные ссылки:
1. https://www.opennet.ru/man.shtml?topic=getopt&category=3&russian=0