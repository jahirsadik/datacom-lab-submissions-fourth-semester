package com.monon.lab5;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    private Socket socket = null;
    private ServerSocket ss = null;
    private DataInputStream inputStream = null;
    private DataOutputStream outputStream = null;

    public Server(int port) {
        try {

            // Create a new ServerSocket on the specified port that would listen to incoming requests
            ss = new ServerSocket(port);
            System.out.println("[Server] Server is now live.");
            // Accept an incoming request
            socket = ss.accept();
            System.out.println("[Server] Connected to client.");

            // Create the streams required for data transfer
            inputStream = new DataInputStream(socket.getInputStream());
            outputStream = new DataOutputStream(socket.getOutputStream());

            String line;
            while (true) {

                // Get selected user inputs from the client
//                Processor.prevNonZero.set(inputStream.readBoolean());
//                Processor.isNonZeroEven.set(inputStream.readBoolean());

                line = inputStream.readUTF();

                if (line.toUpperCase().equals("STOP")) { // Special request to stop all services
                    break;
                } else if (line.toUpperCase().equals("ERROR")) { // Special request for error handling
                    continue;
                }

                System.out.println("[Server] Received data: " + line);

                try {

                    // HDB3 Decoding
                    String decodedString = Processor.manchesterDecoding(line);
                    System.out.println("[Server] Decoded bitstream: " + decodedString);

                    // Parity checking
                    System.out.println("[Server] Checking CRC-16...");
                    if (Processor.checkCRC16(decodedString)) {
                        System.out.println("[Server] CRC-16 check found no error.");
                    } else {
                        throw new Exception("CRC-16 check found errors.");
                    }

                    String actualData = decodedString.substring(0, decodedString.length() - 16);
                    System.out.println("[Server] Actual data: " + actualData);

                    // Sending back the decoded data
                    System.out.println("[Server] Sending response to client...");
                    outputStream.writeUTF(actualData);
                    System.out.println("[Server] Data sent.");

                } catch (Exception e) {
                    // Decoding/Parity errors
                    System.out.println("[ServerError] " + e.getMessage());
                    outputStream.writeUTF("ERROR"); // Send special signal for handling errors
                }
            }

            // Close the ServerSocket
            ss.close();
            System.out.println("[Server] Service stopped.");

        } catch(IOException i) {
            System.out.println("[Server] Connection error.");
        }
    }

    public static void main(String[] args) {
        Server server = new Server(8888);
    }
}
