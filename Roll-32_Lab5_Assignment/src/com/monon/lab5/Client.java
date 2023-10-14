package com.deeparghya.lab5;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    Socket clientSocket = null;
    DataOutputStream outputStream = null;
    DataInputStream inputStream = null;
    Scanner scanner;

    public Client(String address, int port) {

        // Take user input via console
        scanner = new Scanner(System.in);

        try {

            // Create a new socket and attempt to connect to the server
            clientSocket = new Socket(address, port);

            // Create the streams required for data transfer
            outputStream = new DataOutputStream(clientSocket.getOutputStream());
            inputStream = new DataInputStream(clientSocket.getInputStream());

            String input, CRCrem, CRCString, encodedString, response;

            Corruptor corruptor;

            while (true) {

                System.out.println("[Client] Enter your input: ");
                input = scanner.nextLine();
                System.out.println("[Client] Given input (Dataword): " + input);


                // Stop signal handling

                if (input.toUpperCase().equals("STOP")) {
                    outputStream.writeUTF(input);
                    outputStream.flush();
                    System.out.println("[Client] Service stopped.");
                    break;
                }

                try {

                    CRCrem = Processor.generateCRC16(input);
                    System.out.println("[Client] CRC-16 Checkword: " + CRCrem);
                    CRCString = input + CRCrem;
                    System.out.println("[Client] CRC-16 Codeword: " + CRCString);

                    System.out.println("[Client] Test corruption?\n(1) Single-bit\n(2) Two isolated bits\n(3) Odd\n(4) Burst\n(0) None");

                    corruptor = new Corruptor(CRCString);
                    String corruptOpt = scanner.nextLine();
                    String corruptedString;

                    switch (corruptOpt) {
                        case "1":
                            corruptedString = corruptor.getCorrupteddString(Corruptor.CorruptionType.SINGLE);
                            break;
                        case "2":
                            corruptedString = corruptor.getCorrupteddString(Corruptor.CorruptionType.TWO_ISOLATED);
                            break;
                        case "3":
                            corruptedString = corruptor.getCorrupteddString(Corruptor.CorruptionType.ODD);
                            break;
                        case "4":
                            System.out.println("[Client] Enter burst size: ");
                            int burstSize = Integer.parseInt(scanner.nextLine());
                            if (burstSize > CRCString.length()) {
                                System.out.println("[ClientWarn] Burst size too big, maximum burst selected.");
                                burstSize = CRCString.length();
                            }
                            corruptedString = corruptor.getCorrupteddString(Corruptor.CorruptionType.BURST, burstSize);
                            break;
                        case "0":
                            corruptedString = CRCString;
                            break;
                        default:
                            System.out.println("[Client] Invalid option. Default option selected: No");
                            corruptedString = CRCString;
                            break;
                    }

                    System.out.println("[Client] String after corruption: " + corruptedString);
                    encodedString = Processor.manchesterEncoding(corruptedString);
                    System.out.println("[Client] Encoded voltage levels: " + encodedString);

                } catch (Exception e) {
                    System.out.println("[ClientError] " + e.getMessage());
                    outputStream.writeUTF("ERROR");
                    continue;
                }

                // Send data to server after encoding
                System.out.println("[Client] Sending data to server...");
                outputStream.writeUTF(encodedString);
                System.out.println("[Client] Data sent.");
                outputStream.flush();
                response = inputStream.readUTF();
                System.out.println("[Client] Received data: " + response);

            }

            // Close the streams
            outputStream.close();
            clientSocket.close();

        } catch(IOException i) {
            System.out.println("[Client] Error connecting to server");
        }
    }

    public static void main(String[] args) {
        Client client = new Client("localhost", 8888);
        // 01001000010001010100110001010000
    }
}
