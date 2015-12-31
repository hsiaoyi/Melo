package com.hsiaoyi.melo;

import java.io.File;
import java.io.IOException;
import java.util.Currency;
import java.util.Locale;
import java.util.UUID;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.hsiaoyi.melo.util.Encryption;
import com.hsiaoyi.melo.util.FileUtil;
import android.os.Environment;
import android.os.Build;
import android.content.Context;
import android.content.pm.PackageManager.NameNotFoundException;
import android.provider.Settings.Secure;

public class MLUtility {
    public static String getUDIDForVendor(String path, String secretKey) {
        String filePath = Identifier.getSavePath(path);
        File file = new File(filePath);
        String ret = null;

        if (file.exists()) {
            try {
                String encrypted = FileUtil.readFile(filePath);
                ret = Encryption.decryptStr(encrypted, secretKey);
            } catch (IOException e) {
                e.printStackTrace();
                return null;
            }
        } else {
            try {
                ret = UUID.randomUUID().toString();
                String encrypted = Encryption.encryptStr(ret, secretKey);
                FileUtil.writeFile(encrypted, filePath);
            } catch (IOException e) {
                e.printStackTrace();
                return null;
            }
        }

        String androidId = Secure.getString(Cocos2dxActivity.getContext().getContentResolver(), Secure.ANDROID_ID);
        return ret + ":" + androidId;
    }

    public static String getDevice() {
        return Build.MANUFACTURER;
    }

    public static String getDeviceName() {
        return Build.MODEL;
    }

    public static String getOSVersion() {
        return Build.VERSION.RELEASE;
    }

    public static String getAppVersionName() {
        Context context = Cocos2dxActivity.getContext();
        try {
            return context.getPackageManager().getPackageInfo(context.getPackageName(), 0).versionName;
        } catch (NameNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String getAppVersionCode() {
        Context context = Cocos2dxActivity.getContext();
        try {
            Integer versionCode = context.getPackageManager().getPackageInfo(context.getPackageName(), 0).versionCode;
            return versionCode.toString();
        } catch (NameNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String getCountryCode() {
        return Locale.getDefault().getCountry();
    }

    public static String getCurrencyCode() {
        try {
            Currency currency = Currency.getInstance(Locale.getDefault());
            return currency.getCurrencyCode();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
            return "";
        }
    }

    public static String getAdvertisementID() {
        try {
            Context context = Cocos2dxActivity.getContext();
            Info adInfo = AdvertisingIdClient.getAdvertisingIdInfo(context);
            if ( !adInfo.isLimitAdTrackingEnabled() ) {
                return adInfo.getId();
            }
        } catch (IOException e) {
        } catch (GooglePlayServicesNotAvailableException e) {
        } catch (GooglePlayServicesRepairableException e) {
        }

        return "";
    }

    public static String getIdentifier(String path, String secretKey) {
        String filePath = getSavePath(path);

        File file = new File(filePath);
        String ret = null;

        if (file.exists()) {
            try {
                String encrypted = FileUtil.readFile(filePath);
                ret = Encryption.decryptStr(encrypted, secretKey);
            } catch (IOException e) {
                e.printStackTrace();
                return null;
            }
        }

        return ret;
    }

    public static boolean setIdentifier(String path, String identifier, String secretKey) {
        String filePath = getSavePath(path);

        try {
            String encrypted = Encryption.encryptStr(identifier, secretKey);
            FileUtil.writeFile(encrypted, filePath);
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }

    public static boolean deleteIdentifier(String path) {
        String filePath = getSavePath(path);
        File file = new File(filePath);

        if (file.exists()) {
            return file.delete();
        } else {
            return false;
        }
    }

    public static boolean hasIdentifier(String path) {
        String filePath = getSavePath(path);
        File file = new File(filePath);

        return file.exists();
    }

    public static String getSavePath(String path) {
        String packageName = Cocos2dxActivity.getContext().getPackageName();
        String internalFilePath = Cocos2dxActivity.getContext().getFilesDir() + "/." + packageName + "/" + path;
        String externalFilePath = Environment.getExternalStorageDirectory() + "/."+ packageName + "/" + path;
        File internalFile = new File(internalFilePath);
        File externalFile = new File(externalFilePath);
        if (internalFile.exists()) {
            return internalFilePath;
        }
        if (externalFile.exists()) {
            return externalFilePath;
        }
        if (!isExternalStorageWritable()) {
            return internalFilePath;
        }
        return externalFilePath;
    }

    private static boolean isExternalStorageWritable() {
        String state = Environment.getExternalStorageState();
        if (Environment.MEDIA_MOUNTED.equals(state)) {
            return true;
        }
        return false;
    }

    public static String getCertKey() {
        Context context = Cocos2dxActivity.getContext();
        try {
            return context.getPackageManager().getPackageInfo(context.getPackageName(), 0).versionName;
        } catch (NameNotFoundException e) {
            e.printStackTrace();
        }

        return "";
    }

    public static String getSha1() {
        Context context = Cocos2dxActivity.getContext();
        try {
            return context.getPackageManager().getPackageInfo(context.getPackageName(), 0).versionName;
        } catch (NameNotFoundException e) {
            e.printStackTrace();
        }

        return "";
    }
}
