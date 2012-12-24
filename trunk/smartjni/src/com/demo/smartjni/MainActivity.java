package com.demo.smartjni;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {
	
	static{
		System.loadLibrary("smartjni");
	}
	
	private int mValue1 = 1;
	private static int mValue2 = 2;
	private static Integer mValue3 = 3;
	
	
	public int method1(Integer a,  Long b, int c, long d){
		Log.i("TTT", "the method1 was called." );
		return -1;
	}
	
	public static  void method2(Long a, int b){
		Log.i("TTT", "the method2 was called." );
	}
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		nativemethod();
 	}
	
	public native  void nativemethod();

}
