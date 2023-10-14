#include <bits/stdc++.h>
using namespace std;

bool isEncoding;
int typeOfOperation = -1;

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

void manchesterEncoding()
{
	cout << "Assuming that last level was +5V." << endl;
    outputStr = "";
    for (size_t i = 0; i < strlen(inputStr); i++)
    {
        if (inputStr[i] == '0')
        {
            outputStr += "+5V, -5V, ";
        }
        else if (inputStr[i] == '1')
        {
            outputStr += "-5V, +5V, ";
        }
        else
        {
            cout << "Invalid data." << endl;
            return;
        }
    }
    cout << "Output Data: " << outputStr << endl;
    outputToFile();
}

void differentialManchesterIEncoding()
{
	cout << "Assuming that last level was +5V." << endl;
	bool bit = true;	
    outputStr = "";
    for (size_t i = 0; i < strlen(inputStr); i++)
    {
        if (inputStr[i] == '0')
        {
            if(bit)
            {
            	outputStr += "-5V, +5V, ";
            }
            else
            {
            	outputStr += "+5V, -5V, ";
            }
        }
        else if (inputStr[i] == '1')
        {
            if(bit)
            {
            	outputStr += "+5V, -5V, ";
            	bit = false;
            }
            else
            {
            	outputStr += "-5V, +5V, ";
            	bit = true;
            }`
        }
        else
        {
            cout << "Invalid data." << endl;
            return;
        }
    }
    cout << "Output Data: " << outputStr << endl;
    outputToFile();
}

void amiEncoding()
{
    outputStr = "";
	cout << "Assuming that last level was +5V." << endl;
    int flag = 1;

    for (size_t i = 0; i < strlen(inputStr); i++)
    {
        if (inputStr[i] == '0')
        {
            outputStr += "0V, ";
        }
        else if (inputStr[i] == '1')
        {
            flag = flag ^ 1;

            if (flag == 1)
            {
                outputStr += "+5V, ";
            }
            else
            {
                outputStr += "-5V, ";
            }

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

void manchesterDecoding()
{
	cout << "Assuming that last level was +5V." << endl;
    outputStr = "";
    char delim[5] = ", ";
    char *token = strtok(inputStr, delim);
    bool isSecond = false;
    while (token)
    {
        if (!strcmp(token, "+5V"))
        {
            if(isSecond)
            {
            	outputStr += "1";
            }
            isSecond = (1 ^ isSecond);
        }
        else if (!strcmp(token, "-5V"))
        {
            if(isSecond)
            {
            	outputStr += "0";
            }
            isSecond = (1 ^ isSecond);
        }
        else
        {
        	printf("INVALID DATA.\n");
        	outputStr = "INVALID DATA.";
        	return;
        }
        token = strtok(NULL, delim);
    }
    cout << "Output Data: " << outputStr << endl;
    outputToFile();
}

void differentialManchesterIDecoding()
{
	cout << "Assuming that last level was +5V." << endl;
    outputStr = "";
    bool bit = true;
    char delim[5] = ", ";
    char *token = strtok(inputStr, delim);
    bool isSecond = false;
    while (token)
    {
        if (!strcmp(token, "+5V"))
        {
            if(isSecond && bit)
            {
            	outputStr += "0";
            }
            else if(isSecond && !bit)
            {
            	outputStr += "1";
            	bit = (1 ^ bit);
            }
            isSecond = (1 ^ isSecond);
        }
        else if (!strcmp(token, "-5V"))
        {
            if(isSecond && !bit)
            {
            	outputStr += "0";
            }
            else if(isSecond && bit)
            {
            	outputStr += "1";
            	bit = (1 ^ bit);
            }
            isSecond = (1 ^ isSecond);
        }
        else
        {
        	printf("INVALID DATA.\n");
        	outputStr = "INVALID DATA.";
        	return;
        }
        token = strtok(NULL, delim);
    }
    cout << "Output Data: " << outputStr << endl;
    outputToFile();
}

void amiDecoding()
{
	cout << "Assuming that last level was +5V." << endl;
    outputStr = "";
    char delim[5] = ", ";
    char *token = strtok(inputStr, delim);
    while (token)
    {
        if (!strcmp(token, "+5V"))
        {
        	outputStr += "1";
        }
        else if (!strcmp(token, "-5V"))
        {
			outputStr += "1";
        }
        else
        {
        	outputStr += "0";
        }
        token = strtok(NULL, delim);
    }
    cout << "Output Data: " << outputStr << endl;
    outputToFile();
}

int main()
{

	while(1)
	{
	typeOfOperation = -1;
    int temp;
    cout << "\t\t\t (1) Encode\n\t\t\t (2) Decode\n\t\t\t (0) Exit" << endl;
    cin >> temp;
    switch(temp){
    	case 0:
    		cout << "Quitting.." << endl;
    		return 0;
    	case 1:
    	        isEncoding = true;
        		cout << "Chose to Encode." << endl;
        		break;
        case 2:
		        isEncoding = false;
       			cout << "Chose to Decode." << endl;
       			break;
       	default:
       			cout << "Invalid Input" << endl;
    	        isEncoding = true;
        		cout << "Chose to Encode." << endl;
    }

    cout << "\t\t\t (1) Manchester \n\t\t\t (2) Differential Manchester \n\t\t\t (3) AMI" << endl;
    cin >> temp;

    switch(temp){
	case 1:
            typeOfOperation = 1;
        	cout << "Chose Manchester" << endl;
    		break;
	case 2:
            typeOfOperation = 2;
        	cout << "Chose Differential Manchester" << endl;
    		break;
	case 3:
            typeOfOperation = 3;
        	cout << "Chose AMI" << endl;
    		break;
   	default:
   			cout << "Invalid Input" << endl;
            typeOfOperation = 1;
    		cout << "Chose Manchester." << endl;
	}


    inputFromFile();
    if (isEncoding)
    {
        switch(typeOfOperation)
        {
        	case 1:
        		manchesterEncoding();
        		break;
        	case 2:
        		differentialManchesterIEncoding();
        		break;
        	case 3:
        		amiEncoding();
        		break;
        	default:
        		cout << "Error in typeOfOperation. Try again!" << endl;
        }
    }
    else
    {
        switch(typeOfOperation)
        {
        	case 1:
        		manchesterDecoding();
        		break;
        	case 2:
        		differentialManchesterIDecoding();
        		break;
        	case 3:
        		amiDecoding();
        		break;
        	default:
        		cout << "Error in typeOfOperation. Try again!" << endl;
        }
    }

	}
    return 0;
}
