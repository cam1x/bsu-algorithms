# Химическая реакция
Некоторая матрица A размера n × n задаёт результаты химической реакции веществ. Все вещества имеют номера от 1 до n. Элемент aij матрицы равен номеру того вещества, которое получается в результате химической реакции вещества i с веществом j (если вещества не вступают в реакцию, то aij = 0). Задана пробирка, в которую последовательно добавляются некоторые химические вещества в определённой пропорции. Вещество i вступает в химическую реакцию с веществом j, если находится в пробирке непосредственно над ним. Если вещества не вступают в реакцию, то они не смешиваются в пробирке. Необходимо определить, какие вещества и в какой последовательности будут находиться в пробирке после того, как все вещества будут добавлены в пробирку.

## Input
Первая строка содержит число n различных веществ (1 ≤ n ≤ 300) и число m добавляемых веществ (1 ≤ m ≤ 1 000 000). Следующие n строк содержат элементы матрицы, каждая строка содержит разделённые пробелом элементы соответствующей строки матрицы. Гарантируется, что матрица является симметричной (aij = aji для всех i, j) и одинаковые вещества между собой не реагируют, а смешиваются (aii = i для всех i). Последняя строка содержит m чисел, которые соответствуют номерам веществ. Номера химических веществ следуют в строке в той последовательности, в которой они добавлялись в пробирку.

## Output
Выведите разделённые пробелом номера химических веществ, которые получились в пробирке, начиная от верхнего уровня и заканчивая самым нижним уровнем (после последнего вещества в строке пробел не выводится).

### Example
Input:
```
3 4
1 3 2
3 2 1
2 1 3
1 3 1 2
```

Output:
```
1
```