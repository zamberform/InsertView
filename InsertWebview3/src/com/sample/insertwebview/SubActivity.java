package com.sample.insertwebview;

import com.sample.insertweb.R;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;

public class SubActivity extends Activity {

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		// TODO Auto-generated method stub
		finish();
		
		return super.onTouchEvent(event);
	}
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_sub);
	}

}
