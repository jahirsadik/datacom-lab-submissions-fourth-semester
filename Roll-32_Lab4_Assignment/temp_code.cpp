#include <bits/stdc++.h>
using namespace std;
string HDB3OutputString, HDB3InputString;

void HDB3Encoding()
{
    string fourZeros = "0000";
    int lastSignalValue = 1, tot_one = 0, error = 0; // 0-> no error. // initially positive and even
    cout << "Chose if last level was (0) Positive, (1) Negative. For HDB3 Encoding." << endl;
    cin >> lastSignalValue;
    if (lastSignalValue == 0)
    {
        cout << "Assuming that last level was Positive." << endl;
        lastSignalValue = 1;
    }
    else
    {
        cout << "Assuming that last level was Negative." << endl;
        lastSignalValue = -1;
    }
    cout << "Chose if initially the number of non-zero was (0) Even, (1) Odd. For HDB3 Encoding." << endl;
    cin >> tot_one;
    if (!tot_one)
    {
        cout << "Assuming that initially the number of non-zero was Even\n";
    }
    else
    {
        cout << "Assuming that initially the number of non-zero was Odd\n";
        tot_one = 1;
    }
    size_t input_length = HDB3InputString.size();
    int zeroCount = count(HDB3InputString.begin(), HDB3InputString.end(), '0');
    int oneCount = count(HDB3InputString.begin(), HDB3InputString.end(), '1');
    if ((zeroCount + oneCount) != (input_length))
    {
        input_length = -1;
        error = 1;
        HDB3OutputString = "Error in encoding. Only 0's and 1's are allowed\n";
        return;
    }

    for (size_t i = 0; i < input_length;)
    {
        if (HDB3InputString[i] == '1') // bit is 1
        {
            tot_one += 1;
            if (lastSignalValue == 1)
            {
                lastSignalValue = -1;
                HDB3OutputString += "-5V, ";
            }
            else
            {
                lastSignalValue = 1;
                HDB3OutputString += "+5V, ";
            }
            i++;
        }
        else
        {
            if ((i + 4 <= input_length) and (HDB3InputString.substr(i, 4) == fourZeros))
            {
                if ((tot_one % 2) == 0) // B00V
                {
                    tot_one += 2;
                    if (lastSignalValue == 1)
                    {
                        HDB3OutputString += "-5V, 0V, 0V, -5V, ";
                        lastSignalValue = -1;
                    }
                    else
                    {
                        HDB3OutputString += "+5V, 0V, 0V, +5V, ";
                        lastSignalValue = 1;
                    }
                }
                else // 000V
                {
                    tot_one += 1;
                    if (lastSignalValue == 1)
                    {
                        HDB3OutputString += "0V, 0V, 0V, +5V, ";
                    }
                    else
                    {
                        HDB3OutputString += "0V, 0V, 0V, -5V, ";
                    }
                }
                i += 4;
            }
            else
            {
                HDB3OutputString += "0V, ";
                i++;
            }
        }
    }
}

