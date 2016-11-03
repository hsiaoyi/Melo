package com.hsiaoyi.melo;

import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Currency;
import java.util.Locale;
import java.util.UUID;
import java.util.Date;
import java.util.TimeZone;
import java.util.Formatter;

import java.lang.Exception;
import java.text.ParseException;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

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
    static final String TAG = "MLUtility";

    public static String getUDIDForVendor(String path, String secretKey) {
        FileUtil.checkMultiStorage(path);
        String encrypted = FileUtil.readFromMultiStorage(path);
        String ret = null;

        if (encrypted != null) {
            ret = Encryption.decryptStr(encrypted, secretKey);
        }

        if (ret == null) {
            ret = UUID.randomUUID().toString();
            encrypted = Encryption.encryptStr(ret, secretKey);
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

    static final String DATEFORMAT = "yyyy-MM-dd HH:mm:ss";

    public static Date GetUTCdatetimeAsDate()
    {
        return StringDateToDate(GetUTCdatetimeAsString());
    }

    public static String GetUTCdatetimeAsString()
    {
        final SimpleDateFormat sdf = new SimpleDateFormat(DATEFORMAT);
        sdf.setTimeZone(TimeZone.getTimeZone("UTC"));
        final String utcTime = sdf.format(new Date());

        return utcTime;
    }

    public static Date StringDateToDate(String StrDate)
    {
        Date dateToReturn = null;
        SimpleDateFormat dateFormat = new SimpleDateFormat(DATEFORMAT);
        try 
        {
            dateToReturn = (Date)dateFormat.parse(StrDate);
        }
        catch (ParseException e)
        {
            e.printStackTrace();
        }

        return dateToReturn;
    }

    public static String getCertCode(int rndCode, String secretKey) {
        Log.d(TAG, "getCertCode in");
        Date date = GetUTCdatetimeAsDate();
        if ( date != null )
        {
            int iYMD = (date.getYear() + 1900) * 10000 + ((date.getMonth() + 1) * 100) + date.getDate();
            int iDay = date.getDate();
            int iHour = date.getHours();
            int iMinute = date.getMinutes();
            int iMin = (int)(iMinute / 10);

            Log.d(TAG, "iYMD/iDay/iHour/iMinute/iMin = " + iYMD + "/" + iDay + "/" + iHour + "/" + iMinute + "/" + iMin);

            String udidStr = getUDIDForVendor(".superidol", secretKey);
            Log.d(TAG, "getUDIDForVendor : " + udidStr);
            String strNum1 = udidStr.substring(0,4);
            String strNum2 = udidStr.substring(4,8);
            int myPhone1 = Integer.parseInt(strNum1, 16);
            int myPhone2 = Integer.parseInt(strNum2, 16);

            Log.d(TAG, "strNum1 : " + strNum1);
            Log.d(TAG, "strNum2 : " + strNum2);
            Log.d(TAG, "rndCode : " + rndCode);
            Log.d(TAG, "myPhone1 : " + myPhone1);
            Log.d(TAG, "myPhone2 : " + myPhone2);
                
            long shaNumber = myPhone1 * iDay + iYMD + myPhone2 * iMin + iHour * iMin * rndCode + rndCode;
            Log.d(TAG, "shaNumber : " + shaNumber);

            String shaStr = getSha1( String.valueOf(shaNumber), 10 );
            if ( shaStr.length() > 0 )
            {
                Log.d(TAG, "getSha1 return : " + shaStr);
                return shaStr;
            }
        }
        Log.d(TAG, "getCertCode : 9999");
        return "9999";
    }

    public static String bytesToHex( byte[] bytes )
    {
        Formatter formatter = new Formatter();
        for (byte b : bytes)
        {
            formatter.format("%02x", b);
        }
        String result = formatter.toString();
        formatter.close();
        return result;
    }

    public static String getSha1(String shaNumber, int digist) {
        String hash = null;
        try
        {
            MessageDigest digest = MessageDigest.getInstance( "SHA-1" );
            digest.reset();
            digest.update(shaNumber.getBytes("UTF-8"));
            hash = bytesToHex( digest.digest() );
        }
        catch( NoSuchAlgorithmException e )
        {
            e.printStackTrace();
        }
        catch( UnsupportedEncodingException e )
        {
            e.printStackTrace();
        }
        return hash;
    }
}
