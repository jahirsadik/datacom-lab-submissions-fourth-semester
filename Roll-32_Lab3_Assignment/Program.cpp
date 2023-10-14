#include <bits/stdc++.h>
using namespace std;

bool isEncoding, isLineCoding;
int typeOfOperation = -1;
char lineCodingInputStr[1000000];
char scramblingInputStr[1000000];
string lineCodingOutputStr, scramblingOutputStr;
string twoBoneQEncodingOutput;
string twoBoneQDecodingOutput;
string mltThreeEncodingOutput;
string mltThreeDecodingOutput;
string scramblingEncodingOutput;
string scramblingDecodingOutput;

void lineCodingInputFromFile()
{
	FILE *fp;
	if (isEncoding)
	{
		fp = fopen("encoder_input.txt", "r");
		fscanf(fp, "%s", lineCodingInputStr);

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
		strcpy(lineCodingInputStr, input.c_str());
	}
	cout << "Input Data: " << lineCodingInputStr << endl;
}

void scramblingInputFromFile()
{
	FILE *fp;
	if (isEncoding)
	{
		fp = fopen("scrambling_encoder_input.txt", "r");
		fscanf(fp, "%s", scramblingInputStr);
		fclose(fp);
	}
	else
	{
		string tempStr, input = "";
		ifstream MyReadFile("scrambling_decoder_input.txt");
		while (getline(MyReadFile, tempStr))
		{
			input += tempStr;
		}
		MyReadFile.close();
		strcpy(scramblingInputStr, input.c_str());
	}
	cout << "Input Data: " << scramblingInputStr << endl;
}

void scramblingOutputToFile()
{
	FILE *fp;
	if (isEncoding)
	{
		fp = fopen("scrambling_encoder_output.txt", "w");
		fprintf(fp, "%s", scramblingOutputStr.c_str());
	}
	else
	{
		fp = fopen("scrambling_decoder_output.txt", "w");
		fprintf(fp, "%s", scramblingOutputStr.c_str());
	}
	fclose(fp);
	cout << "Output printed to file." << endl;
}

void lineCodingOutputToFile()
{
	FILE *fp;
	if (isEncoding)
	{
		fp = fopen("encoder_output.txt", "w");
		fprintf(fp, "%s", lineCodingOutputStr.c_str());
	}
	else
	{
		fp = fopen("decoder_output.txt", "w");
		fprintf(fp, "%s", lineCodingOutputStr.c_str());
	}
	fclose(fp);
	cout << "Output printed to file." << endl;
}

