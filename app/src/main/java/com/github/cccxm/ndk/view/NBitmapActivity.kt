package com.github.cccxm.ndk.view

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Canvas
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.View
import com.github.cccxm.ndk.R
import com.github.cccxm.ndk.lib.NBitmapLib

class NBitmapActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(BitmapView(this))
    }

    class BitmapView(context: Context) : View(context) {

        private val mBitmap: Bitmap

        init {
            val bitmap = BitmapFactory.decodeResource(context.resources, R.drawable.cat)
            mBitmap = bitmap.copy(Bitmap.Config.ARGB_4444, true)
            val startTime = System.currentTimeMillis()
            NBitmapLib.renderGray(mBitmap)
            //NBitmapLib.javaRenderGray(mBitmap)
            //renderGray(mBitmap)
            Log.e("---time----", "Time:${System.currentTimeMillis() - startTime}")
        }

        fun renderGray(mBitmap: Bitmap) {
            val MODEL = 0xFF
            val height = mBitmap.height
            val width = mBitmap.width
            var av: Int
            var color: Int
            for (y in 0..height - 1)
                for (x in 0..width - 1) {
                    av = 0
                    color = mBitmap.getPixel(x, y)
                    av += color and MODEL
                    av += (color shr 8) and MODEL
                    av += (color shr 16) and MODEL
                    av /= 3
                    color = 0xFF00 + av
                    color = (color shl 8) + av
                    color = (color shl 8) + av
                    mBitmap.setPixel(x, y, color)
                }
        }

        override fun onDraw(canvas: Canvas) {
            canvas.drawBitmap(mBitmap, 0f, 0f, null)
        }
    }

}
