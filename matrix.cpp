#include<bits/stdc++.h>
using namespace std;

class Matrix{
    private:
        int rowSize,colSize;
        int** matrix;

    public:
        Matrix(): rowSize(0), colSize(0), matrix(nullptr) {}
        Matrix(int size): rowSize(size), colSize(size) {
            matrix = new int*[rowSize];
            for(int i=0; i<rowSize; i++) matrix[i] = new int[colSize];
        }
        Matrix(int row, int col): rowSize(row), colSize(col) {
            matrix = new int*[rowSize];
            for(int i=0; i<rowSize; i++) matrix[i] = new int[colSize];
        }
        Matrix(initializer_list<initializer_list<double>> a):
        rowSize(a.size()), colSize(a.begin()->size()){
                matrix = new int*[rowSize];
                for(int i=0; i<rowSize; i++) matrix[i] = new int[colSize];

                int row=0, col=0;
                for(const auto& rowL : a){
                    for(const auto& elm: rowL){
                        matrix[row][col++] = elm;
                    }
                    row++,col=0;
                }
        }
        Matrix(const Matrix& m):rowSize(m.rowSize), colSize(m.colSize){
            matrix = new int*[rowSize];
            for(int i=0; i<rowSize; i++){
                matrix[i] = new int[colSize];
                for(int j=0; i<colSize; j++) matrix[i][j] = m.matrix[i][j];
            }
        }

        void display() const{
            for(int i=0; i<rowSize; i++){
                for(int j=0; j<colSize; j++){
                    printf("%.3lf ",matrix[i][j]);
                }
                puts("");
            }
        }

        const Matrix& append(const Matrix& m, int axis=0){
            if(axis==0){
                if(rowSize != m.rowSize){
                    throw runtime_error("001");
                }
                else{
                    int newCol = colSize + m.colSize;
                    int** newMat = new int*[rowSize];
                    for(int i=0; i<rowSize; i++){
                        newMat[i] = new int[newCol];

                        for(int j=0; j<colSize; j++){
                            newMat[i][j]=matrix[i][j];
                        }
                        for(int j=colSize; j<newCol; j++){
                            newMat[i][j] = m.matrix[i][j-colSize];
                        }
                    }

                    for(int i=0; i<rowSize; i++){
                        delete[] matrix[i];
                    }
                    delete[] matrix;

                    colSize = newCol;
                    matrix = newMat;

                    return *this;
                }
            }else if(axis==1){
                if(colSize != m.colSize){
                    throw runtime_error("002");
                }
                else{
                    int newRow = rowSize + m.rowSize;
                    int** newMat = new int*[newRow];
                    for(int i=0; i<rowSize; i++){
                        newMat[i] = new int[colSize];
                        for(int j=0; j<colSize; j++){
                            newMat[i][j]=matrix[i][j];
                        }
                    }
                    for(int i=rowSize; i<newRow; i++){
                        newMat[i] = new int[colSize];
                        for(int j=0; j<colSize; j++){
                            newMat[i][j]=m.matrix[i-rowSize][j];
                        }
                    }

                    for(int i=0; i<rowSize; i++){
                        delete[] matrix[i];
                    }
                    delete[] matrix;

                    rowSize = newRow;
                    matrix = newMat;

                    return *this;
                }
            }else{
                throw invalid_argument("003");  
            }
        }

        Matrix operator*(const Matrix& m) const{
            if(colSize != m.rowSize){
                throw runtime_error("004");
            }

            Matrix res(rowSize,m.colSize);
            for(int i=0; i<rowSize; i++){
                for(int j=0; j<m.colSize; j++){
                    for(int k=0; k<colSize; k++){
                        res.matrix[i][j] += matrix[i][k]*m.matrix[k][j];
                    }
                }
            }
            
            return res;
        }

        Matrix operator+(const Matrix& m) const{
            if(rowSize!=m.rowSize || colSize!=m.colSize){
                throw runtime_error("005");
            }

            Matrix res(rowSize,colSize);
            for(int i=0; i<rowSize; i++){
                for(int j=0; j<colSize; j++){
                    res.matrix[i][j]=matrix[i][j]+m.matrix[i][j];
                }
            }
            return res;
        }
        Matrix operator-(const Matrix& m)const{
            if(rowSize!=m.rowSize || colSize!=m.colSize){
                throw runtime_error("005");
            }

            Matrix res(rowSize,colSize);
            for(int i=0; i<rowSize; i++){
                for(int j=0; j<colSize; j++){
                    res.matrix[i][j]=matrix[i][j]-m.matrix[i][j];
                }
            }
            return res;
        }

        Matrix& operator+=(const Matrix& m){
            if(rowSize!=m.rowSize || colSize!=m.colSize){
                throw runtime_error("005");
            }

            for(int i=0; i<rowSize; i++){
                for(int j=0; j<colSize; j++){
                    matrix[i][j]+=m.matrix[i][j];
                }
            }
            return *this;
        }

        Matrix& operator++(){
            for(int i=0; i<rowSize; i++){
                for(int j=0; j<colSize; j++){
                    matrix[i][j]++;
                }
            }
            return *this;
        }
        Matrix& operator--(){
            for(int i=0; i<rowSize; i++){
                for(int j=0; j<colSize; j++){
                    matrix[i][j]--;
                }
            }
            return *this;
        }

        int* operator[](int row) const{
            if(row<0 || row>=rowSize){
                throw out_of_range("006");
            }
            return matrix[row];
        }

        bool operator==(const Matrix& m) const{
            if(rowSize!=m.rowSize || colSize!=m.colSize) return 0;
            for(int i=0; i<rowSize; i++){
                for(int j=0; j<colSize; j++){
                    if(matrix[i][j]!=m.matrix[i][j]) return 0;
                }
            }
            return 1;
        }

        Matrix& operator=(const Matrix& m){
            if(this == &m){
                return *this;
            }

            for(int i=0; i<rowSize; i++){
                delete[] matrix[i];
            }
            delete[] matrix;

            rowSize = m.rowSize;
            colSize = m.colSize;
            matrix = new int*[rowSize];
            for(int i=0; i<rowSize; i++){
                matrix[i] = new int[colSize];
                for(int j=0; j<colSize; j++){
                    matrix[i][j] = m.matrix[i][j];
                }
            }
            return *this;
        }

        // auto operator<=>(const Matrix& m) const{
            
        // }
        
    friend ostream& operator<<(ostream& os, const Matrix& m){
        for(int i=0; i<m.rowSize; i++){
            for(int j=0; j<m.colSize; j++){
                os << m.matrix[i][j]<<' ';
            }
        }
        os << '\n';
        return os;
    }
};

int main(){
    
    return 0;
}