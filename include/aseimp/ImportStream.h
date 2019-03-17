#pragma once

#include <string>
#include <vector>

namespace aseimp
{

class ImportStream
{
public:
    ImportStream(const std::string& data);

    bool        Bool();
    float       Float();
    int         Int32();
    std::string String();

    bool IsValid() const { return m_ptr >= 0 && m_ptr < static_cast<int>(m_tokens.size()); }

private:
    std::vector<std::string> m_tokens;
    int m_ptr = -1;

}; // ImportStream

}