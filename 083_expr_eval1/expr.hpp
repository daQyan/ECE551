
#include <sstream>
#include <string>

class Expression {
  public:
    Expression() {}
    virtual std::string toString() const = 0;
    virtual ~Expression() {}
};

class NumExpression : public Expression {
  private:
    long num;
  public:
    NumExpression(long n) : num(n) {}
    virtual std::string toString() const {
      std::stringstream str;
      str << num;
      return str.str();
    }
    virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
  private:
    Expression * lhs;
    Expression * rhs;
  public:
    PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
    virtual std::string toString() const {
      std::stringstream str;
      str << "(" << lhs->toString() << "+" << rhs->toString() << ")";
      return str.str();
    }
    ~PlusExpression() {
      delete rhs;
      delete lhs;
    }
};