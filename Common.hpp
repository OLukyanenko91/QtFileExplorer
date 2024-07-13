#pragma once

#include <iostream>
#include <QObject>


namespace NCommon
{
    class CException : public std::exception
    {
    public:
        CException(const char* message) : mMessage(message)
        {};

    public:
        const char* what() { return mMessage; }

    private:
        const char* mMessage;
    };
}
