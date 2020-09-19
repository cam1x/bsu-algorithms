package by.bsu.fpmi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        BinaryTree binaryTree = new BinaryTree();

        List<String> strings = Files.readAllLines(Paths.get("input.txt"));
        strings.forEach(x -> binaryTree.add(Long.parseLong(x.trim())));

        binaryTree.traversePreOrder("output.txt");
    }
}

class BinaryTree {
    private TreeNode root;

    public void add(long value) {
        root = addRecursive(root, value);
    }

    private TreeNode addRecursive(TreeNode current, long value) {
        if (current == null) {
            return new TreeNode(value);
        }

        long currentValue = current.value;

        if (value < currentValue) {
            current.leftNode = addRecursive(current.leftNode, value);
        } else {
            if (value > currentValue) {
                current.rightNode = addRecursive(current.rightNode, value);
            }
        }

        return current;
    }

    public void traversePreOrder(String filePath) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
        traversePreOrder(writer, root);
        writer.close();
    }

    private void traversePreOrder(BufferedWriter writer, TreeNode node) throws IOException {
        if (node != null) {
            writer.write(node.value + "\n");
            traversePreOrder(writer, node.leftNode);
            traversePreOrder(writer, node.rightNode);
        }
    }

    private static class TreeNode {
        private long value;
        private TreeNode leftNode;
        private TreeNode rightNode;

        TreeNode(long value) {
            this.value = value;
        }
    }
}
