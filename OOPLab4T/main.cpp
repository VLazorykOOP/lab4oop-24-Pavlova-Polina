#include <iostream>
#include <stdexcept>

class VectorInt {
private:
    int* data;
    size_t size;
    int codeError;
    static int objectCount;

public:
    VectorInt() : data(new int[1] {0}), size(1), codeError(0) {
        ++objectCount;
    }

    VectorInt(size_t size) : data(new int[size] {0}), size(size), codeError(0) {
        ++objectCount;
    }

    VectorInt(size_t size, int init_value) : data(new int[size]), size(size), codeError(0) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = init_value;
        }
        ++objectCount;
    }

    VectorInt(const VectorInt& other) : data(new int[other.size]), size(other.size), codeError(other.codeError) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        ++objectCount;
    }

    ~VectorInt() {
        delete[] data;
        --objectCount;
    }

    VectorInt& operator=(const VectorInt& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            codeError = other.codeError;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    VectorInt& operator++() {
        for (size_t i = 0; i < size; ++i) {
            ++data[i];
        }
        return *this;
    }

    VectorInt operator++(int) {
        VectorInt temp(*this);
        ++(*this);
        return temp;
    }

    VectorInt& operator--() {
        for (size_t i = 0; i < size; ++i) {
            --data[i];
        }
        return *this;
    }

    VectorInt operator--(int) {
        VectorInt temp(*this);
        --(*this);
        return temp;
    }

    bool operator!() const {
        return size == 0;
    }

    VectorInt operator~() const {
        VectorInt temp(*this);
        for (size_t i = 0; i < size; ++i) {
            temp.data[i] = ~data[i];
        }
        return temp;
    }

    VectorInt operator-() const {
        VectorInt temp(*this);
        for (size_t i = 0; i < size; ++i) {
            temp.data[i] = -data[i];
        }
        return temp;
    }

    VectorInt& operator+=(const VectorInt& other) {
        if (size != other.size) {
            codeError = 1;
            throw std::invalid_argument("Vectors must be the same size for addition");
        }
        for (size_t i = 0; i < size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    VectorInt& operator-=(const VectorInt& other) {
        if (size != other.size) {
            codeError = 1;
            throw std::invalid_argument("Vectors must be the same size for subtraction");
        }
        for (size_t i = 0; i < size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    VectorInt& operator*=(int scalar) {
        for (size_t i = 0; i < size; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    VectorInt& operator/=(int scalar) {
        if (scalar == 0) {
            codeError = 2;
            throw std::invalid_argument("Division by zero");
        }
        for (size_t i = 0; i < size; ++i) {
            data[i] /= scalar;
        }
        return *this;
    }

    VectorInt& operator%=(int scalar) {
        if (scalar == 0) {
            codeError = 2;
            throw std::invalid_argument("Modulo by zero");
        }
        for (size_t i = 0; i < size; ++i) {
            data[i] %= scalar;
        }
        return *this;
    }

    friend VectorInt operator+(const VectorInt& lhs, const VectorInt& rhs) {
        VectorInt temp(lhs);
        temp += rhs;
        return temp;
    }

    friend VectorInt operator-(const VectorInt& lhs, const VectorInt& rhs) {
        VectorInt temp(lhs);
        temp -= rhs;
        return temp;
    }

    friend VectorInt operator*(const VectorInt& vec, int scalar) {
        VectorInt temp(vec);
        temp *= scalar;
        return temp;
    }

    friend VectorInt operator/(const VectorInt& vec, int scalar) {
        VectorInt temp(vec);
        temp /= scalar;
        return temp;
    }

    friend VectorInt operator%(const VectorInt& vec, int scalar) {
        VectorInt temp(vec);
        temp %= scalar;
        return temp;
    }


    friend std::istream& operator>>(std::istream& is, VectorInt& vec) {
        for (size_t i = 0; i < vec.size; ++i) {
            is >> vec.data[i];
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const VectorInt& vec) {
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.data[i] << ' ';
        }
        return os;
    }

    bool operator==(const VectorInt& other) const {
        if (size != other.size) {
            return false;
        }
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const VectorInt& other) const {
        return !(*this == other);
    }

    int& operator[](size_t index) {
        if (index >= size) {
            codeError = 3;
            return data[size - 1];
        }
        return data[index];
    }


    bool operator>(const VectorInt& other) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] <= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(const VectorInt& other) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] < other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const VectorInt& other) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] >= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const VectorInt& other) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>(int value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] <= value) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(int value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] < value) {
                return false;
            }
        }
        return true;
    }

    bool operator<(int value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] >= value) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(int value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] > value) {
                return false;
            }
        }
        return true;
    }

    static int getObjectCount() {
        return objectCount;
    }
};

