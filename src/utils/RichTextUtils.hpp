#pragma once

#include "../resources/PowerUpDatabaseResource.hpp"

inline RichTextPart T(const std::string& text)
{
    return RichTextPart{text, TextStyle::Normal};
}

inline RichTextPart Good(const std::string& text)
{
    return RichTextPart{text, TextStyle::Good};
}

inline RichTextPart Bad(const std::string& text)
{
    return RichTextPart{text, TextStyle::Bad};
}

inline RichTextPart Muted(const std::string& text)
{
    return RichTextPart{text, TextStyle::Muted};
}

inline RichTextPart GoldText(const std::string& text)
{
    return RichTextPart{text, TextStyle::Gold};
}
