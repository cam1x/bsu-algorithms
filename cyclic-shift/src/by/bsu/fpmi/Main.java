package by.bsu.fpmi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        Path path = Paths.get("input.txt");
        List<String> lines = Files.readAllLines(path);

        BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
        writer.write("" + SubstringFinder.indexOf(lines.get(1) + lines.get(1), lines.get(2)));
        writer.close();
    }
}

class SubstringFinder {
    public static int indexOf(String source, String pattern) {
        int sourceLength = source.length();
        int patternLength = pattern.length();

        if (patternLength == 0) {
            return 0;
        }

        int[] prefix = createPrefixFunction(pattern);
        int sourceIndex = 0;
        int patternIndex = 0;

        while (sourceIndex < sourceLength) {
            if (source.charAt(sourceIndex) == pattern.charAt(patternIndex)) {
                ++sourceIndex;
                if (++patternIndex == patternLength) {
                    return sourceIndex - patternLength;
                }
            } else {
                if (patternIndex > 0) {
                    patternIndex = prefix[patternIndex - 1];
                } else {
                    ++sourceIndex;
                }
            }
        }

        return -1;
    }

    private static int[] createPrefixFunction(String line) {
        int[] prefix = new int[line.length()];
        int leftIndex = 0;

        for (int i = 1; i < line.length(); i++) {
            if (line.charAt(i) == line.charAt(leftIndex)) {
                prefix[i] = ++leftIndex;
            } else {
                if (leftIndex != 0) {
                    leftIndex = prefix[leftIndex - 1];
                }
            }
        }

        return prefix;
    }
}