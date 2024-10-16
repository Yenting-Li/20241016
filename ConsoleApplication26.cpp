// ConsoleApplication26.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <cmath>
using namespace std;

// 表示複數的基本類 Complex
class Complex {
public:
    // 無參數，初始化 real 和 image 為 0
    Complex() : real(0), image(0) {}

    // 有參數建構子
    Complex(float r, float i) : real(r), image(i) {}

    // 設定複數的實部和虛部
    void set(float r, float i) {
        real = r;
        image = i;
    }

    // 取得複數的實部
    float GetReal() const {
        return real;
    }

    // 取得複數的虛部
    float GetImage() const {
        return image;
    }

    // 計算複數的模
    float magnitude() const {
        return sqrt(real * real + image * image);
    }

    // 處理i的係數為-1 or 1 的情況
    void print() const {
        if (image == 1) {
            cout << real << " + i";
        }
        else if (image == -1) {
            cout << real << " - i";
        }
        else if (image < 0) {
            cout << real << " - " << -image << "i";
        }
        else if (image > 0) {
            cout << real << " + " << image << "i";
        }
        else {
            cout << real;
        }
    }

protected:
    // 讓子類可以訪問
    float real;
    float image;
};

// 繼承自 Complex 的子類 ComplexNew，增加了複數運算操作符的重載
class ComplexNew : public Complex {
public:
    // 無參數建構子，呼叫父類的無參數建構子
    ComplexNew() : Complex() {}

    // 有參數建構子，呼叫父類的有參數建構子
    ComplexNew(float r, float i) : Complex(r, i) {}

    // 讓許兩個 ComplexNew 物件進行相加
    ComplexNew operator+(const ComplexNew& other) const {
        // 新的 ComplexNew 物件，其實部和虛部分別是相加的結果
        return ComplexNew(GetReal() + other.GetReal(), GetImage() + other.GetImage());
    }

    //  讓兩個 ComplexNew 物件進行相乘
    ComplexNew operator*(const ComplexNew& other) const {
        // 複數相乘
        float realPart = GetReal() * other.GetReal() - GetImage() * other.GetImage();
        float imagePart = GetReal() * other.GetImage() + GetImage() * other.GetReal();
        return ComplexNew(realPart, imagePart);
    }

    // 計算兩個複數向量
    static ComplexNew dotProduct(ComplexNew* vecA, ComplexNew* vecB, int n) {
        ComplexNew result(0, 0);
        // 一個一個元素相乘並累加結果，得到積
        for (int i = 0; i < n; ++i) {
            result = result + (vecA[i] * vecB[i]);
        }
        return result;
    }
};

int main() {
    int n;
    // 輸入向量長度
    cout << "Enter the length of the vectors: ";
    cin >> n;

    // 動態分配存儲空間
    ComplexNew* vecA = new ComplexNew[n];
    ComplexNew* vecB = new ComplexNew[n];

    // 讓使用者輸入向量 A 的 n 個複數
    cout << "Enter " << n << " complex numbers for vector A (real and imaginary parts):\n";
    for (int i = 0; i < n; ++i) {
        float real, image;
        cout << "A[" << i + 1 << "] real part: ";
        cin >> real;
        cout << "A[" << i + 1 << "] imaginary part: ";
        cin >> image;
        // 將輸入的實部和虛部設置到向量 A 的第 i 個複數
        vecA[i].set(real, image);
    }

    // 讓使用者輸入向量 B 的 n 個複數
    cout << "Enter " << n << " complex numbers for vector B (real and imaginary parts):\n";
    for (int i = 0; i < n; ++i) {
        float real, image;
        cout << "B[" << i + 1 << "] real part: ";
        cin >> real;
        cout << "B[" << i + 1 << "] imaginary part: ";
        cin >> image;
        // 將輸入的實部和虛部設置到向量 B 的第 i 個複數
        vecB[i].set(real, image);
    }

    // 計算元素相加，並顯示結果
    cout << "Element-wise sum: [";
    for (int i = 0; i < n; ++i) {
        ComplexNew sum = vecA[i] + vecB[i];  
        sum.print(); 
        if (i < n - 1) cout << ", ";  
    }
    cout << "]\n";

    // 計算兩個向量的積
    ComplexNew dotProd = ComplexNew::dotProduct(vecA, vecB, n); 
    cout << "Dot product: ";
    dotProd.print();  
    cout << endl;

    // 計算點積的模
    float dotProdMagnitude = dotProd.magnitude();  
    cout << "Magnitude of dot product: " << dotProdMagnitude << endl;

    // 分別計算向量 A 的每個元素的模長
    cout << "Magnitudes of A: [";
    for (int i = 0; i < n; ++i) {
        cout << vecA[i].magnitude();  
        if (i < n - 1) cout << ", ";  
    }
    cout << "]\n";

    // 分別計算向量 B 的每個元素的模長
    cout << "Magnitudes of B: [";
    for (int i = 0; i < n; ++i) {
        cout << vecB[i].magnitude();  
        if (i < n - 1) cout << ", ";  
    }
    cout << "]\n";

    // 釋放動態記憶體
    delete[] vecA;
    delete[] vecB;

    return 0;
}




// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
