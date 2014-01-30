package com.sample.insertwebview;

import com.sample.insertweb.R;
import com.sample.insertwebview.util.CustomWebView;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.NativeActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainNativeOne extends NativeActivity {

	WebView m_webView;
	FrameLayout m_webLayout;
	LinearLayout m_topLayout;
	Button m_backButton;
	Dialog dialog;
	static MainNativeOne oneActivity = null;

	public static MainNativeOne getInstance() {
		Log.v("TestJacky", "getInstance");
		return oneActivity;
	}

	public MainNativeOne() {
		super();
		oneActivity = this;
	}

	public void showDialog() {
		runOnUiThread(new Runnable() {
			public void run() {
				new AlertDialog.Builder(MainNativeOne.this)
						.setIcon(android.R.drawable.ic_dialog_alert)
						.setTitle("ダイアログ")
						.setMessage("ダイアログのテストです")
						.setPositiveButton("OK",
								new DialogInterface.OnClickListener() {
									public void onClick(DialogInterface dialog,
											int whichButton) {

									}
								}).show();
			}
		});
	}

	public void openWebview() {
		this.runOnUiThread(new Runnable() {
			@SuppressLint({ "SetJavaScriptEnabled", "ResourceAsColor" })
			public void run() {
				dialog = new Dialog(MainNativeOne.this);
				dialog.getWindow().requestFeature(Window.FEATURE_NO_TITLE);
				dialog.getWindow().setFlags(
						WindowManager.LayoutParams.FLAG_FULLSCREEN,
						WindowManager.LayoutParams.FLAG_FULLSCREEN);
				dialog.getWindow().setBackgroundDrawable(
						new ColorDrawable(Color.TRANSPARENT));

				dialog.show();

				m_webLayout = new FrameLayout(MainNativeOne.this);
				FrameLayout.LayoutParams lytp = new FrameLayout.LayoutParams(
						600, 400);
				lytp.gravity = Gravity.CENTER;
				dialog.addContentView(m_webLayout, lytp);
				m_webView = new WebView(MainNativeOne.this);
				m_webView.getSettings().setJavaScriptEnabled(true);
				m_webView.getSettings().setSupportZoom(false);
				m_webView.getSettings().setBuiltInZoomControls(true);
				m_webView.setBackgroundResource(R.drawable.hello);
				m_webView.loadUrl("http://www.google.co.jp");
				m_webView.requestFocus();
				m_webView.setWebViewClient(new CustomWebView());

				m_topLayout = new LinearLayout(MainNativeOne.this);
				m_topLayout.setOrientation(LinearLayout.VERTICAL);
				m_backButton = new Button(MainNativeOne.this);
				m_backButton
						.setBackgroundResource(android.R.drawable.star_big_off);
				LinearLayout.LayoutParams lypt = new LinearLayout.LayoutParams(
						LinearLayout.LayoutParams.WRAP_CONTENT,
						LinearLayout.LayoutParams.WRAP_CONTENT);
				lypt.gravity = Gravity.RIGHT;
				m_backButton.setLayoutParams(lypt);
				m_backButton.setOnClickListener(new OnClickListener() {
					public void onClick(View v) {
						removeWebView();
					}
				});
				m_topLayout.addView(m_backButton);
				m_topLayout.addView(m_webView);
				m_webLayout.addView(m_topLayout);
			}
		});
	}

	public void removeWebView() {
		m_webLayout.removeView(m_topLayout);
		m_topLayout.destroyDrawingCache();

		m_topLayout.removeView(m_webView);
		m_webView.destroy();

		m_topLayout.removeView(m_backButton);
		m_backButton.destroyDrawingCache();

		dialog.cancel();

		closeWebView();
	}

	public boolean onKeyDown(int keyCoder, KeyEvent event) {
		if(m_webView!=null)
		{
			if (m_webView.canGoBack() && keyCoder == KeyEvent.KEYCODE_BACK) {
				m_webView.goBack();
			} else {
				removeWebView();
			}
		}

		return false;
	}

	public void openOtherActivity() {
		runOnUiThread(new Runnable() {
			public void run() {
				Intent intent = new Intent(MainNativeOne.this,
						SubActivity.class);
				startActivity(intent);
			}
		});
	}

	public void insertLayoutByResoureId() {
		runOnUiThread(new Runnable() {
			public void run() {
				final Dialog dialog = new Dialog(oneActivity);
				dialog.setContentView(R.layout.open_by_resource);
				dialog.setTitle("ResourceDailog");

				TextView text = (TextView) dialog.findViewById(R.id.text);
				text.setText("Android custom dialog example!");
				ImageView image = (ImageView) dialog.findViewById(R.id.image);
				image.setImageResource(R.drawable.hello);

				Button dialogButton = (Button) dialog
						.findViewById(R.id.dialogButtonOK);
				dialogButton.setOnClickListener(new OnClickListener() {
					@Override
					public void onClick(View v) {
						dialog.dismiss();
					}
				});

				dialog.show();
			}
		});
	}

	private native int closeWebView();
}