void HDB3Decoding()
{
    int lastSignalValue = -1, tot_one = 0, error = 0; // 0-> no error. // initially positive and even
    // cout << "Chose if last level was (0) Positive, (1) Negative. For HDB3 Decoding." << endl;
    // cin >> lastSignalValue;
    // if (lastSignalValue == 0)
    // {
    //     cout << "Assuming that last level was Positive." << endl;
    //     lastSignalValue = 1;
    // }
    // else
    // {
    //     cout << "Assuming that last level was Negative." << endl;
    //     lastSignalValue = -1;
    // }
    // cout << "Chose if initially the number of non-zero was (0) Even, (1) Odd. For HDB3 Decoding." << endl;
    // cin >> tot_one;
    // if (!tot_one)
    // {
    //     cout << "Assuming that initially the number of non-zero was Even\n";
    // }
    // else
    // {
    //     cout << "Assuming that initially the number of non-zero was Odd\n";
    //     tot_one = 1;
    // }
    size_t input_length = HDB3InputString.size();
    vector<int> decodingInput;
    for (size_t i = 0; i < input_length - 1; i++)
    {
        if (HDB3InputString[i] == ' ' or HDB3InputString[i] == ',' or HDB3InputString[i] == 'V' or HDB3InputString[i] == 'v' or HDB3InputString[i] == '5')
        {
            continue;
        }
        if (HDB3InputString[i] == '+' and HDB3InputString[i + 1] == '5')
        {
            decodingInput.push_back(5);
        }
        else if (HDB3InputString[i] == '-' and HDB3InputString[i + 1] == '5')
        {
            decodingInput.push_back(-5);
        }
        else if (HDB3InputString[i] == '0')
        {
            decodingInput.push_back(0);
        }
        else
        {
            cout << "Invalid Input for HDB3 decoding. Invalid Input was ->(" << HDB3InputString[i] << ")\n";
            HDB3OutputString = "Error in input.\n";
            return;
        }
    }
    for (int i = 0; i < decodingInput.size(); i++)
        cout << "sex: " << decodingInput[i] << endl;
    size_t decodingVectorSize = decodingInput.size();
    // int zeroCount = count(HDB3InputString.begin(), HDB3InputString.end(), '0');
    // int fiveCount = count(HDB3InputString.begin(), HDB3InputString.end(), '5');
    // if (decodingVectorSize != (zeroCount + fiveCount))
    // {
    //     printf("Input voltages weren't correct!\n");
    // }
    // checks
    int cur_number_of_zeros = 0;
    for (size_t i = 0; i < decodingVectorSize; i++)
    {
        printf("Dhuksi %d: %d\n", i, decodingInput[i]);
        if (decodingInput[i] == 0)
        {
            cur_number_of_zeros++;
            if (cur_number_of_zeros == 4)
            {
                // HDB3 CANNOT HAVE FOUR CONSECUTIVE 0 Volts
                printf("HDB3 CANNOT HAVE FOUR CONSECUTIVE 0 Volts\n");
                HDB3OutputString += "HDB3 CANNOT HAVE FOUR CONSECUTIVE 0 Volts\n";
                return;
            }
            HDB3OutputString += "0";
        }
        else if (decodingInput[i] == 5 or decodingInput[i] == -5)
        {
            cur_number_of_zeros = 0;
            // violation not found
            if (lastSignalValue == 1 and decodingInput[i] == -5)
            {
                lastSignalValue = -1;
                tot_one += 1;
                HDB3OutputString += "1";
            }
            else if (lastSignalValue == -1 and decodingInput[i] == 5)
            {
                lastSignalValue = 1;
                tot_one += 1;
                HDB3OutputString += "1";
            }
            // any violations found
            else if ((lastSignalValue == 1 and decodingInput[i] == 5) or (lastSignalValue == -1 and decodingInput[i] == -5))
            {
                tot_one += 1; // including the violation, it must be even
                if ((tot_one % 2) != 0)
                {
                    // INVALID SEQUENCE
                    printf("INVALID VIOLATION FOUND at i = %d!(ODD)\n", i);
                    HDB3OutputString = "INVALID VIOLATION FOUND (ODD)!";
                    return;
                }
                // check if i < 3 for any violation, which is impossible
                if (i < 3)
                {
                    // INVALID SEQUENCE
                    printf("INVALID VIOLATION FOUND at i = %d!\n", i);
                    HDB3OutputString = "INVALID VIOLATION FOUND!";
                    return;
                }
                // BOOV found
                if ((decodingInput[i] == 5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == 5) or
                    (decodingInput[i] == -5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == -5))
                {
                    printf("BOOV found!\n");
                    size_t actualLength = HDB3OutputString.size();
                    HDB3OutputString = HDB3OutputString.substr(0, actualLength - 3);
                    HDB3OutputString += "0000";
                }
                // OOOV found
                if ((decodingInput[i] == 5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == 0) or (decodingInput[i] == -5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == 0))
                {
                    printf("000V found!\n");
                    HDB3OutputString += "0";
                }
            }
        }
    }
}

void parityMaker()
{
    size_t input_length = HDB3InputString.size();
    if ((input_length % 8) != 0)
    {
        printf("ERROR. Nije ebar thik kore nilam\n");
        while ((input_length % 8) != 0)
        {
            HDB3InputString += "0";
            input_length++;
        }
    }
    vector<string> parityBits;
    for (int i = 0; i + 8 <= input_length; i += 8)
    {
        string temp = HDB3InputString.substr(i, 8);
        parityBits.push_back(temp);
        cout << temp << endl;
    }
    int rows = parityBits.size();
    for (int i = 0; i < rows; i++)
    {
        int oneCount = count(HDB3InputString[i].begin(), HDB3InputString[i].end(), '1');
        if (oneCount % 2 == 0)
        {
            parityBits[i] += "0";
        }
        else
        {
            parityBits[i] += "1";
        }
    }
    for (int i = 0; i < 9; i++)
    {
        int countOfOne = 0;
        for (int j = 0; j < rows; j++)
        {
            if (parityBits[j][i] == '1')
            {
                countOfOne += 1;
            }
        }
        if (countOfOne % 2 == 0)
        {
            parityBits[rows] += "0";
        }
        else
        {
            parityBits[rows] += "1";
        }
    }
    rows += 1;
    input_length += 8;
    for (int i = 0; i < rows; i++)
    {
        cout << parityBits[i] << endl;
    }
}

int main()
{
    int isEncoding;
    printf("Decode(0) or Encode(1): \n");
    scanf("%d", &isEncoding);
    cout << "Enter input\n";
    cin >> HDB3InputString;
    cout << "Input is: " << HDB3InputString << endl;
    //parityMaker();
    if (isEncoding)
    {
        HDB3Encoding();
    }
    else
    {
        HDB3Decoding();
    }
    cout << "Output: " << HDB3OutputString << endl;
    return 0;
}