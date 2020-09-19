package by.bsu.fpmi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException {
        Path path = Paths.get("input.txt");
        List<String> lines = Files.readAllLines(path);
        lines.remove(0);

        List<Pair> pairs = lines.stream()
                .map(x -> {
                    String[] parts = x.split("\\s+");
                    return Pair.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
                })
                .collect(Collectors.toList());

        MatrixOperationOptimization matrixOperationOptimization =
                new MatrixOperationOptimization(pairs);

        BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
        writer.write(matrixOperationOptimization.getNumOfMinOperations() + "");
        writer.close();
    }
}

class MatrixOperationOptimization {
    private int[][] resultMatrix;
    private List<Pair> pairs;
    private int numOfMinOperations;

    public MatrixOperationOptimization(List<Pair> pairs) {
        this.pairs = pairs;
        int size = pairs.size();
        resultMatrix = new int[size][];
        for (int i = 0; i < size; ++i) {
            resultMatrix[i] = new int[size];
        }
        numOfMinOperations = countMinNumOfMultiplies();
    }

    public int getNumOfMinOperations() {
        return numOfMinOperations;
    }

    private int countMinNumOfMultiplies() {
        int size = pairs.size();
        for (int step = 1; step < size; ++step) {
            for (int i = 0; i < size - step; ++i) {
                int j = i + step;
                resultMatrix[i][j] = Integer.MAX_VALUE;
                for (int k = i; k < j; ++k) {
                    resultMatrix[i][j] = Math.min(resultMatrix[i][j],
                            countNumOfMultiplyOperations(i, j, k));
                }
            }
        }
        return resultMatrix[0][size - 1];
    }

    private int countNumOfMultiplyOperations(int firstIndex, int lastIndex, int k) {
        return resultMatrix[firstIndex][k] + resultMatrix[k + 1][lastIndex] +
                pairs.get(firstIndex).getFirst() * pairs.get(k).getSecond() * pairs.get(lastIndex).getSecond();
    }
}

class Pair {
    int first;
    int second;

    public Pair(int first, int second) {
        this.first = first;
        this.second = second;
    }

    public static Pair of(int first, int second) {
        return new Pair(first, second);
    }

    public int getFirst() {
        return first;
    }

    public int getSecond() {
        return second;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Pair pair = (Pair) o;
        return first == pair.first &&
                second == pair.second;
    }

    @Override
    public int hashCode() {
        return Objects.hash(first, second);
    }
}