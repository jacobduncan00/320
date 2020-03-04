#include <iostream>
#include <iomanip>
#include <math.h>
#include "Matrix.h"

#define RESET "\033[0m"
#define WHITE "\033[37m" 
#define PURPLE "\033[35m"
#define RED "\033[31m" 

namespace counter{
    int count = 0;
}

Matrix::Matrix(){
    rows = 0;
    cols = 0;
}

Matrix::Matrix(long int row, long int col){
  if (row <= 0 || col <= 0){
    std::cout << "Invalid Matrix Size" << std::endl;
    exit(1);
  } 
  rows = row;
  cols = col;
  mat = new double*[rows];
  srand(time(NULL));
  for(long int i = 0; i < rows; i++){
    mat[i] = new double[cols];
  }
}


Matrix::Matrix(const Matrix& m){
  rows = m.rows;
  cols = m.cols;
  double** arr = new double*[rows];
  for(long int i = 0; i < rows; i++){
    arr[i] = new double[cols];
  }
  mat = arr;
  for(long int i = 0; i < m.rows; i++){
    for(long int j = 0; j < cols; j++){
      mat[i][j] = m.mat[i][j];
    }
  }
}

Matrix::~Matrix(){
  for(long int i = 0; i < rows; i++){
    delete[] mat[i];
  }
  delete[] mat;
}

Matrix Matrix::fillMatrix(){
  Matrix A = Matrix(rows, cols);
  A.mat[0][0] = 1.0;
	A.mat[0][1] = 0.0;
	A.mat[0][2] = 0.0;
	
	A.mat[1][0] = 0.0;
	A.mat[1][1] = 2.0;
	A.mat[1][2] = 0.0;
	
	A.mat[2][0] = 0.0;
	A.mat[2][1] = 0.0;
	A.mat[2][2] = 3.0;

  return A;
}

void Matrix::insert(long int i, long int j, double num){
  mat[i][j] = num;
}

double Matrix::getVal(int i, int j){
  return mat[i][j];
}

void Matrix::determinant(){
  int det = 0;
  if(rows != cols){
    std::cout << "Matrix is not a square, cannot be invertible" << std::endl;
  }
  if(rows == 2 && cols == 2){
    det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    if(det == 0){
      std::cout << "Matrix is not invertible.\n";
    }
    else{
      std::cout << "Matrix is invertible.\n";
    }
  }
  else if (rows == 3 && cols == 3){
    det = (mat[0][0] * mat[1][1] * mat[2][2]
			  + mat[0][1]  * mat[1][2] * mat[2][0]
		  	+ mat[0][2]  * mat[1][0] * mat[2][1])
		  	- (mat[0][2] * mat[1][1] * mat[2][0]
		  	+  mat[0][0] * mat[1][2] * mat[2][1]
		  	+  mat[0][1] * mat[1][0] * mat[2][2]);
      
    if(det == 0){
      std::cout << "Matrix is not invertible.\n";
    }
    else{
      std::cout << "Matrix is invertible.\n";
    }
  }
  else{
    int count;
    for(long int i = 0; i < rows; i++){
      for (long int j = 0; j < cols; j++){
        det+=mat[i][j];
      }
      if(det == 0){
        std::cout << "Matrix is not invertible.\n";
      }
      else{
        count++;
      }
    }
    if(count == rows - 1){
      std::cout << "Matrix is invertible.\n";
    }
  }
}

bool Matrix::isSymmetric(){
  Matrix a = *this;
  Matrix b = this->transpose();
  for(long int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(a.mat[i][j] != b.mat[i][j]){ // if the original is not the same as the tranpose, shows symmetry
        return false;
      }
    }
  }
  return true;
}

Matrix Matrix::padMatrix(int d){
	int size = 0;
  while(log2(d + size) - (int)log2(d + size) != 0){
    size++;
  }
  Matrix rtn(d+size, d+size);
  Matrix id(size, size);
  id.identityMatrix();
  for(long int i = 0; i < rtn.rows; i++){
    for(long int j = 0; j < rtn.cols; j++){
      if(i < d && j < d){
        rtn.mat[i][j] = mat[i][j];
      }
      if(i >= d && j >= d){
        rtn.mat[i][j] = id.mat[i-d][j-d];
      }
      if((i >= d && j < d) || (i < d && j >= d)){
        rtn.mat[i][j] = 0;
      }
    }
  }
  return rtn;
}

