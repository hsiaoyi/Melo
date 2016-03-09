package com.hsiaoyi.melo.util;

import android.os.Environment;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Vector;

public class FileUtil {
    private static void writeFile(String str, String path) throws IOException {
        File file = new File(path);
        file.getParentFile().mkdir();

        FileOutputStream fos = null;

        try {
            fos = new FileOutputStream(file, false);
            OutputStreamWriter osw = null;
            try {
                osw = new OutputStreamWriter(fos, "UTF-8");
                BufferedWriter bw = null;
                try {
                    bw = new BufferedWriter(osw);
                    bw.write(str);
                    bw.flush();
                } finally {
                    if (bw != null) bw.close();
                }
            } finally {
                if (osw != null) osw.close();
            }
        } finally {
            if (fos != null) fos.close();
        }
    }

    private static String readFile(String path) throws IOException {
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
            paths.add(Environment.getExternalStorageDirectory() + "/."+ packageName + "/" + path);
        }

        ret = new String[paths.size()];

        paths.toArray(ret);

        return ret;
    }

    private static String getLoadPath(String path) {
        String[] paths = getSavePaths(path);
        File loadFile = null;

        for (String loadPath : paths) {
            File file = new File(loadPath);

            if (file.exists()) {
                loadFile = file;
                break;
            }
        }

        if (loadFile == null) return "";

        return loadFile.getPath();
    }

    private static boolean isExternalStorageWritable() {
        String state = Environment.getExternalStorageState();
        if (Environment.MEDIA_MOUNTED.equals(state)) {
            return true;
        }
        return false;
    }
}
