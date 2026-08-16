#pragma once

#include <algorithm>
#include <cstdint>
#include <string>

using ScoreValue = __int128_t;
using UnsignedScoreValue = __uint128_t;

static UnsignedScoreValue AbsScoreValue(ScoreValue value)
{
    if(value >= 0)
    {
        return static_cast<UnsignedScoreValue>(value);
    }

    // Avoid overflow on the minimum negative value.
    return static_cast<UnsignedScoreValue>(-(value + 1)) + 1;
}

static std::string ScoreToDecimalString(ScoreValue value)
{
    bool negative = value < 0;

    UnsignedScoreValue number =
        AbsScoreValue(value);

    if(number == 0)
    {
        return "0";
    }

    std::string result;

    while(number > 0)
    {
        int digit =
            static_cast<int>(number % 10);

        result.push_back(
            static_cast<char>('0' + digit)
        );

        number /= 10;
    }

    if(negative)
    {
        result.push_back('-');
    }

    std::reverse(
        result.begin(),
        result.end()
    );

    return result;
}

static std::string AddCommasToIntegerString(const std::string& value)
{
    bool negative =
        !value.empty() && value[0] == '-';

    std::size_t start =
        negative ? 1 : 0;

    std::string result;

    if(negative)
    {
        result.push_back('-');
    }

    int digitsBeforeComma =
        static_cast<int>((value.size() - start) % 3);

    if(digitsBeforeComma == 0)
    {
        digitsBeforeComma = 3;
    }

    int digitCount = 0;

    for(std::size_t i = start; i < value.size(); ++i)
    {
        if(digitCount > 0 &&
           digitCount % 3 == digitsBeforeComma)
        {
            result.push_back('.');
        }

        result.push_back(value[i]);
        digitCount++;
    }

    return result;
}

static std::string FormatScientificScoreString(const std::string& decimalString)
{
    bool negative =
        !decimalString.empty() && decimalString[0] == '-';

    std::size_t start =
        negative ? 1 : 0;

    std::string digits =
        decimalString.substr(start);

    int exponent =
        static_cast<int>(digits.size()) - 1;

    // We want 4 significant digits:
    // 123456789012 -> 1.235e11
    int mantissaInt = 0;

    for(int i = 0; i < 4; ++i)
    {
        mantissaInt *= 10;

        if(i < static_cast<int>(digits.size()))
        {
            mantissaInt += digits[i] - '0';
        }
    }

    // Round using the 5th significant digit.
    if(digits.size() > 4 && digits[4] >= '5')
    {
        mantissaInt++;
    }

    // Example:
    // 999999999999 -> 10000 after rounding.
    // Convert it to 1.000e12.
    if(mantissaInt >= 10000)
    {
        mantissaInt = 1000;
        exponent++;
    }

    int whole =
        mantissaInt / 1000;

    int fraction =
        mantissaInt % 1000;

    std::string result;

    if(negative)
    {
        result += "-";
    }

    result += std::to_string(whole);
    result += ".";

    if(fraction < 100)
    {
        result += "0";
    }

    if(fraction < 10)
    {
        result += "0";
    }

    result += std::to_string(fraction);
    result += "e";
    result += std::to_string(exponent);

    return result;
}

static std::string FormatScore(ScoreValue value)
{
    constexpr ScoreValue eSwitchPoint =
        static_cast<ScoreValue>(100000000000LL);

    std::string decimalString =
        ScoreToDecimalString(value);

    ScoreValue absValue =
        value < 0 ? -value : value;

    if(absValue >= eSwitchPoint)
    {
        return FormatScientificScoreString(decimalString);
    }

    return AddCommasToIntegerString(decimalString);
}