Matrix Matrix::inverse(){
  // Assuming that "this" is a square (n x n) matrix and is symmetric

  if(rows != cols){
    throw "Not a square matrix!";
  }

  if(rows == 1 && cols == 1){
    if(mat[0][0] != 0){
      mat[0][0] = 1/mat[0][0];
    }
    return *this;
  }

  int ogRow = rows;
  if(log2(rows) - (int)log2(rows) != 0){ // check to see if Matrix is a 2^n x 2^n
    if(rows == 1){
      Matrix rtn2(1,1);
      rtn2.mat[0][0] = mat[0][0];
      return rtn2;
    }
  }
  Matrix curr = padMatrix(rows);
  Matrix rtn = curr.inverse();


  long int row = rows;
  long int col = cols;

  padMatrix(row);

	long int row2 = rows/2;
	long int col2 = cols/2;

	Matrix B(row2, col2); // n/2 matrix
	Matrix C(row2, col2); // n/2 matrix
	Matrix CT(row2, col2); // n/2 matrix
	Matrix D(row2, col2); // n/2 matrix

	for(long int i = 0; i < rows; i++){
		for(long int j = 0; j < cols; j++){

			if(i < row2 && j < col2){ //top left
				B.mat[i][j] = mat[i][j];
      }
			else if(i < row2 && j >= col2){ //top right
				CT.mat[i][j - col2] = mat[i][j];
      }
			else if(i >= row2 && j < col2){ // bottom left
				C.mat[i - row2][j] = mat[i][j];
      }
			else if(i >= row2 && j >= col2){ //bottom right
				D.mat[i - row2][j - col2] = mat[i][j];
      }

		}
  }

	Matrix BI = (B.inverse()); // recursively call this function
	Matrix W = (C) * (BI);
  Matrix WT = W.transpose();
	Matrix X = W * CT;
	Matrix S = D - X;
	Matrix V = (S.inverse());
	Matrix Y = V * (W);
	Matrix YT = Y.transpose();
	Matrix T = (YT * -1);
	Matrix U = (Y * -1);
	Matrix Z = (WT) * (Y);
	Matrix R = BI + Z;

  for(long int i = 0; i < rows; i++){
		delete[] mat[i];
  }
	delete[] mat;

  rows = row;
  cols = col;

  mat = new double*[rows];
	for(long int i = 0; i < rows; i++){
		mat[i] = new double[cols];
	}

  for(long int i = 0; i < rows; i++){
		for(long int j = 0; j < cols; j++){

			if(i < row2 && j < col2){ //top left
				mat[i][j] = R.mat[i][j];
      }
			else if(i < row2 && j >= col2){ //top right
				mat[i][j] = T.mat[i][j-col2];
      }
			else if(i >= row2 && j < col2){ // bottom left
				mat[i][j] = U.mat[i-row2][j];
      }
			else if(i >= row2 && j >= col2){ //bottom right
				mat[i][j] = V.mat[i-row2][j-col2];
      }

		}
  }
	return *this;
}

void Matrix::twoDRegression(std::string fileName){
  std::ifstream infile(fileName);
  if(!infile.is_open()){
      	std::cout << "File Opening Error.\n";
      	exit (1);
  }
  int datasize;
  if(fileName == "points100.dat"){
    datasize = 100;
  }
  else if(fileName == "points500.dat"){
    datasize = 500;
  }
  else if(fileName == "points1000.dat"){
    datasize = 1000;
  }
  else if(fileName == "points5000.dat"){
    datasize = 5000;
  }
  else if(fileName == "points10000.dat"){
    datasize = 10000;
  }
  else if(fileName == "points50000.dat"){
    datasize = 50000;
  }
  else if(fileName == "points100000.dat"){
    datasize = 100000;
  }
  else{
    std::cout << "Data Size could not be calculated!" << std::endl;
    return;
  }
  double c1, c2;
  Matrix *A = new Matrix(datasize, 2);
  Matrix *b = new Matrix(datasize, 1);
  for(long int i = 0; i < datasize; i++){
    infile >> c1;
    //std::cout << "1st Value: " << c1 << std::endl;
    infile >> c2;
    //std::cout << "2nd Value: " << c2 << std::endl;
    A->insert(i, 0, c1);
    b->insert(i, 0, c2);
    A->insert(i, 1, 1.0);
  }
  infile.close();
  Matrix AT = (*A).transpose();
  Matrix Beta = (((AT * *A).inverse() * AT) * *b);
  std::cout << "[2D] Aβ = [A]*[β]=[x] = b:" << std::endl;
  std::cout << Beta << std::endl; // Prints regression line.
}


void Matrix::identityMatrix(){
  for(long int i = 0; i < this->rows; i++){
    this->mat[i][i] = 1;
  }
}

