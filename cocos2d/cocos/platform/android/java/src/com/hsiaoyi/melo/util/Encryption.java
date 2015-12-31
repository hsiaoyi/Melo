package com.hsiaoyi.melo.util;

import java.security.GeneralSecurityException;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import android.util.Base64;
import android.util.Log;

public class Encryption {
    static final String TAG = Encryption.class.getSimpleName();
    static final String TRANSFORMATION = "AES";

    public static String encryptStr(String str, String secretKey) {
        byte[] strBytes = str.getBytes();
        byte[] secretKeyBytes = secretKey.getBytes();

        String ret = null;

        try {
            SecretKeySpec keySpec = new SecretKeySpec(secretKeyBytes, TRANSFORMATION);
            byte[] encryptedBytes = encryptBytes(strBytes, keySpec);
            // encode base64 because bytes size is changed when convert to String directly
            byte[] base64Bytes = Base64.encode(encryptedBytes, 0);
            ret = new String(base64Bytes);
            Log.d(TAG, "Encrypted string: " + ret);

            return ret;

        } catch (GeneralSecurityException e) {
            e.printStackTrace();
        }

        return ret;
    }

    public static String decryptStr(String str, String secretKey){
        byte[] encryptBytes = Base64.decode(str, 0);
        byte[] secretKeyBytes = secretKey.getBytes();

        String ret = null;

        try {
            SecretKeySpec keySpec = new SecretKeySpec(secretKeyBytes, TRANSFORMATION);
            byte[] decryptedBytes = decryptBytes(encryptBytes, keySpec);
            ret = new String(decryptedBytes);

            Log.d(TAG, "Decrypted string: " + ret);

            return ret;
        } catch (GeneralSecurityException e){
            e.printStackTrace();
        }

        return ret;
    }

    private static byte[] encryptBytes(byte[] src, SecretKeySpec skey) throws GeneralSecurityException {
        Cipher cipher = Cipher.getInstance(TRANSFORMATION);
        cipher.init(Cipher.ENCRYPT_MODE, skey);
        return cipher.doFinal(src);
    }

    private static byte[] decryptBytes(byte[] src, SecretKeySpec skey) throws GeneralSecurityException {
        Cipher cipher = Cipher.getInstance(TRANSFORMATION);
        cipher.init(Cipher.DECRYPT_MODE, skey);
        return cipher.doFinal(src);
    }
}
