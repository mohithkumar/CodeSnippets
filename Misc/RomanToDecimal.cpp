// Program to convert Roman number to Decimal

int RomanToDecimal(const string& romanIp)
{
    static const string roman[] = {"M", "CM", "CD", "D", "C", "XC", "XL", "L", "X", "IX", "IV", "V", "I"};
    static const int decimal[] = { 1000, 900, 400, 500, 100, 90, 40, 50, 10, 9, 4, 5, 1};
    static const size_t size = sizeof(decimal)/sizeof(decimal[0]);

    int value = 0;
    size_t index = 0;

    for(int i = 0; i < size; ++i)
    {
        while(romanIp.substr(index, roman[i].length()) == roman[i])
        {
            value += decimal[i];
            index += roman[i].length();
        }
    }
    return value;
}


int main()
{
    cout << "MCXIV" << ": " << RomanToDecimal("MCXIV") << endl;
    cout << "CCCLIX" << ": " << RomanToDecimal("CCCLIX") << endl;
    cout << "MDCLXVI" << ": " << RomanToDecimal("MDCLXVI") << endl;
}

