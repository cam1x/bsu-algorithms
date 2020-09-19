package by.bsu.fpmi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Main {
    public static void main(String[] args) throws IOException {
        Set<Long> numberSet = new HashSet<>();

        List<String> strings = Files.readAllLines(Paths.get("input.txt"));
        strings.forEach(x -> numberSet.add(Long.parseLong(x)));

        long sum = numberSet.stream()
                .mapToLong(Long::longValue)
                .sum();

        BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
        writer.write(Long.toString(sum));
        writer.close();
    }
}