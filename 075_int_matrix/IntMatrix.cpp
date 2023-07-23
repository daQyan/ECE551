#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[numRows]; // r
  for (ssize_t i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) : 
  numRows(rhs.numRows), 
  numColumns(rhs.numColumns) {
    rows = new IntArray*[rhs.numRows];
    for (ssize_t i = 0; i < rhs.numRows; i++) {
      rows[i] = new IntArray(*rhs.rows[i]);         // using copy constructor of Intarray
    } 
}
IntMatrix::~IntMatrix() {
  for (ssize_t i = 0; i < numRows; ++i) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (ssize_t i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;    
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray*[rhs.numRows];
    for (ssize_t i = 0; i < rhs.numRows; i++) {
      rows[i] = new IntArray(*rhs.rows[i]);         // using copy constructor of Intarray
    }
  }
  return *this;    
}

int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {

  // assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  // IntMatrix ans(numRows, numColumns);
  // for (ssize_t i = 0; i < numRows; ++i)  {
  //   for (ssize_t j = 0; j < numColumns; ++i) {
  //     ans[i][j] = (*this)[i][j] + rhs[i][j];
  //   }    
  // }
  // return ans;

  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  IntMatrix ans(numRows, numColumns);
  for (ssize_t i = 0; i < numRows; ++i)
    for (ssize_t j = 0; j < numColumns; ++j)
      (*ans.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
  return ans;

}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (ssize_t i = 0; i < rhs.getRows(); ++i) {
    s << rhs[i];
    if (i != rhs.getRows() - 1)
      s << ",\n";
  }
  s << " ]";
  return s;
}
