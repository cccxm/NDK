package com.github.cccxm.ndk.view;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import com.github.cccxm.ndk.R;
import com.github.cccxm.ndk.lib.JniCallbackLib;

/**
 * 陈小默 16/11/1.
 */

public class JniCallbackActivity extends AppCompatActivity {
    private int count = 0;
    private TextView tv;

    @Override

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_callback);
        tv = (TextView) findViewById(R.id.tv_jni_callback);

        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                JniCallbackLib.callback(JniCallbackActivity.this);
            }
        });
    }

    public void setText(int nCount) {
        count = nCount;
        tv.setText("" + count);
    }

    public int getCount() {
        return count;
    }
}