void twoBoneQEncoding()
{

	char tempInputStr[1000000];
	strcpy(tempInputStr, lineCodingInputStr);
	twoBoneQEncodingOutput = "";
	int flag = 0, error = 0; // 0-> no error. 1-> bit error. -1-> less than 2 bits in input
	cout << "Chose if last level was (0) Positive, (1) Negative. For 2B1Q Encoding." << endl;
	cin >> flag;
	if (!flag)
	{
		cout << "Assuming that last level was Positive." << endl;
	}
	else
	{
		cout << "Assuming that last level was Negative." << endl;
	}
	map<string, string> mp;
	mp["+00"] = "+1V, ";
	mp["-00"] = "-1V, ";
	mp["+01"] = "+3V, ";
	mp["-01"] = "-3V, ";
	mp["+10"] = "-1V, ";
	mp["-10"] = "+1V, ";
	mp["+11"] = "-3V, ";
	mp["-11"] = "+3V, ";

	size_t input_length = strlen(tempInputStr);
	if (input_length < 2)
	{
		cout << "Less than two bits are in input. No output can be given" << endl;
		error = -1;
	}
	if (input_length % 2)
	{
		cout << "Odd number of bits added as input. Last bit is discarded." << endl;
		input_length--;
	}

	for (size_t i = 0; i < input_length; i += 2)
	{
		if (tempInputStr[i] == '0') // 00 or 01
		{
			if (tempInputStr[i + 1] == '0') // 00
			{
				if (!flag) // last level was positive
				{
					twoBoneQEncodingOutput += mp["+00"];
					flag = 0;
				}
				else // last level was negative
				{
					twoBoneQEncodingOutput += mp["-00"];
					flag = 1; // this level is negative
				}
			}
			else if (tempInputStr[i + 1] == '1') // 01
			{
				if (!flag) // last level was positive
				{
					twoBoneQEncodingOutput += mp["+01"];
					flag = 0;
				}
				else // last level was negative
				{
					twoBoneQEncodingOutput += mp["-01"];
					flag = 1; // this level is negative
				}
			}
			else
			{
				error = 1;
			}
		}
		else if (tempInputStr[i] == '1') // 10 or 11
		{
			if (tempInputStr[i + 1] == '0') // 10
			{
				if (!flag) // +10
				{
					twoBoneQEncodingOutput += mp["+10"];
					flag = 1;
				}
				else
				{
					twoBoneQEncodingOutput += mp["-10"];
					flag = 0; // this level is positive
				}
			}
			else if (tempInputStr[i + 1] == '1') // 11
			{
				if (!flag) // +11
				{
					twoBoneQEncodingOutput += mp["+11"];
					flag = 1;
				}
				else
				{
					twoBoneQEncodingOutput += mp["-11"];
					flag = 0; // this level is positive
				}
			}
			else
			{
				error = 1;
			}
		}
		else
		{
			error = 1;
		}
	}
	if (error == 1)
	{
		twoBoneQEncodingOutput = "For input: ";
		string tempInputString(tempInputStr);
		twoBoneQEncodingOutput += tempInputString;
		twoBoneQEncodingOutput += ":\nEncoded Output Data for 2B1Q: (These was error in input bits.)\n\n";
	}
	else if (error == -1)
	{
		twoBoneQEncodingOutput = "For input: ";
		string tempInputString(tempInputStr);
		twoBoneQEncodingOutput += tempInputString;
		twoBoneQEncodingOutput += ":\nEncoded Output Data for 2B1Q: (These was less than two bits in input)\n\n";
	}
	else
	{
		string tempInputString(tempInputStr);
		twoBoneQEncodingOutput = "For input: " + tempInputString + ":\nEncoded Output Data for 2B1Q: (" + twoBoneQEncodingOutput + ")\n\n";
	}
	cout << twoBoneQEncodingOutput << endl;
	lineCodingOutputStr += twoBoneQEncodingOutput;
}

void mltThreeEncoding()
{
	char tempInputStr[1000000];
	strcpy(tempInputStr, lineCodingInputStr);
	mltThreeEncodingOutput = "";
	int levelNow = 0, error = 0; // 0-> no error. 1-> bit error.
	int lastNonZeroLevel = 0;	 // 0 means positive
	cout << "Chose if last non-zero level was (0) Positive, (1) Negative. For MLT3 encoding." << endl;
	cin >> lastNonZeroLevel;
	if (!lastNonZeroLevel)
	{
		cout << "Assuming that last non-zero level was Positive." << endl;
	}
	else
	{
		cout << "Assuming that last level was Negative." << endl;
	}

	size_t input_length = strlen(tempInputStr);

	for (size_t i = 0; i < input_length; i++)
	{
		if (tempInputStr[i] == '0')
		{
			// level now doesn't change for 0
			if (levelNow == 0)
			{
				// last non zero level doesn't change for 0
				mltThreeEncodingOutput += "0V, ";
			}
			else if (levelNow == 1)
			{
				mltThreeEncodingOutput += "+5V, ";
				lastNonZeroLevel = 0;
				levelNow = 1;
			}
			else
			{
				mltThreeEncodingOutput += "-5V, ";
				lastNonZeroLevel = 1;
				levelNow = -1;
			}
		}
		else if (tempInputStr[i] == '1')
		{
			if (!levelNow) // current level was not zero
			{
				if (!lastNonZeroLevel)
				{
					levelNow = -1;
					mltThreeEncodingOutput += "-5V, ";
					lastNonZeroLevel = 1;
				}
				else
				{
					levelNow = 1;
					mltThreeEncodingOutput += "+5V, ";
					lastNonZeroLevel = 0;
				}
			}
			else // current level was zero
			{
				// level now changes to zero
				levelNow = 0;
				// last non zero bit doesn't change
				mltThreeEncodingOutput += "0V, ";
			}
		}
		else
		{
			error = 1;
		}
	}
	if (error == 1)
	{
		mltThreeEncodingOutput = "For input: ";
		string tempInputString(tempInputStr);
		mltThreeEncodingOutput += tempInputString;
		mltThreeEncodingOutput += ":\nEncoded Output Data for MLT3: (These was error in input bits.)\n\n";
	}
	else
	{
		string tempInputString(tempInputStr);
		mltThreeEncodingOutput = "For input: " + tempInputString + ":\nEncoded Output Data for MLT3: (" + mltThreeEncodingOutput + ")\n\n";
	}
	cout << mltThreeEncodingOutput << endl;
	lineCodingOutputStr += mltThreeEncodingOutput;
}

