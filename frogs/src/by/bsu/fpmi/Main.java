package by.bsu.fpmi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        List<String> strings = Files.readAllLines(Paths.get("input.txt"));
        Integer[] inputArray = Arrays.stream(strings.get(1).split("\\s+"))
                .mapToInt(Integer::parseInt)
                .boxed()
                .toArray(Integer[]::new);

        BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
        writer.write(forwardSolution(inputArray) + "");
        writer.close();
    }

    public static int backSolution(Integer[] array) {
        if (array.length == 1) {
            return array[0];
        }
        int[] solution = new int[array.length + 1];
        solution[1] = array[0];
        solution[2] = -1;

        for (int i = 3; i < solution.length; ++i) {
            solution[i] = Math.max(solution[i - 2], solution[i - 3]) + array[i - 1];
        }
        return solution[array.length];
    }

    public static int forwardSolution(Integer[] array) {
        if (array.length == 1) {
            return array[0];
        }

        int[] solution = new int[array.length];
        solution[0] = array[0];
        solution[1] = -1;
        for (int i = 0; i <= solution.length - 3; ++i) {
            solution[i + 2] = Math.max(solution[i+2], solution[i] + array[i + 2]);
            if (i < solution.length - 3) {
                solution[i + 3] = Math.max(solution[i+3], solution[i] + array[i + 3]);
            }
        }

        return solution[solution.length - 1];
    }
}
