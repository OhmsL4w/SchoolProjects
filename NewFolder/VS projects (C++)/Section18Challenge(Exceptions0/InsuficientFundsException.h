#ifndef __INSUFICIENT_FUNDS_EXCEPTION_H__
#define __INSUFICIENT_FUNDS_EXCEPTION_H__

class InsuficientFundsException : public std:: exception{

public:
    InsuficientFundsException() noexcept = default;
    ~InsuficientFundsException() = default;
    virtual const char* what() const noexcept {
        return "Insufficient Funds exception";
    }

};

#endif // __INSUFFICIENT_FUNDS_EXCEPTION_H__
