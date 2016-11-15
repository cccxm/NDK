package com.github.cccxm.ndk.view;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.github.cccxm.ndk.R;

/**
 * 陈小默 16/11/1.
 */

public class HelloJavaActivity extends AppCompatActivity {
    private TextView tv;

    @Override

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_callback);
        tv = (TextView) findViewById(R.id.tv_jni_callback);

        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                callback();
            }
        });
    }

    public void setText(int count) {
        tv.setText("" + count);
    }

    public native void callback();
}
