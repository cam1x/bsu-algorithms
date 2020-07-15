#include <iostream>

using namespace std;

bool binarySearch(const int *array, int number);

int binarySearchLowerBound(const int *array, int number);

int binarySearchUpperBound(const int *array, int number);

int arrayLength;

int main() {
    cin >> arrayLength;
    int *array = new int[arrayLength];
    for (int i = 0; i < arrayLength; ++i) {
        cin >> array[i];
    }

    int valueNumber;
    cin >> valueNumber;
    for (int i = 0; i < valueNumber; ++i) {
        int value;
        cin >> value;
        cout << ((binarySearch(array, value)) ? 1 : 0) << " " << binarySearchLowerBound(array, value)
             << " " << binarySearchUpperBound(array, value) << endl;
    }
    return 0;
}

bool binarySearch(const int *array, int number) {
    int leftBound = 0;
    int rightBound = arrayLength;

    while (leftBound < rightBound) {
        int middle = (leftBound + rightBound) / 2;
        if (number == array[middle]) {
            return true;
        }
        if (number < array[middle]) {
            rightBound = middle;
        } else {
            leftBound = middle + 1;
        }
    }
    return false;
}

int binarySearchLowerBound(const int *array, int number) {
    int leftBound = 0;
    int rightBound = arrayLength;

    while (leftBound < rightBound) {
        int middle = (leftBound + rightBound) / 2;
        if (number > array[middle]) {
            leftBound = middle + 1;
        } else {
            rightBound = middle;
        }
    }
    return leftBound;
}

int binarySearchUpperBound(const int *array, int number) {
    int leftBound = 0;
    int rightBound = arrayLength;

    while (leftBound < rightBound) {
        int middle = (leftBound + rightBound) / 2;
        if (number < array[middle]) {
            rightBound = middle;
        } else {
            leftBound = middle + 1;
        }
    }
    return rightBound;
}