package com.monon.lab5;
import java.util.HashSet;
import java.util.Random;

public class Corruptor {

    public enum CorruptionType {
        SINGLE, TWO_ISOLATED, ODD, BURST
    }

    Random random = new Random();

    String stringToCorrupt;
    char[] mutableString;
    HashSet<Integer> indicesToCorrupt = new HashSet<>();

    Corruptor(String stringToCorrupt) {
        this.stringToCorrupt = stringToCorrupt;
        mutableString = stringToCorrupt.toCharArray();
    }

    public String getCorrupteddString(CorruptionType corruptionType, int... burstSize) throws Exception {

        switch (corruptionType) {
            case SINGLE:
                return getSingleCorruption();
            case TWO_ISOLATED:
                return getTwoIsolatedCorruption();
            case ODD:
                return getOddCorruption();
            case BURST:
                if (burstSize.length >= 1) {
                    return getBurstCorruption(burstSize[0]);
                }
                else {
                    return getBurstCorruption(random.nextInt(stringToCorrupt.length()));
                }
            default:
                throw new Exception("[Corruptor] Invalid corruption type.");
        }
    }

    private String corruptIsolatedBits(int n) {

        while (indicesToCorrupt.size() < n) {
            int currentIndex = random.nextInt(stringToCorrupt.length());
            if (!indicesToCorrupt.contains(currentIndex + 1) && !indicesToCorrupt.contains(currentIndex - 1))
                indicesToCorrupt.add(currentIndex);
        }

        for (int corruptIndex : indicesToCorrupt) {
            mutableString[corruptIndex] = mutableString[corruptIndex] == '0' ? '1' : '0';
        }

        return new String(mutableString);

    }

    private String getSingleCorruption() {
        return corruptIsolatedBits(1);
    }

    private String getTwoIsolatedCorruption() {
        return corruptIsolatedBits(2);
    }

    private String getOddCorruption() {

        int oddNum;

        do {
            oddNum = random.nextInt(stringToCorrupt.length() / 2);
        } while (oddNum % 2 == 0);

        return corruptIsolatedBits(oddNum);
    }

    private String getBurstCorruption(int burstSize) {

        int startIndex;

        do {
            startIndex = random.nextInt(stringToCorrupt.length());
        } while (startIndex + burstSize > stringToCorrupt.length());

        for (int offset = 0; offset < burstSize; offset++) {
            mutableString[startIndex + offset] = mutableString[startIndex + offset] == '0' ? '1' : '0';
        }

        return new String(mutableString);

    }
}