void mltThreeDecoding()
{
	char tempInputStr[1000000];
	strcpy(tempInputStr, lineCodingInputStr);
	mltThreeDecodingOutput = "";
	int levelNow = 0, error = 0; // 0-> no error. 1-> bit error.
	char delim[5] = ", ";
	char *token = strtok(lineCodingInputStr, delim);
	bool isSecond = false;
	while (token)
	{
		if (!strcmp(token, "+5V"))
		{
			if (levelNow == 1)
			{
				mltThreeDecodingOutput += "0";
			}
			else
			{
				mltThreeDecodingOutput += "1";
			}
			levelNow = 1;
		}
		else if (!strcmp(token, "-5V"))
		{
			if (levelNow == -1)
			{
				mltThreeDecodingOutput += "0";
			}
			else
			{
				mltThreeDecodingOutput += "1";
			}
			levelNow = -1;
		}
		else if (!strcmp(token, "0V"))
		{
			if (levelNow == 0)
			{
				mltThreeDecodingOutput += "0";
			}
			else
			{
				mltThreeDecodingOutput += "1";
			}
			levelNow = 0;
		}
		else
		{
			error = 1;
			break;
		}
		token = strtok(NULL, delim);
	}
	if (error == 1)
	{
		mltThreeDecodingOutput = "For input: ";
		string tempInputString(tempInputStr);
		mltThreeDecodingOutput += tempInputString;
		mltThreeDecodingOutput += ":\nDecoded Output Data for MLT3: (These was error in input voltages.)\n\n";
	}
	else
	{
		string tempInputString(tempInputStr);
		mltThreeDecodingOutput = "For input: " + tempInputString + ":\nDecoded Output Data for 2B1Q: (" + mltThreeDecodingOutput + ")\n\n";
	}
	cout << mltThreeDecodingOutput << endl;
	lineCodingOutputStr += mltThreeDecodingOutput;
}

