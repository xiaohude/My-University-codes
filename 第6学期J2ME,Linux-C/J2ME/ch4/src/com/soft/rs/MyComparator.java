package com.soft.rs;

import javax.microedition.rms.RecordComparator;

public class MyComparator implements RecordComparator {

	public int compare(byte[] rsData1, byte[] rsData2) {
		String s1 = new String(rsData1);
		String s2 = new String(rsData2);
		
		int res = s1.compareTo(s2);
		if (res < 0) {
			return RecordComparator.PRECEDES;
		} else if (res > 0) {
			return RecordComparator.FOLLOWS;
		}
		
		return 0;
	}

}