int VectorInt::objectCount = 0;
#include <iostream>
#include <string>

class Assoc {
    struct Node {
        std::string productName;
        int inventoryNumber;
        Node* next;

        Node(const std::string& prodName, int invNum) : productName(prodName), inventoryNumber(invNum), next(nullptr) {}
    };

    Node* head;
    int errorCode;

public:
    enum ErrorCodes {
        NO_ERROR = 0,
        EMAIL_NOT_FOUND
    };

    Assoc() : head(nullptr), errorCode(NO_ERROR) {}

    ~Assoc() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void createAssociations(const std::string& productName, int inventoryNumber) {
        Node* newNode = new Node(productName, inventoryNumber);
        newNode->next = head;
        head = newNode;
    }

    int getInventoryNumber(const std::string& productName) {
        Node* current = head;
        while (current != nullptr) {
            if (current->productName == productName) {
                errorCode = NO_ERROR;
                return current->inventoryNumber;
            }
            current = current->next;
        }
        errorCode = EMAIL_NOT_FOUND;
        return -1;
    }

    int getErrorCode() const {
        return errorCode;
    }

    friend std::ostream& operator<<(std::ostream& os, const Assoc& assoc) {
        Node* current = assoc.head;
        while (current != nullptr) {
            os << "Product: " << current->productName << ", Inventory Number: " << current->inventoryNumber << std::endl;
            current = current->next;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Assoc& assoc) {
        std::string productName;
        int inventoryNumber;
        while (is >> productName >> inventoryNumber) {
            assoc.createAssociations(productName, inventoryNumber);
        }
        return is;
    }
};

int main() {
    VectorInt v1;
    std::cout << "Vector v1: " << v1 << std::endl;
    VectorInt v2(5);
    std::cout << "Vector v2: " << v2 << std::endl;
    VectorInt v3(3, 10);
    std::cout << "Vector v3: " << v3 << std::endl;
    VectorInt v4 = v3;
    std::cout << "Vector v4: " << v4 << std::endl;
    VectorInt v5;
    v5 = v2;
    std::cout << "Vector v5: " << v5 << std::endl;
    ++v5;
    std::cout << "Vector v5 after ++: " << v5 << std::endl;
    VectorInt v6 = v5++;
    std::cout << "Vector v6 (v5++): " << v6 << std::endl;
    std::cout << "Vector v5 after post-increment: " << v5 << std::endl;
    --v6;
    std::cout << "Vector v6 after --: " << v6 << std::endl;
    VectorInt v7 = v6--;
    std::cout << "Vector v7 (v6--): " << v7 << std::endl;
    std::cout << "Vector v6 after post-decrement: " << v6 << std::endl;
    std::cout << "Negation of v7: " << ~v7 << std::endl;
    std::cout << "Negation of v7: " << -v7 << std::endl;
    VectorInt v8(3, 5);
    std::cout << "v8: " << v8 << std::endl;
    VectorInt v71(3, 8);
    v8 += v71;
    std::cout << "v8 after v8 += v7: " << v8 << std::endl;
    VectorInt v9 = v8 + v3;
    std::cout << "v9 = v8 + v3: " << v9 << std::endl;
    v9 -= v4;
    std::cout << "v9 after v9 -= v4: " << v9 << std::endl;
    VectorInt v10 = v9 * 2;
    std::cout << "v10 = v9 * 2: " << v10 << std::endl;
    v10 /= 2;
    std::cout << "v10 after v10 /= 2: " << v10 << std::endl;
    VectorInt v11 = v9 % 3;
    std::cout << "v11 = v9 % 3: " << v11 << std::endl;
    std::cout << "v9 == v10: " << (v9 == v10) << std::endl;
    std::cout << "v9 != v10: " << (v9 != v10) << std::endl;
    std::cout << "v9[0]: " << v9[0] << std::endl;
    std::cout << "v9[10]: " << v9[10] << std::endl;
    std::cout << "Number of VectorInt objects: " << VectorInt::getObjectCount() << std::endl;
    Assoc inventory;

    inventory.createAssociations("Laptop", 1001);
    inventory.createAssociations("Smartphone", 2002);
    inventory.createAssociations("Tablet", 3003);

    std::cout << "Inventory:\n";
    std::cout << inventory;

    std::cout << "Inventory Number for Laptop: " << inventory.getInventoryNumber("Laptop") << std::endl;
    std::cout << "Inventory Number for Smartphone: " << inventory.getInventoryNumber("Smartphone") << std::endl;
    std::cout << "Inventory Number for Tablet: " << inventory.getInventoryNumber("Tablet") << std::endl;

    return 0;
    return 0;
}

