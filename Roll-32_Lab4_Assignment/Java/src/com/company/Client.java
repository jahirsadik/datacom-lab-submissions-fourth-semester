package com.company;
import java.io.*;
import java.net.*;
import java.util.Random;
import java.sql.Timestamp;
import java.util.Date;
import java.util.concurrent.atomic.AtomicBoolean;

public class Client {
    static int lastSignalValue = -1;
    static int tot_one = 0;

    public Client(){
        final int PORT_NO = 9999;
        DataOutputStream outputStream = null;
        DataInputStream inputStream;
        BufferedReader bufferedReader;
        Socket socket = null;
        try{
            socket = new Socket("localhost", PORT_NO);                  // client socket connecting to port
            outputStream = new DataOutputStream(socket.getOutputStream());
            inputStream = new DataInputStream(socket.getInputStream());
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
            String writeData = "", readData = "", inputBits = "";
            while (!writeData.equals("stop")){                              // run loop until user inputs 'stop'
                System.out.println("Enter Input Bitstream:");
                writeData = bufferedReader.readLine();                      // take input bitstream
                inputBits = writeData;
                if(writeData.equals("stop"))
                {
                    System.out.println("[Client Console] Stopping the client side program and corresponding server thread.");
                    outputStream.writeUTF("stop");
                    outputStream.flush();
                    break;
                }
                //code for last signal value and num of one
                System.out.println("Enter if the last signal value was -1(negative) or 1(positive):");
                writeData = bufferedReader.readLine();                      // take input bitstream
                int temp = Integer.parseInt(writeData);
                if(temp == 1){
                    lastSignalValue = 1;
                }
                else
                {
                    lastSignalValue = -1;
                }
                System.out.println("Enter the total number of 1's before the input bitstream:");
                writeData = bufferedReader.readLine();                       // take input bitstream
                temp = Integer.parseInt(writeData);
                if((temp % 2) == 1){
                    tot_one  = 1;
                }
                else{
                    tot_one = 0;
                }
                System.out.println("[Client console] Input Bitstream: " + inputBits + "\nAssuming lastSignalValue and tot_one to be: " + lastSignalValue + ", " + tot_one);
                writeData = Processing.parityBits(inputBits);
                if(writeData.startsWith("Error")){                          // Skip next part in case of error
                    System.out.println(writeData);
                    continue;
                }
                System.out.println("1D form of 2D parity:" + writeData);
                writeData = Processing.HDB3Encoding(writeData, lastSignalValue, tot_one); // add parity bits and encode
                System.out.println("[Client console] Sending to Server: " + writeData);
                System.out.println("Add error? 0| No  \n\t\t   1| Yes");

                temp = Integer.parseInt(bufferedReader.readLine());
                if(temp == 1){
                    int length = writeData.length();
                    // new Random().nextInt(length);
                    int numOfErrors = 3;
                    System.out.println("Introducing " + numOfErrors + " errors.");
                    for(int i = 0; i < numOfErrors;){
                        int at = (new Random().nextInt(length));
                        char ch = writeData.charAt(at);
                        if(ch == '+' || ch == '-' || ch == '0'){
                            System.out.println("Changing index:" + at);
                            if(ch == '+'){
                                writeData = writeData.substring(0,at) + "-"+ writeData.substring(at+1, length-1);
                            }
                            else if(ch == '-'){
                                writeData = writeData.substring(0,at) + "+"+ writeData.substring(at+1, length-1);
                            }
                            else{
                                writeData = writeData.substring(0,at) + "+5, "+ writeData.substring(at+1,length-1);
                            }
                            i++;
                        }
                    }
                }
                outputStream.writeUTF(writeData);
                outputStream.flush();   // send the input bitstream data to server
                if(lastSignalValue == -1){                                  // lastSignalValue-tot_one = (-1,0)-> 0, (-1,1)->1, (1,0) -> 2, (1,1) -> 3
                    if(tot_one == 0){
                        outputStream.writeInt(0);
                    }else{
                        outputStream.writeInt(1);
                    }
                }else{
                    if(tot_one == 0){
                        outputStream.writeInt(2);
                    }else{
                        outputStream.writeInt(3);
                    }
                }
                outputStream.flush();                                                // send choices to server
                readData = inputStream.readUTF();
                System.out.println("[Client Console] Server says: " + readData);    // print the data server sent
            }
        }catch (IOException i){
            System.out.println("Cannot connect. Server is not live.");
           // i.printStackTrace();
        }
        finally {
            if(outputStream != null && socket != null)
            {
                try
                {
                    outputStream.close();
                    socket.close();
                }catch (IOException err)
                {
                    err.printStackTrace();
                }
            }
        }
    }
    public static void main(String[] args) {
        Client client = new Client();
    }
}
