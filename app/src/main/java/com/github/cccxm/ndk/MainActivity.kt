package com.github.cccxm.ndk

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import com.github.cccxm.ndk.view.HelloJniActivity
import com.github.cccxm.ndk.view.HelloJavaActivity
import com.github.cccxm.ndk.view.NBitmapActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        btn_hello_jni.setOnClickListener {
            val intent = Intent(this, HelloJniActivity::class.java)
            startActivity(intent)
        }
        btn_jni_callback.setOnClickListener {
            val intent = Intent(this, HelloJavaActivity::class.java)
            startActivity(intent)
        }
        btn_jni_bitmap.setOnClickListener {
            val intent = Intent(this, NBitmapActivity::class.java)
            startActivity(intent)
        }
    }
}