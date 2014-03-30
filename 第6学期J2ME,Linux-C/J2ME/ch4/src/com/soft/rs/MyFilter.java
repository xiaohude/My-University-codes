package com.soft.rs;

import javax.microedition.rms.RecordFilter;

public class MyFilter implements RecordFilter {

	public boolean matches(byte[] rsData) {
		String s = new String(rsData);
		
		if (s.indexOf("3") != -1) {
			return true;
		}
		
		return false;
	}

}
