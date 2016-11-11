package com.github.cccxm.ndk.view

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.github.cccxm.ndk.R
import com.github.cccxm.ndk.lib.HelloJniLib
import kotlinx.android.synthetic.main.activity_hello_jni.*

class HelloJniActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_hello_jni)

        tv_hello_jni.text = HelloJniLib.helloJNI()
    }
}
