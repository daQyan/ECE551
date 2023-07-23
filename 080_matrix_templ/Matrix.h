#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;
 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = new std::vector<T>*[r];                        //
    for (ssize_t i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(c);
    }
  }

  Matrix(const Matrix & rhs) :  
    numRows(rhs.numRows), 
    numColumns(rhs.numColumns) {
      rows = new std::vector<T>*[rhs.numRows];
      for (ssize_t i = 0; i < numRows; i++) {
        rows[i] = new std::vector<T>(*rhs.rows[i]);
      }
  }

  ~Matrix() {
    for (ssize_t i = 0; i < numRows; ++i) {
      delete rows[i];
    }
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      for (ssize_t i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;    
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = new std::vector<T>*[rhs.numRows];
      for (ssize_t i = 0; i < rhs.numRows; i++) {
        rows[i] = new std::vector<T>(*rhs.rows[i]);         // using copy constructor of Intarray
      }
    }
    return *this;    
  }

  int getRows() const {
    return numRows;
  }
  int getColumns() const {
    return numColumns;
  }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }
  std::vector<T> & operator[](int index){
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }
    if (numColumns != rhs.numColumns) {
      return false;
    }
    for (ssize_t i = 0; i < numRows; ++i) {
      if (*rows[i] != rhs[i]) {  // rhs[i] will return ref of rhs.rows[i]
        return false;
      }    
    }
    return true;  
  }

  Matrix operator+(const Matrix & rhs) const {

    // assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    // IntMatrix ans(numRows, numColumns);
    // for (ssize_t i = 0; i < numRows; ++i)  {
    //   for (ssize_t j = 0; j < numColumns; ++i) {
    //     ans[i][j] = (*this)[i][j] + rhs[i][j];
    //   }    
    // }
    // return ans;

  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  Matrix ans(numRows, numColumns);
  for (ssize_t i = 0; i < numRows; ++i)
    for (ssize_t j = 0; j < numColumns; ++j)
      (*ans.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
  return ans;

  }
};

  template<typename T>
  std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
    s << "[ ";
    for (ssize_t i = 0; i < rhs.getRows(); ++i) {
      s << rhs[i];
      if (i != rhs.getRows() - 1)
        s << ",\n";
    }
    s << " ]";
    return s;
  }
  

  template<typename T>
  std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
    s << "{";
    for (size_t i = 0; i < rhs.size()-1; i++) {
      s << rhs[i] << ",";
    }
    if (rhs.size() != 0) {
      s << rhs[rhs.size()-1];
    }
    s << "}";
    return s;
  }
  

#endif