void twoBoneQDecoding()
{
	char tempInputStr[1000000];
	strcpy(tempInputStr, lineCodingInputStr);
	twoBoneQDecodingOutput = "";
	int flag = 0, error = 0; // 0-> no error.
	cout << "Chose if last level was (0) Positive, (1) Negative. For 2B1Q Decoding." << endl;
	cin >> flag;
	if (!flag)
	{
		cout << "Assuming that last level was Positive." << endl;
	}
	else
	{
		cout << "Assuming that last level was Negative." << endl;
	}
	map<string, string> mpOfPrevPos;
	map<string, string> mpOfPrevNeg;
	mpOfPrevPos["+1V"] = "00";
	mpOfPrevPos["+3V"] = "01";
	mpOfPrevPos["-1V"] = "10";
	mpOfPrevPos["-3V"] = "11";
	mpOfPrevNeg["+1V"] = "10";
	mpOfPrevNeg["+3V"] = "11";
	mpOfPrevNeg["-1V"] = "00";
	mpOfPrevNeg["-3V"] = "01";
	char delim[5] = ", ";
	char *token = strtok(tempInputStr, delim);
	while (token)
	{
		if (!strcmp(token, "+3V"))
		{
			if (flag) // previous was negative
			{
				twoBoneQDecodingOutput += mpOfPrevNeg["+3V"];
				flag = 0; //
			}
			else
			{
				twoBoneQDecodingOutput += mpOfPrevPos["+3V"];
				flag = 0;
			}
		}
		else if (!strcmp(token, "-3V"))
		{
			if (flag) // previous was negative
			{
				twoBoneQDecodingOutput += mpOfPrevNeg["-3V"];
				flag = 1; //
			}
			else
			{
				twoBoneQDecodingOutput += mpOfPrevPos["-3V"];
				flag = 1;
			}
		}
		else if (!strcmp(token, "+1V"))
		{
			if (flag) // previous was negative
			{
				twoBoneQDecodingOutput += mpOfPrevNeg["+1V"];
				flag = 0; //
			}
			else
			{
				twoBoneQDecodingOutput += mpOfPrevPos["+1V"];
				flag = 0;
			}
		}
		else if (!strcmp(token, "-1V"))
		{
			if (flag) // previous was negative
			{
				twoBoneQDecodingOutput += mpOfPrevNeg["-1V"];
				flag = 1; //
			}
			else
			{
				twoBoneQDecodingOutput += mpOfPrevPos["-1V"];
				flag = 1;
			}
		}
		else
		{
			error = 1;
			break;
		}
		token = strtok(NULL, delim);
	}
	if (error == 1)
	{
		twoBoneQDecodingOutput = "For input: ";
		string tempInputString(tempInputStr);
		twoBoneQDecodingOutput += tempInputString;
		twoBoneQDecodingOutput += ":\nDecoded Output Data for 2B1Q: (These was error in input voltages.)\n\n";
	}
	else
	{
		string tempInputString(tempInputStr);
		twoBoneQDecodingOutput = "For input: " + tempInputString + ":\nDecoded Output Data for 2B1Q: (" + twoBoneQDecodingOutput + ")\n\n";
	}
	cout << twoBoneQDecodingOutput << endl;
	lineCodingOutputStr += twoBoneQDecodingOutput;
}

void BEightZSEncoding()
{
	string tempInputStr(scramblingInputStr);
	string eightZeros = "00000000";
	scramblingEncodingOutput = "";
	int lastSignalPositive = 0, error = 0; // 0-> no error.
	cout << "Chose if last level was (0) Positive, (1) Negative. For B8ZS Encoding." << endl;
	cin >> lastSignalPositive;
	if (!lastSignalPositive)
	{
		cout << "Assuming that last level was Positive." << endl;
		lastSignalPositive = 1;
	}
	else
	{
		cout << "Assuming that last level was Negative." << endl;
		lastSignalPositive = 0;
	}
	size_t input_length = tempInputStr.size();
	int zeroCount = count(tempInputStr.begin(), tempInputStr.end(), '0');
	int oneCount = count(tempInputStr.begin(), tempInputStr.end(), '1');
	if ((zeroCount + oneCount) != (input_length))
	{
		input_length = -1;
	}

	for (size_t i = 0; i < input_length;)
	{
		if (tempInputStr[i] == '1')
		{
			if (!lastSignalPositive)
			{
				scramblingEncodingOutput += "+5V, ";
				lastSignalPositive = 1;
			}
			else
			{
				scramblingEncodingOutput += "-5V, ";
				lastSignalPositive = 0;
			}
			i++;
		}
		else
		{
			if ((i + 8 <= input_length) and (tempInputStr.substr(i, 8) == eightZeros))
			{
				for (int k = 0; k < 3; k++)
				{
					scramblingEncodingOutput += "0V, ";
				}
				int Vsign = lastSignalPositive;
				if (lastSignalPositive)
				{
					scramblingEncodingOutput += "+5V, -5V, 0V, -5V, +5V, ";
				}
				else
				{
					scramblingEncodingOutput += "-5V, +5V, 0V, +5V, -5V, ";
				}
				i += 8;
			}
			else
			{
				scramblingEncodingOutput += "0V, ";
				i++;
			}
		}
	}

	if (input_length == -1)
	{
		scramblingEncodingOutput = "For input: ";
		scramblingEncodingOutput += tempInputStr;
		scramblingEncodingOutput += ":\nEncoded Output Data for B8ZS: (These was error in input bits.)\n\n";
	}
	else
	{
		scramblingEncodingOutput = "For input: " + tempInputStr + ":\nEncoded Output Data for B8ZS: (" + scramblingEncodingOutput + ")\n\n";
	}
	cout << scramblingEncodingOutput << endl;
	scramblingOutputStr += scramblingEncodingOutput;
}

