package com.monon.lab5;
import java.util.ArrayList;
import java.util.Arrays;

public class Processor {

    // Checks the integrity of the bitstream
    private static boolean bitStreamError(String bitStream) {

        int bitStreamSize = bitStream.length();

        for (int idx = 0; idx < bitStreamSize; idx++) {
            if (bitStream.charAt(idx) != '0' && bitStream.charAt(idx) != '1') {
                return true;
            }
        }

        return false;

    }

    public static String manchesterEncoding(String bitStream) throws Exception {

        if (bitStreamError(bitStream)) {
            throw new Exception("Invalid bitstream.");
        }

        int bitStreamLength = bitStream.length();
        StringBuilder encodedString = new StringBuilder();

        for (int idx = 0; idx < bitStreamLength; idx++) {

            if (bitStream.charAt(idx) == '0') {
                encodedString.append("+5V, -5V");
            } else {
                encodedString.append("-5V, +5V");
            }

            if (idx != bitStreamLength - 1) {
                encodedString.append(", ");
            }

        }

        return encodedString.toString();

    }

    public static String manchesterDecoding(String encodedString) throws Exception {

        // Split the string into individual voltage levels
        encodedString = encodedString.replace(" ", "").toUpperCase();
        ArrayList<String> voltages = new ArrayList<>(Arrays.asList(encodedString.split(",")));

        int voltagesSize = voltages.size();
        StringBuilder decodedString = new StringBuilder();

        // Check voltage level integrity
        for (String voltage : voltages) {
            if (!voltage.equals("+5V") && !voltage.equals("-5V")) {
                throw new Exception("Invalid voltage level.");
            }
        }

        for (int idx = 0; idx < voltagesSize; idx += 2) {
            if ((idx + 1 < voltagesSize) && voltages.get(idx).equals(voltages.get(idx + 1))) {
                throw new Exception("Invalid sequence.");
            }

            if (voltages.get(idx).equals("+5V")) {
                decodedString.append('0');
            } else {
                decodedString.append('1');
            }
        }

        return decodedString.toString();

    }

    public static String stringXOR(String a, String b) throws Exception {

        if (a.length() != b.length()) {
            throw new Exception("[Processor] String lengths must be the same!");
        }

        int range = a.length();
        StringBuilder xored = new StringBuilder();

        for (int idx = 0; idx < range; idx++) {
            if (a.charAt(idx) == b.charAt(idx)) {
                xored.append('0');
            } else {
                xored.append('1');
            }
        }

        return new String(xored);

    }

    public static String generateCRC16(String bitStream) throws Exception {

        if (bitStreamError(bitStream)) {
            throw new Exception("Invalid bitstream.");
        }

        int bitStreamLength = bitStream.length();
        String divisor = "10001000000100001";
//        String divisor = "1011";
        int divisorLength = divisor.length();
        char[] zeroes = new char[divisorLength];
        Arrays.fill(zeroes, '0');
        String divisorNeg = new String(zeroes);
        int lastCursor = divisorLength;
        String dividend = bitStream + "0000000000000000";
//        String dividend = bitStream + "000";
        String temp = dividend.substring(0, lastCursor);

        while (lastCursor < bitStreamLength + divisorLength - 1) {

            if (temp.charAt(0) == '1') {
                temp = stringXOR(temp, divisor).substring(1, divisorLength) + dividend.charAt(lastCursor);

            } else {
                temp = stringXOR(temp, divisorNeg).substring(1, divisorLength) + dividend.charAt(lastCursor);
            }
            lastCursor++;
        }

        return temp.substring(1);

    }

    public static boolean checkCRC16(String bitStream) throws Exception {

        if (bitStreamError(bitStream)) {
            throw new Exception("Invalid bitstream.");
        }

        int bitStreamLength = bitStream.length();
        String divisor = "10001000000100001";
//        String divisor = "1011";
        int divisorLength = divisor.length();

        char[] zeroes = new char[divisorLength];
        Arrays.fill(zeroes, '0');
        String divisorNeg = new String(zeroes);

        int lastCursor = divisorLength;
        String temp = bitStream.substring(0, lastCursor);

        while (lastCursor < bitStreamLength) {

            if (temp.charAt(0) == '1') {
                temp = stringXOR(temp, divisor).substring(1, divisorLength) + bitStream.charAt(lastCursor);

            } else {
                temp = stringXOR(temp, divisorNeg).substring(1, divisorLength) + bitStream.charAt(lastCursor);
            }
            lastCursor++;
        }

        System.out.println("[Processor] Syndrome: " + temp.substring(1));
        return temp.substring(1).equals(divisorNeg.substring(1));

    }

//    public static void main(String[] args) {
//
//        String dataWord = "01010";
//
//        try {
//            String augmented = generateCRC16(dataWord);
//            System.out.println(dataWord + augmented);
//            System.out.println(checkCRC16(dataWord + augmented));
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
//    }
}
