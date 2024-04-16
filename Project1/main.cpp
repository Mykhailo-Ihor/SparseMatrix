#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

template <typename T>
class SparseMatrix {
private:
    struct Element {
        int row;
        int col;
        T value;
    };

    int rows;
    int cols;
    std::vector<Element> elements;
    void removeZeros() {
        auto it = elements.begin();
        while (it != elements.end()) {
            if (it->value == T()) {
                it = elements.erase(it);
            }
            else {
                ++it;
            }
        }
    }

public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {}

    void addElement(int row, int col, T value) 
    {
        if (row >= 1 && row <= rows && col >= 1 && col <= cols) {
            Element e = { row, col, value };
            elements.push_back(e);
        }
        else {
            std::cout << "Invalid row or column index." << std::endl;
        }
    }

    SparseMatrix<T> operator+(const SparseMatrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cout << "Matrices dimensions must match." << std::endl;
            return *this;
        }

        SparseMatrix<T> result(rows, cols);

        for (const auto& e : elements) 
        {
            result.addElement(e.row, e.col, e.value + other.getValueAt(e.row,e.col));
        }
        for (const auto& e : other.elements)
        {
            result.addElement(e.row, e.col, e.value + getValueAt(e.row, e.col));
        }
        result.removeZeros();

        return result;
    }
    SparseMatrix operator-(const SparseMatrix<T>& other) const {
        SparseMatrix<T> result = this->operator+(other * -1);
		return result;
	}

    void print(std::ostream& os = std::cout) const {
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                T value = getValueAt(i, j);
                os << value << "\t";
            }
            os << std::endl;
        }
    }

    T getValueAt(int row, int col) const {
        for (const auto& e : elements) {
            if (e.row == row && e.col == col) {
                return e.value;
            }
        }
        return T();
    }

    SparseMatrix<T> operator*(const SparseMatrix<T>& other) const {
        if (cols != other.rows) {
            std::cout << "Number of columns in the first matrix must match number of rows in the second matrix." << std::endl;
            return *this;
        }

        SparseMatrix<T> result(rows, other.cols);

        std::unordered_map<int, std::vector<std::pair<int, T>>> colsOfOther;
        for (const auto& e : other.elements) {
            colsOfOther[e.col].push_back({ e.row, e.value });
        }

        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= other.cols; ++j) {
                T value = T();

                for (int k = 1; k <= cols; ++k) {
                    T a = getValueAt(i, k);

                    if (colsOfOther.find(j) != colsOfOther.end()) {
                        for (const auto& pair : colsOfOther[j]) {
                            if (pair.first == k) {
                                value += a * pair.second;
                                break;
                            }
                        }
                    }
                }

                if (value != T()) {
                    result.addElement(i, j, value);
                }
            }
        }

        return result;
    }
    SparseMatrix<T> operator*(int val) const {
		SparseMatrix<T> result(rows, cols);
        for (const auto& e : elements) {
			result.addElement(e.row, e.col, e.value * val);
		}
		return result;
	}
};

int main() {
    SparseMatrix<int> matrix1(3, 3);
    matrix1.addElement(1, 1, 1);
    matrix1.addElement(1, 2, 1);
    matrix1.addElement(2, 2, 2);
    matrix1.addElement(3, 3, 3);
    std::cout << "Matrix1:" << std::endl;
    matrix1.print();
    std::cout << std::endl;
    SparseMatrix<int> matrix2(3, 3);
    matrix2.addElement(1, 1, 4);
    matrix2.addElement(2, 2, 5);
    matrix2.addElement(3, 2, 6);
    std::cout << "Matrix2:" << std::endl;
    matrix2.print();
    std::cout << std::endl;
    SparseMatrix<int> sum = matrix1 + matrix2;
    std::cout << "Sum of matrices:" << std::endl;
    sum.print();
    std::cout << std::endl;
    SparseMatrix<int> matrix3 = matrix1 * matrix2;
    std::cout << "Product of matrices:" << std::endl;
    matrix3.print();
    std::cout << std::endl;
    std::cout << "Matrix1 * 2:" << std::endl;
    matrix3 = matrix1 * 2;
    matrix3.print();
    std::cout << std::endl;
    std::cout << "Matrix2 - Matrix1:" << std::endl;
    matrix3 = matrix2 - matrix1;
    matrix3.print();
    return 0;
}
