# Разрушение дорог (простая версия)
В Берляндии nn городов, связанных mm дорогами. Гарантируется, что изначально граф из городов связный, т.е. существует путь между любой парой вершин.
В Берляндии происходит qq землетрясений, в ходе каждого из них разрушается ровно одна дорога. Необходимо после каждого землетрясения узнать, является ли полученный граф из городов связным. После очередного землетрясений дорога не перестраивается, то есть разрушается навсегда.

## Input
Первая строка входного файла содержит три числа n, m, q (1≤n,m,q≤100000) - количество городов, дорог и землетрясений в Берляндии соответственно.
Следующие q строк содержат по одному числу x_i (1≤x_i≤m) - номер дороги, которая пострадает во время i-ого землетрясения. Гарантируется, что два различных землетрясения не разрушают одну и ту же дорогу.

## Output
Выведите строку длины qq из нулей и единиц. ii-ый символ равен 1, если после ii-ого землетрясения граф оказался связным, в противном случае выведите 0.

### Example
Input:
```
4 6 6
1 2
2 3
3 4
4 1
3 1
4 2
1
6
2
5
4
3
```

Output:
```
110000
```
