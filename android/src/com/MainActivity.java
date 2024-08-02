package com.MyActivity;
import org.qtproject.qt.android.QtNative;
import org.qtproject.qt.android.bindings.QtActivity;
import java.io.File;
import java.io.IOException;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.ByteArrayOutputStream;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Environment;
import android.content.Intent;
import android.content.Context;
import android.content.ContentValues;
import android.content.ContentResolver;
import android.content.res.Configuration;
import android.content.pm.PackageManager;
import android.content.pm.ApplicationInfo;
import android.app.Activity;
import android.app.Notification;
import android.app.PendingIntent;
import android.app.UiModeManager;
import android.app.NotificationManager;
import android.app.NotificationChannel;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Canvas;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.BitmapDrawable;
import android.provider.Settings;
import android.provider.MediaStore;
import android.widget.Toast;
import android.util.Log;
import android.net.Uri;
import androidx.core.content.FileProvider;
public class MainActivity extends org.qtproject.qt.android.bindings.QtActivity{
    private static MainActivity m_instance;

    public static native void onConfigurationChanged_native(Configuration newConfig);
    @Override
    public void onConfigurationChanged(Configuration newConfig)
    {
        super.onConfigurationChanged(newConfig);
        m_instance.onConfigurationChanged_native(newConfig);
    }
     public MainActivity()
     {
          m_instance = this;
     }
}
