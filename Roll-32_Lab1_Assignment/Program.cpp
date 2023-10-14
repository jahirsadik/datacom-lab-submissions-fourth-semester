#include <bits/stdc++.h>
using namespace std;

bool isEncoding, isNRZ_L;

char inputStr[1000000];
string outputStr;

void inputFromFile()
{
    FILE *fp;
    if (isEncoding)
    {
        fp = fopen("encoder_input.txt", "r");
        fscanf(fp, "%s", inputStr);

        fclose(fp);
    }
    else
    {
        string tempStr, input = "";
        ifstream MyReadFile("decoder_input.txt");
        while (getline(MyReadFile, tempStr))
        {
            input += tempStr;
        }
        MyReadFile.close();
        strcpy(inputStr, input.c_str());
    }
    cout << "Input Data: " << inputStr << endl;
}

void outputToFile()
{
    FILE *fp;
    if (isEncoding)
    {
        fp = fopen("encoder_output.txt", "w");
        fprintf(fp, "%s", outputStr.c_str());
    }
    else
    {
        fp = fopen("decoder_output.txt", "w");
        fprintf(fp, "%s", outputStr.c_str());
    }
    fclose(fp);
    cout << "Output printed to file." << endl;
}

void nrzLEncoding()
{
    outputStr = "";
    for (size_t i = 0; i < strlen(inputStr); i++)
    {
        if (inputStr[i] == '0')
        {
            outputStr += "+5V, ";
        }
        else if (inputStr[i] == '1')
        {
            outputStr += "-5V, ";
        }
        else
        {
            cout << "Invalid data" << endl;
            return;
        }
    }
    cout << "Output Data: " << outputStr << endl;
    outputToFile();
}

void nrzIEncoding()
{
    outputStr = "";

    string current = "+5V, ";
    int flag = 1;

    for (size_t i = 0; i < strlen(inputStr); i++)
    {
        if (inputStr[i] == '0')
        {
            outputStr += current;
        }
        else if (inputStr[i] == '1')
        {
            flag = flag ^ 1;

            if (flag == 1)
            {
                current = "+5V, ";
            }
            else
            {
                current = "-5V, ";
            }

            outputStr += current;
        }
        else
        {
            cout << "Invalid data" << endl;
            return;
        }
    }

    cout << "Output Data: " << outputStr << endl;
    outputToFile();

}

void nrzLDecoding()
{
    outputStr = "";
    char delim[5] = ", ";
    char *token = strtok(inputStr, delim);
    while (token)
    {
        if (!strcmp(token, "+5V"))
        {
            outputStr += "0";
        }
        else
        {
            outputStr += "1";
        }
        token = strtok(NULL, delim);
    }
    cout << "Output Data: " << outputStr << endl;
    outputToFile();
}

void nrzIDecoding()
{
    outputStr = "";
    string current = "+5V";
    int flag = 1;
    char delim[5] = ", ";
    char *token = strtok(inputStr, delim);
    while (token)
    {
        if (!strcmp(token, current.c_str()))
        {
            outputStr += "0";
        }
        else
        {
            flag = flag ^ 1;
            if (flag)
            {
                current = "+5V";
            }
            else
            {
                current = "-5V";
            }
            outputStr += "1";
        }
        token = strtok(NULL, delim);
    }
    cout << "Output data: " << outputStr << endl;
    outputToFile();
}

int main()
{
    int temp;
    cout << "\t\t\t (1) Encode\n\t\t\t (2) Decode" << endl;
    cin >> temp;
    if (temp == 1)
    {
        isEncoding = true;
        cout << "Chose to Encode." << endl;
    }
    else
    {
        isEncoding = false;
        cout << "Chose to Decode." << endl;
    }

    cout << "\t\t\t (1) NRZ_L\n\t\t\t (2) NRZ_I" << endl;
    cin >> temp;
    if (temp == 1)
    {
        isNRZ_L = true;
        cout << "Chose NRZ_L" << endl;
    }
    else
    {
        isNRZ_L = false;
        cout << "Chose NRZ_I" << endl;
    }

    inputFromFile();

    if (isEncoding)
    {
        if (isNRZ_L)
        {
            nrzLEncoding();
        }
        else
        {
            nrzIEncoding();
        }
    }
    else
    {
        if (isNRZ_L)
        {
            nrzLDecoding();
        }
        else
        {
            nrzIDecoding();
        }
    }

    return 0;
}
