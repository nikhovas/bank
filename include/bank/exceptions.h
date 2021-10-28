#pragma once
#include <exception>


class ObjectDoesNotExists : public std::exception {
public:
    const char* what() const throw() {
        return "Object does not exists";
    }
};


class BadDataSourceForObject : public std::exception {
public:
    const char* what() const throw() {
        return "Bad data source for object";
    }
};


class TryCreateTransactionForUnverifiedClient : public std::exception {
public:
    const char* what() const throw() {
        return "Bad data source for object";
    }
};


class BadNameOrSurnameForClient : public std::exception {
public:
    const char* what() const throw() {
        return "Bad data source for object";
    }
};

class TryToPerformBannedOperation : public std::exception {
public:
    const char* what() const throw() {
        return "Bad data source for object";
    }
};