string opposite(string s)
{
	if (s == "+5V")
		return "-5V";
	if (s == "-5V")
		return "+5V";
	return s;
}

void BEightZSDecoding()
{
	string tempInputStr(scramblingInputStr);
	scramblingEncodingOutput = "";
	int lastSignalPositive = 0, error = 0; // 0-> no error.
	cout << "Chose if last level was (0) Positive, (1) Negative. For B8ZS Decoding." << endl;
	cin >> lastSignalPositive;
	if (!lastSignalPositive)
	{
		cout << "Assuming that last level was Positive." << endl;
		lastSignalPositive = 1;
	}
	else
	{
		cout << "Assuming that last level was Negative." << endl;
		lastSignalPositive = 0;
	}
	size_t input_length = tempInputStr.size();
	stringstream ss(tempInputStr);
	vector<string> all_levels;
	string cur_Level;
	while (ss >> cur_Level)
	{
		if (cur_Level != "0V," and cur_Level != "+5V," and cur_Level != "-5V,")
		{
			error = 1;
		}
		if (cur_Level == "0V,")
		{
			all_levels.push_back("0V");
		}
		else if (cur_Level == "+5V,")
		{
			all_levels.push_back("+5V");
		}
		else
		{
			all_levels.push_back("-5V");
		}
	}
	input_length = all_levels.size();
	string lastNonZeroLevel = "-5V";
	if (lastSignalPositive)
	{
		lastNonZeroLevel = "+5V";
	}

	for (size_t i = 0; i < input_length and !error;)
	{
		string curVoltage = all_levels[i];
		if (curVoltage != "0V")
		{
			if (curVoltage == lastNonZeroLevel)
			{
				error = 1;
				break;
			}
			else
			{
				scramblingDecodingOutput += "1";
				lastNonZeroLevel = opposite(lastNonZeroLevel);
			}
			i++;
		}
		else if (i + 8 <= input_length)
		{
			if (all_levels[i] == "0V" and all_levels[i + 1] == "0V" and all_levels[i + 2] == "0V" and
				all_levels[i + 3] == lastNonZeroLevel and all_levels[i + 4] == opposite(all_levels[i + 3]) and all_levels[i + 5] == "0V" and all_levels[i + 6] == opposite(all_levels[i + 3]) and all_levels[i + 7] == all_levels[i + 3])
			{
				scramblingDecodingOutput += "00000000";
				i += 8;
			}
			else
			{
				scramblingDecodingOutput += "0";
				i++;
			}
		}
		else
		{
			scramblingDecodingOutput += "0";
			i++;
		}
	}

	if (error == 1)
	{
		scramblingDecodingOutput = "For input: ";
		scramblingDecodingOutput += tempInputStr;
		scramblingDecodingOutput += ":\nDecoded Output Data for B8ZS: (These was error in input voltages.)\n\n";
	}
	else
	{
		scramblingDecodingOutput = "For input: " + tempInputStr + ":\nDecoded Output Data for B8ZS: (" + scramblingDecodingOutput + ")\n\n";
	}
	cout << scramblingDecodingOutput << endl;
	scramblingOutputStr += scramblingDecodingOutput;
}

