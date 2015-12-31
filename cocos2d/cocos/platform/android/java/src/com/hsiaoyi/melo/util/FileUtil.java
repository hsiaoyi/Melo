package com.hsiaoyi.melo.util;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

public class FileUtil {
    public static void writeFile(String str, String path) throws IOException {
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

    public static String readFile(String path) throws IOException {
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
}
