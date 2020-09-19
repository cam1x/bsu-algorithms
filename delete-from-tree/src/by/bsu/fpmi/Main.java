package by.bsu.fpmi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Main extends Thread {
    public static void main(String[] args) {
        new Thread(null, new Main(), "Deleting value from tree", 64 * 1024 * 1024).start();
    }

    @Override
    public void run() {
        try {
            BinaryTree binaryTree = new BinaryTree();

            List<String> strings = Files.readAllLines(Paths.get("input.txt"));
            long toDeleteValue = Long.parseLong(strings.get(0));

            strings.remove(0);
            strings.remove(0);

            strings.forEach(x -> binaryTree.add(Long.parseLong(x.trim())));
            binaryTree.remove(toDeleteValue);

            binaryTree.traversePreOrder("output.txt");
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}

class BinaryTree {
    private TreeNode root;

    public void add(long value) {
        root = addRecursive(root, value);
    }

    public void remove(long value) {
        root = removeRecursive(root, value);
    }

    public void traversePreOrder(String filePath) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
        traversePreOrder(writer, root);
        writer.close();
    }

    private TreeNode addRecursive(TreeNode current, long value) {
        if (current == null) {
            return new TreeNode(value);
        }

        long currentValue = current.value;

        if (value == currentValue) {
            return current;
        }

        if (value < currentValue) {
            current.leftNode = addRecursive(current.leftNode, value);
        } else {
            current.rightNode = addRecursive(current.rightNode, value);
        }

        return current;
    }

    private TreeNode removeRecursive(TreeNode current, long value) {
        if (current == null) {
            return null;
        }

        long currentValue = current.value;

        if (value == currentValue) {
            if (current.leftNode == null && current.rightNode == null) {
                return null;
            }
            if (current.rightNode == null) {
                return current.leftNode;
            }
            if (current.leftNode == null) {
                return current.rightNode;
            }

            long smallestValue = findSmallestValue(current.rightNode);
            current.value = smallestValue;
            current.rightNode = removeRecursive(current.rightNode, smallestValue);
            return current;
        }

        if (value < currentValue) {
            current.leftNode = removeRecursive(current.leftNode, value);
        } else {
            current.rightNode = removeRecursive(current.rightNode, value);
        }

        return current;
    }

    private long findSmallestValue(TreeNode root) {
        return (root.leftNode == null) ? root.value : findSmallestValue(root.leftNode);
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