void Matrix::diagonalMatrix(){
  srand(time(NULL));
  for(long int i = 0; i < this->rows; i++){
    this->mat[i][i] = 999;
  }
}

void Matrix::triangularMatrix(bool up){
  srand(time(NULL));
  if(up){
    for(long int i = 0; i < this->rows; i++){
      for(long int j = 0; j < this->rows; j++){
        if(i < j){
          this->mat[i][j] = 999;
        }
        else{
          this->mat[i][j] = 0;
        }
      }
    }
  }
  else{
    for(long int i = 0; i < this->rows; i++){
      for(long int j = 0; j < this->rows; j++){
        if(i > j){
          this->mat[i][j] = 999;
        }
        else{
          this->mat[i][j] = 0;
        }
      }
    }
  }
}

void Matrix::printMatrix(){
    for(long int i = 0; i < this->rows; i++){
        if(i != 0)
            std::cout << std::endl;
        for(long int j = 0; j < this->cols; j++){
              std::cout << std::setw(5) << this->mat[i][j] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

Matrix& Matrix::operator=(const Matrix& m){
  if(this == &m){ // when matrices are already the same
    return *this;
  }
  for(long int i = 0; i < rows; i++){
    delete[] mat[i];
  }
  delete[] mat;
  mat = new double*[m.rows];
  for(long int i = 0; i < m.rows; i++){
    mat[i] = new double[m.cols];
  }
  rows = m.rows;
  cols = m.cols;
  for(long int i = 0; i < rows; i++){
    for(long int j = 0; j < cols; j++){
      mat[i][j] = m.mat[i][j];
    }
  }
  counter::count++;
  return *this;
}

std::ostream& operator<< (std::ostream& os, const Matrix& matrix){
    for(long int i = 0; i < matrix.rows; i++){
        for(long int k = 0; k < matrix.cols; k++){
            os << matrix.mat[i][k] << " ";
        }
        std::cout << "\n";
    }
    return os;
}

Matrix operator+ (const Matrix& matrixa, const Matrix& matrixb){
	if(matrixa.rows != matrixb.rows || matrixa.cols != matrixb.cols){
		std::cout << "Invalid matrix size combination.";
		exit (1);
	}

	Matrix matrixc(matrixa.rows, matrixa.cols);
	for(long int i = 0; i < matrixa.rows; i++){
		for(long int k = 0; k < matrixa.cols; k++){
			matrixc.mat[i][k] = matrixa.mat[i][k] + matrixb.mat[i][k];
    }
  }
  counter::count++;
	return matrixc;
}

Matrix operator- (const Matrix& matrixa, const Matrix& matrixb){
	if(matrixa.rows!= matrixb.rows|| matrixa.cols != matrixb.cols){
		std::cout << "Invalid matrix size combination.";
		exit (1);
	}
	Matrix matrixc(matrixa.rows, matrixa.cols);
	for(long int i = 0; i < matrixa.rows;i++){
		for(long int k = 0; k < matrixa.cols; k++){
			matrixc.mat[i][k] = matrixa.mat[i][k] - matrixb.mat[i][k];
    }
  }
  counter::count++;
	return matrixc;
}

Matrix operator* (const Matrix& matrixa, const Matrix& matrixb){
	if(matrixa.cols != matrixb.rows){
		std::cout << "Invalid matrix size combination.";
		exit(1);
	}
	Matrix matrixc(matrixa.rows, matrixb.cols);
	for(long int i = 0; i < matrixa.rows; i++){
		for(long int j = 0; j < matrixb.cols; j++){
      double sum = 0.0;
      for(long int l = 0; l < matrixa.cols; l++){
        sum += matrixa.mat[i][l] * matrixb.mat[l][j];
      }
      matrixc.mat[i][j] = sum;
    }
  }
  counter::count++;
	return matrixc;
}

Matrix operator* (const Matrix& matrixa, const double& c){ // Scalar Mult.
	Matrix matrixb(matrixa.rows, matrixa.cols);
	for(long int i = 0; i < matrixa.rows; i++){
		for(long int k = 0; k < matrixa.cols; k++){
			matrixb.mat[i][k] = (matrixa.mat[i][k] * c);
    }
  }
  counter::count++;
	return matrixb;
}

Matrix Matrix::transpose(){ // Tranpose function
	Matrix transpose(cols, rows);
	for(long int i = 0; i < rows; i++){
		for(long int j = 0; j < cols; j++){
			transpose.mat[j][i] = mat[i][j];
    }
  }
  counter::count++;
	return transpose;
}