
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

class OprExpression : public Expression {
  private:
    char op;
    Expression * lhs;
    Expression * rhs;
    

  public:
    OprExpression(char op, Expression * lhs, Expression * rhs) : op(op), lhs(lhs), rhs(rhs) {}
    virtual std::string toString() const {
      std::stringstream str;
      str << "(" << lhs->toString() << op << rhs->toString() << ")";
      return str.str();
    }
    ~OprExpression() {
      delete rhs;
      delete lhs;
    }
};

class PlusExpression : public OprExpression {
  public:
    PlusExpression(Expression * lhs, Expression * rhs) : OprExpression('+', lhs, rhs) {}    // using opr's contructor
};

class MinusExpression : public OprExpression {
  public:
    MinusExpression(Expression * lhs, Expression * rhs) : OprExpression('-', lhs, rhs) {}    // using opr's contructor
};

class TimesExpression : public OprExpression {
  public:
    TimesExpression(Expression * lhs, Expression * rhs) : OprExpression('*', lhs, rhs) {}    // using opr's contructor
};

class DivExpression : public OprExpression {
  public:
    DivExpression(Expression * lhs, Expression * rhs) : OprExpression('/', lhs, rhs) {}    // using opr's contructor
};