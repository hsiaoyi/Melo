package com.hsiaoyi.melo.util;

import android.os.Environment;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Vector;

import android.util.Log;

public class FileUtil {
    private static final String TMP_PREFIX = ".__tmp";
    static final String TAG = "FileUtil";

    private static void deleteTemporaryFile(File dir) {
        File[] files = dir.listFiles(new FilenameFilter() {
            @Override
            public boolean accept(File dir, String filename) {
                return filename.startsWith(TMP_PREFIX);
            }
        });

        for (File file : files) {
            file.delete();
        }
    }

    private static void writeFile(String str, String path) throws IOException {
        Log.d(TAG, "writeFile: " + str + " path : " + path);
        File file = new File(path);
        file.getParentFile().mkdirs();
        deleteTemporaryFile(file.getParentFile());

        File tmpFile = File.createTempFile(TMP_PREFIX, "", file.getParentFile());

        FileOutputStream fos = null;
        OutputStreamWriter osw = null;
        BufferedWriter bw = null;
        boolean tempWriteSucceeded = false;

        try {
            fos = new FileOutputStream(tmpFile, false);
            osw = new OutputStreamWriter(fos, "UTF-8");
            bw = new BufferedWriter(osw);
            bw.write(str);
            bw.flush();
            tempWriteSucceeded = true;
        } finally {
            if (bw != null) bw.close();
            if (osw != null) osw.close();
            if (fos != null) fos.close();
        }

        if (tempWriteSucceeded) {
            try {
                if (!tmpFile.renameTo(file)) {
                    throw new IOException("rename failed");
                }
            } catch(Exception e) {
                throw new java.io.IOError(e);
            }
        }
    }

    private static String readFile(String path) throws IOException {
        Log.d(TAG, "readFile: " + path);
        File file = new File(path);
        String ret = null;

        if (file.exists()) {
            FileInputStream fis = null;
            try {
                fis = new FileInputStream(file);
                byte[] readBytes = new byte[fis.available()];
                fis.read(readBytes);

                ret = new String(readBytes);
            } finally {
                if (fis != null) fis.close();
            }
        }
        return ret;
    }

    public static String readFromMultiStorage(String path) {
        String filePath = getLoadPath(path);
        Log.d(TAG, "readFromMultiStorage: " + filePath);
        File file = new File(filePath);
        String ret = null;

        if (file.exists()) {
            try {
                ret = readFile(filePath);
            } catch (IOException e) {
                e.printStackTrace();
                return null;
            }
        }

        return ret;
    }

    public static boolean writeToMultiStorage(String str, String path) {
        String[] paths = getSavePaths(path);
        boolean ret = true;

        for (String savePath : paths) {
            try {
                if (!str.equals(readFile(path))) {
                    writeFile(str, savePath);
                }
            } catch (IOException e) {
                ret = false;
            }
        }

        return ret;
    }

    public static boolean deleteMultiStorage(String path) {
        String[] paths = getSavePaths(path);
        boolean ret = true;

        for (String savePath : paths) {
            File file = new File(savePath);
            if (file.exists()) {
                if(!file.delete()){
                    ret = false;
                }
            }
        }

        return ret;
    }

    public static boolean checkMultiStorage(String path) {
        return !getLoadPath(path).isEmpty();
    }

    private static String[] getSavePaths(String path) {
        Log.d(TAG, "getSavePaths" + path);
        String packageName = Cocos2dxActivity.getContext().getPackageName();
        Vector<String> paths = new Vector<String>();
        String[] ret;

        String[] innerPaths = {
                Cocos2dxActivity.getContext().getFilesDir() + "/." + packageName + "/" + path,
                Cocos2dxActivity.getContext().getFilesDir() + "/"  + path
        };


        for (String innerPath : innerPaths) {
            try {
                File file = new File(innerPath).getParentFile();
                Log.d(TAG, "getSavePaths mkdirs : " + innerPath);
                file.mkdirs();
                file.setWritable(true);

                if (file.canWrite()) {
                    paths.add(innerPath);
                    break;
                }
            } catch (Exception e) {

            }
        }

        if (isExternalStorageWritable()) {
            String externPath = Environment.getExternalStorageDirectory() + "/."+ packageName + "/" + path;
            File file = new File(externPath).getParentFile();
            Log.d(TAG, "isExternalStorageWritable mkdirs : " + externPath);
            file.mkdirs();
            file.setWritable(true);
            if (file.canWrite()) {
                paths.add(externPath);
            }
        }

        ret = new String[paths.size()];

        paths.toArray(ret);

        return ret;
    }

    private static String getLoadPath(String path) {
        Log.d(TAG, "getLoadPath");
        String[] paths = getSavePaths(path);
        Log.d(TAG, "getLoadPath : " + paths);
        File loadFile = null;

        for (String loadPath : paths) {
            File file = new File(loadPath);

            if (file.exists()) {
                loadFile = file;
                break;
            }
        }

        if (loadFile == null) {
            return "";
        }

        return loadFile.getPath();
    }

    private static boolean isExternalStorageWritable() {
        String state = Environment.getExternalStorageState();
        if (Environment.MEDIA_MOUNTED.equals(state)) {
            Log.d(TAG, "isExternalStorageWritable : TRUE");
            return true;
        }
        return false;
    }
}
