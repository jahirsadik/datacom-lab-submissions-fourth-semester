package com.company;

import java.net.*;
import java.io.*;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;

public class Server {
    private Socket socket = null;
    private ServerSocket ss = null;
    private DataInputStream inputStream = null;
    private DataOutputStream outputStream = null;

    public Server (int port){
        try {
            int lastSignalValue = -1;
            int tot_one = 0;
            ss = new ServerSocket(port);
            System.out.println("[Server Console] Waiting for client.!\n");
            socket = ss.accept();           // wait for client and accept when client requests
            inputStream = new DataInputStream(socket.getInputStream());
            outputStream = new DataOutputStream(socket.getOutputStream());
            //BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
            String writeData = "", readData = "";
            while (true){
                readData = inputStream.readUTF();
                if(readData.equals("stop")){
                    System.out.println("[Server Console] Stopping the server side program.");
                    break;
                }
                int temp = inputStream.readInt();
                if(temp == 3){                  // lastSignalValue-tot_one = (-1,0)-> 0, (-1,1)->1, (1,0) -> 2, (1,1) -> 3
                    lastSignalValue = 1;
                    tot_one = 1;
                }else if(temp == 2){
                    lastSignalValue = 1;
                    tot_one = 0;
                }else if(temp == 1){
                    lastSignalValue = -1;
                    tot_one = 1;
                }else{
                    lastSignalValue = -1;
                    tot_one = 0;
                }
                System.out.println("[Server Console] Received At Server: " + readData);
                readData = Processing.HDB3Decoding(readData, lastSignalValue, tot_one); // decode the code
                System.out.println("Assuming lastSignalValue and tot_one to be: " + lastSignalValue + ", " + tot_one);
                System.out.println("[Server Console] After Decoding: " + readData);
                ArrayList<String> outputData = new ArrayList<>();
                outputData = Processing.ParityChecker(readData); // check the parity bits to see if errors occured
                if(outputData.get(0).startsWith("Error")){
                    System.out.println("Error at receiver. Error: " + outputData);
                }
                else
                {
                    System.out.println("[Server Console] Final Output: " + outputData);
                }
                outputStream.writeUTF("[Data received at server] Final Output: " + outputData);
                outputStream.flush();
            }
        } catch(IOException i){
            i.printStackTrace();
        }
        finally {
            try{
                if(outputStream != null && socket != null && ss != null)
                {
                    outputStream.close();
                    socket.close();
                    ss.close();
                }
            }
            catch (IOException err)
            {
                err.printStackTrace();
            }
        }
    }

    public static void main(String[] args){
        Server myserver = new Server(9999);
    }

}
