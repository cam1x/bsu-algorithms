package by.bsu.fpmi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class Main extends Thread {
    public static void main(String[] args) {
        new Thread(null, new Main(), "Deleting value from tree", 64 * 1024 * 1024).start();
    }

    @Override
    public void run() {
        try {
            BinaryTree binaryTree = new BinaryTree();

            List<String> strings = Files.readAllLines(Paths.get("input.txt"));
            strings.forEach(x -> binaryTree.add(Long.parseLong(x.trim())));
            binaryTree.setHeightAndMslForEachNode();

            binaryTree.deleteAvgValueOfMaxSemiWay();
            binaryTree.traversePreOrder("output.txt");
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}

class BinaryTree {
    private TreeNode root;
    private long maxMsl;

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

    public void setHeightAndMslForEachNode() {
        setHeightAndMslForEachNode(root);
    }

    public void deleteAvgValueOfMaxSemiWay() {
        Set<Long> maxWayValues = new TreeSet<>();

        TreeNode rootOfMaxWay = getNodeOfSemiMaxWay();
        maxWayValues.add(rootOfMaxWay.value);
        addValuesOfSemiMaxWayNodes(maxWayValues, rootOfMaxWay.leftNode);
        addValuesOfSemiMaxWayNodes(maxWayValues, rootOfMaxWay.rightNode);

        int size = maxWayValues.size();
        if (size % 2 == 1) {
            long toDelete = maxWayValues.toArray(new Long[0])[size / 2];
            remove(toDelete);
        }
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

    private void addValuesOfSemiMaxWayNodes(Set<Long> collection, TreeNode current) {
        if (current == null) {
            return;
        }

        collection.add(current.value);
        if (current.leftNode != null && current.height - current.leftNode.height == 1) {
            addValuesOfSemiMaxWayNodes(collection, current.leftNode);
        } else {
            if (current.rightNode != null && current.height - current.rightNode.height == 1) {
                addValuesOfSemiMaxWayNodes(collection, current.rightNode);
            }
        }
    }

    private TreeNode getNodeOfSemiMaxWay() {
        Set<TreeNode> nodesWithMaxMvc = new TreeSet<>();
        getNodeOfSemiMaxWay(nodesWithMaxMvc, root);
        return nodesWithMaxMvc.toArray(new TreeNode[0])[0];
    }

    private void getNodeOfSemiMaxWay(Set<TreeNode> collection, TreeNode current) {
        if (current != null) {
            getNodeOfSemiMaxWay(collection, current.leftNode);
            if (current.msl == maxMsl) {
                collection.add(current);
            }
            getNodeOfSemiMaxWay(collection, current.rightNode);
        }
    }

    private void setHeightAndMslForEachNode(TreeNode node) {
        if (node != null) {
            setHeightAndMslForEachNode(node.leftNode);
            setHeightAndMslForEachNode(node.rightNode);
            handleSettingOfHeightAndMsl(node);
        }
    }

    private void handleSettingOfHeightAndMsl(TreeNode node) {
        if (node == null) return;
        if (node.hasOnlyLeftSon()) {
            long height = node.leftNode.height;
            node.height = height + 1;
            node.msl = height + 1;
            updateMsl(node.msl);
        }
        if (node.hasOnlyRightSon()) {
            long height = node.rightNode.height;
            node.height = height + 1;
            node.msl = height + 1;
            updateMsl(node.msl);
        }
        if (node.hasTwoSons()) {
            long heightOfLeftSon = node.leftNode.height;
            long heightOfRightSon = node.rightNode.height;
            node.height = Math.max(heightOfLeftSon, heightOfRightSon) + 1;
            node.msl = heightOfLeftSon + heightOfRightSon + 2;
            updateMsl(node.msl);
        }
    }

    private void updateMsl(long number) {
        if (maxMsl < number) {
            maxMsl = number;
        }
    }

    private static class TreeNode implements Comparable<TreeNode> {
        private long value;
        private long height;
        private long msl;
        private TreeNode leftNode;
        private TreeNode rightNode;

        TreeNode(long value) {
            this.value = value;
        }

        boolean hasOnlyRightSon() {
            return leftNode == null && rightNode != null;
        }

        boolean hasOnlyLeftSon() {
            return leftNode != null && rightNode == null;
        }

        boolean hasTwoSons() {
            return leftNode != null && rightNode != null;
        }

        @Override
        public int compareTo(TreeNode o) {
            return Long.compare(value, o.value);
        }
    }
}