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

import com.google.android.gms.ads.identifier.AdvertisingIdClient;
import com.google.android.gms.ads.identifier.AdvertisingIdClient.Info;

import com.google.android.gms.common.GooglePlayServicesNotAvailableException;
import com.google.android.gms.common.GooglePlayServicesRepairableException;

import android.util.Log;

public class MLUtility {
    public static String getUDIDForVendor(String path, String secretKey) {
        String encrypted = FileUtil.readFromMultiStorage(path);
        String ret;

        if (encrypted == null) {
            ret = UUID.randomUUID().toString();
            encrypted = Encryption.encryptStr(ret, secretKey);
        } else {
            ret = Encryption.decryptStr(encrypted, secretKey);
        }

        FileUtil.writeToMultiStorage(encrypted, path);

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
        String encrypted = FileUtil.readFromMultiStorage(path);
        String ret = null;

        if (encrypted != null) {
            FileUtil.writeToMultiStorage(encrypted, path);

            ret = Encryption.decryptStr(encrypted, secretKey);
        }

        return ret;
    }

    public static boolean setIdentifier(String path, String identifier, String secretKey) {
        String encrypted = Encryption.encryptStr(identifier, secretKey);

        return FileUtil.writeToMultiStorage(encrypted, path);
    }

    public static boolean deleteIdentifier(String path) {
        return FileUtil.deleteMultiStorage(path);
    }

    public static boolean hasIdentifier(String path) {
        return FileUtil.checkMultiStorage(path);
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
