#include "Account.h"

const std::string BLOCKED_STATUS="blocked";

Account::Account(const std::string& id,const std::string& status):id(id),status(status){}

bool Account::isBlocked() const{
    return status==BLOCKED_STATUS;
}