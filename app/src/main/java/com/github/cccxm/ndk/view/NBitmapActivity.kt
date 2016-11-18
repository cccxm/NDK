package com.github.cccxm.ndk.view

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import com.github.cccxm.ndk.R
import com.github.cccxm.ndk.lib.NBitmapLib
import kotlinx.android.synthetic.main.activity_nbitmap.*

class NBitmapActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_nbitmap)

        val bitmap = BitmapFactory.decodeResource(resources, R.drawable.hy)
        val jni_bitmap = bitmap.copy(Bitmap.Config.ARGB_4444, true)

        var startTime = System.currentTimeMillis()
        NBitmapLib.renderGray(jni_bitmap)
        Log.e("---time----", "JNI Time:${System.currentTimeMillis() - startTime}")
        native_to_gray.setImageBitmap(jni_bitmap)

        val java_bitmap = bitmap.copy(Bitmap.Config.ARGB_4444, true)

        startTime = System.currentTimeMillis()
        NBitmapLib.javaRenderGray(java_bitmap)
        //kotlinRenderGray(java_bitmap)
        Log.e("---time----", "Java Time:${System.currentTimeMillis() - startTime}")
        java_to_gray.setImageBitmap(java_bitmap)
    }

    fun kotlinRenderGray(bitmap: Bitmap) {
        val MODEL = 0xFF
        val height = bitmap.height
        val width = bitmap.width

        val pixelArray = IntArray(width * height)
        bitmap.getPixels(pixelArray, 0, width, 0, 0, width, height)
        var color: Int
        var av: Int
        for (i in pixelArray.indices) {
            color = pixelArray[i]
            av = 0
            av += color and MODEL
            av += color shr 8 and MODEL
            av += color shr 16 and MODEL
            av /= 3
            color = 0xFF00 + av
            color = (color shl 8) + av
            color = (color shl 8) + av
            pixelArray[i] = color
        }
        bitmap.setPixels(pixelArray, 0, width, 0, 0, width, height)
    }
}