string HDB3OutputString, HDB3InputString;

void HDB3Encoding()
{
	HDB3InputString = scramblingInputStr;
    HDB3OutputString = "";
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
		cout << "HDB3 Encoding: " << HDB3OutputString << endl;
		scramblingOutputStr += ("HDB3 Encoding: " + HDB3OutputString);
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

	cout << "HDB3 Encoding: " << HDB3OutputString << endl;
	scramblingOutputStr += ("HDB3 Encoding: " + HDB3OutputString);
}

void HDB3Decoding()
{
	int lastSignalValue = -1, tot_one = 0, error = 0; // 0-> no error. // initially positive and even
	HDB3InputString = scramblingInputStr;
    HDB3OutputString = "";
	cout << "Chose if last level was (0) Positive, (1) Negative. For HDB3 Decoding." << endl;
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
	cout << "Chose if initially the number of non-zero was (0) Even, (1) Odd. For HDB3 Decoding." << endl;
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
			scramblingOutputStr += ("HDB3 Decoding: " + HDB3OutputString);
			return;
		}
	}

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
                    scramblingOutputStr += ("HDB3 Decoding: " + HDB3OutputString);
					return;
				}
				// check if i < 3 for any violation, which is impossible
				if (i < 3)
				{
					// INVALID SEQUENCE
					printf("INVALID VIOLATION FOUND at i = %d!\n", i);
					HDB3OutputString = "INVALID VIOLATION FOUND!";
                    scramblingOutputStr += ("HDB3 Decoding: " + HDB3OutputString);
					return;
				}
				// BOOV found
				if ((decodingInput[i] == 5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == 5) or
					(decodingInput[i] == -5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == -5))
				{
					//printf("BOOV found!\n");
					size_t actualLength = HDB3OutputString.size();
					HDB3OutputString = HDB3OutputString.substr(0, actualLength - 3);
					HDB3OutputString += "0000";
				}
				// OOOV found
				if ((decodingInput[i] == 5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == 0) or (decodingInput[i] == -5 and decodingInput[i - 1] == 0 and decodingInput[i - 2] == 0 and decodingInput[i - 3] == 0))
				{
					//printf("000V found!\n");
					HDB3OutputString += "0";
				}
			}
		}
	}
	cout << "HDB3 Decoding: " << HDB3OutputString << endl;
	scramblingOutputStr += ("HDB3 Decoding: " + HDB3OutputString);
}

int main()
{
	while (1)
	{
		int temp;
		cout << "\t\t\t (1) Encode\n\t\t\t (2) Decode\n\t\t\t (0) Exit" << endl;
		cin >> temp;
		switch (temp)
		{
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
			cout << "Chose to Encode by default." << endl;
		}

		cout << "\t\t\t (1) Line Coding\n\t\t\t (2) Scrambling" << endl;
		cin >> temp;
		switch (temp)
		{
		case 1:
			isLineCoding = true;
			cout << "Chose Line Coding." << endl;
			break;
		case 2:
			isLineCoding = false;
			cout << "Chose Scrambling." << endl;
			break;
		default:
			cout << "Invalid Input" << endl;
			isLineCoding = true;
			cout << "Chose Line Coding by default." << endl;
		}

		if (isLineCoding)
		{
			lineCodingInputFromFile();
		}
		else
		{
			scramblingInputFromFile();
		}

		if (isLineCoding && isEncoding)
		{
			twoBoneQEncoding();
			mltThreeEncoding();
			lineCodingOutputToFile();
		}
		else if (isLineCoding && !isEncoding)
		{
			twoBoneQDecoding();
			mltThreeDecoding();
			lineCodingOutputToFile();
		}
		else if (!isLineCoding && isEncoding)
		{
			// scrambling encoding
			BEightZSEncoding();
			HDB3Encoding();
			scramblingOutputToFile();
		}
		else
		{
			// scrambling decoding
			BEightZSDecoding();
			HDB3Decoding();
			scramblingOutputToFile();
		}
	}
	return 0;
}
