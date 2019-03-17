#pragma once

#include <string>

namespace aseimp
{

enum class VarType
{
    Bool,
    Int,
    Float,
    String,
};

class Variant
{
public:
    explicit Variant(bool b);
    explicit Variant(int  i);
    explicit Variant(float f);
    explicit Variant(const std::string& str);
    Variant(const Variant& var);
    Variant& operator = (const Variant& var);
    ~Variant();

    VarType type;

    union
    {
        bool  b;
        int   i;
        float f;
        char* c = nullptr;
    };

}; // Variant

}