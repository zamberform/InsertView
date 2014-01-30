package com.sample.insertwebview.util;

import android.annotation.SuppressLint;
import android.graphics.Bitmap;
import android.net.http.SslError;
import android.webkit.HttpAuthHandler;
import android.webkit.SslErrorHandler;
import android.webkit.WebView;
import android.webkit.WebViewClient;

@SuppressLint("NewApi")
public class CustomWebView extends WebViewClient {

	@Override
	public void onPageStarted(WebView view, String url, Bitmap favicon) {

	}

	@Override
	public void onPageFinished(WebView view, String url) {

	}

	@Override
	public void onReceivedError(WebView view, int errorCode,
			String description, String failingUrl) {
	}

	@Override
	public void onReceivedHttpAuthRequest(WebView view,
			HttpAuthHandler handler, String host, String realm) {
		// TODO Auto-generated method stub
		super.onReceivedHttpAuthRequest(view, handler, host, realm);
	}

	@Override
	public void onReceivedLoginRequest(WebView view, String realm,
			String account, String args) {
		// TODO Auto-generated method stub
		super.onReceivedLoginRequest(view, realm, account, args);
	}

	@Override
	public void onReceivedSslError(WebView view, SslErrorHandler handler,
			SslError error) {
		// TODO Auto-generated method stub
		super.onReceivedSslError(view, handler, error);
	}

	@Override
	public boolean shouldOverrideUrlLoading(WebView view, String url) {
		// TODO Auto-generated method stub
		//電話の番号特別処理
		if (url.indexOf("tel:") < 0) {
			view.loadUrl(url);
		}
		return super.shouldOverrideUrlLoading(view, url);
	}
	
}