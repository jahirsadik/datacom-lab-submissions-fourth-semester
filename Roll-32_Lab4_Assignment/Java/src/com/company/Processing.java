package com.company;

import java.util.ArrayList;
import java.lang.*;
import java.util.Scanner;

public class Processing {
     static String HDB3Encoding(String HDB3InputString, int lastSignalValue, int tot_one){
        String HDB3OutputString = "";
        int error;
        int input_length = HDB3InputString.length();
        long zeroCount = HDB3InputString.chars().filter(ch -> ch == '0').count(); // count no of 0's
        long oneCount = HDB3InputString.chars().filter(ch -> ch == '1').count(); // count no of 1's
         if ((zeroCount + oneCount) != (input_length)) // see if sum of 0 and 1 count matches total length of input
         {
             input_length = -1;
             error = 1;
             HDB3OutputString = "Error in encoding. Only 0's and 1's are allowed\n";
             return HDB3OutputString;
         }
         for (int i = 0; i < input_length;)
         {
             if (HDB3InputString.charAt(i) == '1') // cur bit is 1
             {
                 tot_one += 1;
                 if (lastSignalValue == 1) // if last signal was positive
                 {
                     lastSignalValue = -1;
                     HDB3OutputString += "-5V, ";
                 }
                 else                       // if last signal was positive
                 {
                     lastSignalValue = 1;
                     HDB3OutputString += "+5V, ";
                 }
                 i++;
             }
             else                           // if cur bit is 0
             {
                 if ((i + 4 <= input_length) &&  (HDB3InputString.substring(i, i+4).equals("0000"))) // if 4 consecutive 0's are found
                 {
                     if ((tot_one % 2) == 0) // encode as B00V
                     {
                         tot_one += 2;
                         if (lastSignalValue == 1) // if last signal was positive
                         {
                             HDB3OutputString += "-5V, 0V, 0V, -5V, ";
                             lastSignalValue = -1;
                         }
                         else                   // if last signal was negative
                         {
                             HDB3OutputString += "+5V, 0V, 0V, +5V, ";
                             lastSignalValue = 1;
                         }
                     }
                     else // encode as 000V
                     {
                         tot_one += 1;
                         if (lastSignalValue == 1)      // if last signal was positive
                         {
                             HDB3OutputString += "0V, 0V, 0V, +5V, ";
                         }
                         else                   // if last signal was negative
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
        return HDB3OutputString;
    }

    static String manchesterEncoding(String inputStr)
    {
        System.out.println("Assuming that last level was +5V.");
        String outputStr = "";
        for (int i = 0; i < inputStr.length(); i++)
        {
            if (inputStr.charAt(i) == '0')
            {
                outputStr += "+5V, -5V, ";
            }
            else if (inputStr.charAt(i) == '1')
            {
                outputStr += "-5V, +5V, ";
            }
            else
            {
                System.out.println("Invalid data.");
                return "Error in Manchester Encoding";
            }
        }
        System.out.println("Output Data: " + outputStr);
        return outputStr;
    }


    static String HDB3Decoding(String HDB3InputString, int lastSignalValue, int tot_one) {
        String HDB3OutputString = "";
        int input_length = HDB3InputString.length();
        ArrayList<Integer> decodingInput = new ArrayList<>();
        for (int i = 0; i < input_length - 1; i++) {  // loop to convert input voltages to 0, +5 or -5
            if (HDB3InputString.charAt(i) == ' ' || HDB3InputString.charAt(i) == ',' || HDB3InputString.charAt(i) == 'V' || HDB3InputString.charAt(i) == 'v' || HDB3InputString.charAt(i) == '5') {
                continue;
            }
            if (HDB3InputString.charAt(i) == '+' && HDB3InputString.charAt(i + 1) == '5') {
                decodingInput.add(5);
            } else if (HDB3InputString.charAt(i) == '-' && HDB3InputString.charAt(i + 1) == '5') {
                decodingInput.add(-5);
            } else if (HDB3InputString.charAt(i) == '0') {
                decodingInput.add(0);
            } else {                            // if any input is other than 0,+5,-5,V,v,',',or ' ' -> error in decoder input
                System.out.println("Invalid Input for HDB3 decoding. Invalid Input was ->(" + HDB3InputString.charAt(i) + ")\n");
                HDB3OutputString = "Error in input.\n";
                return HDB3InputString;
            }
        }
        //System.out.println("After Conversion:");
//        for (Integer integer : decodingInput) {
//            System.out.printf("%d, ", integer);
//        }
        //System.out.println();

        int decodingVectorSize = decodingInput.size();
        //System.out.println("Our Final Vector Size: " + String.valueOf(decodingVectorSize));
        int cur_number_of_zeros = 0;   // keeps track of consecutive 0's at any point
        for (int i = 0; i < decodingVectorSize; i++)
        {
            //System.out.printf("Dhuksi at %d: value %d. TOT_ONES: %d\n", i, decodingInput.get(i), tot_one);
            if (decodingInput.get(i) == 0)     // 0 voltage found
            {
                cur_number_of_zeros++;
                if (cur_number_of_zeros == 4)    // err if more than 3 consecutive 0's are found
                {
                    // HDB3 CANNOT HAVE FOUR CONSECUTIVE 0 Volts
                    System.out.println("HDB3 CANNOT HAVE FOUR CONSECUTIVE 0 Volts");
                    HDB3OutputString += "HDB3 CANNOT HAVE FOUR CONSECUTIVE 0 Volts\n";
                    return HDB3OutputString;
                }
                HDB3OutputString += "0";
            }
            else if (decodingInput.get(i) == 5 || decodingInput.get(i) == -5) // positive voltage found
            {
                cur_number_of_zeros = 0;
                // violation not found
                if (lastSignalValue == 1 && decodingInput.get(i) == -5)
                {
                    lastSignalValue = -1;
                    tot_one += 1;
                    HDB3OutputString += "1";
                } else if (lastSignalValue == -1 && decodingInput.get(i) == 5)
                {
                    lastSignalValue = 1;
                    tot_one += 1;
                    HDB3OutputString += "1";
                }
                // any violations found
                else if ((lastSignalValue == 1 && decodingInput.get(i) == 5) || (lastSignalValue == -1 && decodingInput.get(i) == -5))
                {
                    tot_one += 1; // including the violation voltage, tot_one value must be even
                    if ((tot_one % 2) != 0)
                    {
                        // INVALID SEQUENCE
                        System.out.printf("INVALID VIOLATION FOUND at i = %d!(ODD)\n", i);
                        HDB3OutputString = "INVALID VIOLATION FOUND (ODD)!";
                        return HDB3OutputString;
                    }
                    // check if i < 3 for any violation, which is impossible
                    if (i < 3)
                    {
                        // INVALID SEQUENCE
                        System.out.printf("INVALID VIOLATION FOUND at i = %d!\n", i);
                        HDB3OutputString = "INVALID VIOLATION FOUND!";
                        return HDB3OutputString;
                    }
                    // BOOV found
                    if ((decodingInput.get(i) == 5 && decodingInput.get(i - 1) == 0 && decodingInput.get(i - 2) == 0 && decodingInput.get(i - 3) == 5) ||
                            (decodingInput.get(i) == -5 && decodingInput.get(i - 1) == 0 && decodingInput.get(i - 2) == 0 && decodingInput.get(i - 3) == -5))
                    {
                        //System.out.printf("BOOV found!\n");
                        int actualLength = HDB3OutputString.length();
                        HDB3OutputString = HDB3OutputString.substring(0, actualLength - 3);
                        HDB3OutputString += "0000";
                    }
                    // OOOV found
                    if ((decodingInput.get(i) == 5 && decodingInput.get(i - 1) == 0 && decodingInput.get(i - 2) == 0 && decodingInput.get(i - 3) == 0) || (decodingInput.get(i) == -5 && decodingInput.get(i - 1) == 0 && decodingInput.get(i - 2) == 0 && decodingInput.get(i-3) == 0))
                    {
                        //System.out.printf("000V found!\n");
                        HDB3OutputString += "0";
                    }
                }
            }
        }
        return HDB3OutputString;
    }

     static String parityBits(String toBeParsed){
        int len = toBeParsed.length();
        if(len % 8 != 0)
        {
            System.out.println("Discarding last " + (len%8) + " bits of the input bitstream.");
        }
        len = len - (len%8);
        toBeParsed = toBeParsed.substring(0, len);
        if(len == 0) // add 0's in the end if total input length is not divisible by 8
        {
            return "Error. Input length was less than 8.";
        }

        ArrayList<String> parityAddedBitstreams = new ArrayList<String>();
        for(int i = 0; i+8<=len; i+=8)
        {
            String currentBitStream = toBeParsed.substring(i,i+8);
            long count = currentBitStream.chars().filter(ch -> ch == '1').count(); // total 1's in the row
            if(count%2==0) currentBitStream+="0";
            else currentBitStream+="1";
            parityAddedBitstreams.add(currentBitStream);
        }

        int numOfStrings = parityAddedBitstreams.size();
        String columnParity = "";                           // for the last 'column parity' row
        for(int i = 0; i<9; i++)
        {
            int ones = 0;
            for(String curString : parityAddedBitstreams)
            {
                if(curString.charAt(i)=='1') ones++; // total 1's in the column
            }
            if(ones%2!=0) columnParity += '1';
            else columnParity += '0';
        }
        parityAddedBitstreams.add(columnParity);
        System.out.println("2D parity added array: " + parityAddedBitstreams);
        String parityAddedString = "";
        for (String temp : parityAddedBitstreams)
        {
            parityAddedString += temp;
        }
        return parityAddedString;
    }

    static ArrayList<String> ParityChecker(String input)
    {
        if(input.charAt(0)!='0'|| input.charAt(0)!='+' || input.charAt(0)!='-'){
            ArrayList<String> outputBitStreams = new ArrayList<String>();
            outputBitStreams.add("Error. Couldn't decode using HDB3.");
            return outputBitStreams;
        }
        String outputString = "";
        int validity = 1;       // validity == 1 means no error
        ArrayList<String> receivedBitstreams = new ArrayList<String>();
        int len = input.length();
        System.out.println("Parity checker input length: " + len +". Input in parity checker: " + input);
        if(len%9!=0)
        {
            validity = -5;
        }
        else
        {
            for(int i = 0; i<len; i+=9)
            {
                String curBitStream = input.substring(i,i+9);
                receivedBitstreams.add(curBitStream);
            }
            int numOfStrings = receivedBitstreams.size();
            int rowParityChecker = 1, columnParityChecker = 1;
            for(int i=0;i<9; i++)
            {
                int ones = 0;
                for(int j = 0; j<numOfStrings; j++)
                {
                    String curBitStream = receivedBitstreams.get(j);
                    if(curBitStream.charAt(i)=='1') ones++;
                }
                if(ones%2!=0)               // if no. of 1's in a row isn't even
                {
                    outputString = "Error found at -> " + String.valueOf(i+1) + "th Column.";
                    columnParityChecker = 0;
                    break;
                }
            }
            for(int i = 0; i<numOfStrings; i++)
            {
                int ones = 0;
                for(int j = 0; j<9; j++)
                {
                    String curBitStream = receivedBitstreams.get(i);
                    if(curBitStream.charAt(j)=='1') ones++;
                }
                if(ones%2!=0)           // if no. of 1's in a row isn't even
                {
                    outputString = "Error found at -> " + String.valueOf(i+1) + "th row.";
                    rowParityChecker = 0;
                    break;
                }
            }
            validity = rowParityChecker & columnParityChecker;
        }
        if(validity == -5)
        {
            ArrayList<String> outputBitStreams = new ArrayList<String>();
            outputBitStreams.add("Error, Wasn't divisible by 9.");
            return outputBitStreams;
        }
        if(outputString.startsWith("Error")){
            ArrayList<String> outputBitStreams = new ArrayList<String>();
            outputBitStreams.add(outputString);
            return outputBitStreams;
        }
        ArrayList<String> outputBitStream = new ArrayList<>();
        int rows = receivedBitstreams.size();
        //System.out.printf("Size: %d", rows);
        for(int i = 0; i < rows-1; i++){
            outputBitStream.add(receivedBitstreams.get(i).substring(0, 8));
        }

        return outputBitStream;
    }

    public static void main(String[] args){  // only for checking the functions in this class
         while(true){
             String str;
             Scanner myObj = new Scanner(System.in);  // Create a Scanner object
             System.out.println("Enter Decoder Input: ");
             str = myObj.nextLine();  // Read user input
             System.out.println("Input is: " + str);  // Output user input
             System.out.println("Final Output: " + Processing.HDB3Encoding(str, -1, 0));;
             System.out.println("Parity Added: \n" + parityBits(str));
         }
    }
}