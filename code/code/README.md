# Код
Вас наняло Управление национальной безопасности для того, чтобы взломать RSA-код, который используется в одной очень секретной системе. Но от вас требуется только решить одну подзадачу, чтобы остальные специалисты Управления могли использовать ваши результаты для дальнейшего взлома.

Для этой цели можно воспользоваться следующим алгоритмом:
* Вы собираете коллекцию C отношений, не содержащую квадрат. Сначала C пустая.
* Затем, когда на вход поступают отношения, C начинает расти. Предположим, что на вход было подано отношение { p, q }. Если не возникло квадратов при добавлении отношения в коллекцию, то отношение просто добавляется в коллекцию. В противном случае нужно увеличить число квадратов, но отношение не добавляется в коллекцию.
Реализуйте этот алгоритм и примените его к конкретному набору отношений, чтобы получить число квадратов.

## Input
В первой строке содержатся два целых числа n и r (1 ≤ n, r ≤ 100 000), где n — мощность множества P, а r — число отношений.
Заметим, что в данной задаче можно не уделять внимания тому, какие именно простые числа составляют множество P, а использовать их индексы, так как на решение это не влияет.

Далее следуют r строк, в каждой из которых записаны два целых числа i и j, которые образуют отношение { pi, pj } (1 ≤ i, j ≤ n). Гарантируется, что числа i и j различны.

## Output
В первой и единственной строке выведите число квадратов, которые могут быть образованы данными отношениями при помощи указанного выше алгоритма.

### Example
Input:
```
6 7
1 2
3 5
2 4
1 4
3 5
1 6
4 6
```

Output:
```
3
```

Пусть P = { 2, 3, 5, 7, 11, 13 }, т. е. p1 = 2, p2 = 3, p3 = 5, p4 = 7, p5 = 11, p6 = 13.
Первым на вход поступает отношение S1 = { p1, p2 } = { 2, 3 }, и мы помещаем его в C.
Далее следуют отношения S2 = { 5, 11 }, S3 = { 3, 7 }, и они тоже помещаются в C.
Но когда поступает отношение S4 = { 2, 7 }, оно образует квадрат с отношениями из C, т. е. S1 ⋅ S3 ⋅ S4 = { 2, 3 } ⋅ { 3, 7 } ⋅ { 2, 7 } = (2 ⋅ 3 ⋅ 7)2 (так как образован квадрат, то мы увеличиваем число квадратов и не помещаем отношение S4 в C).
Далее поступает отношение S5 = { 5, 11 }, которое образует квадрат с отношением S2.
Далее отношение S6 = { 2, 13 } помещаем в С.
И наконец, поступает отношение S7 = { 7, 13 }, которое образует квадрат S1 ⋅ S3 ⋅ S6 ⋅ S7. Таким образом, мы получили три квадрата.
