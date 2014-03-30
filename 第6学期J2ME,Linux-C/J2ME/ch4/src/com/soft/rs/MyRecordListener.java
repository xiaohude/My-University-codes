package com.soft.rs;

import javax.microedition.rms.RecordListener;
import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreNotOpenException;

public class MyRecordListener implements RecordListener {

	public void recordAdded(RecordStore rs, int recordID) {
		try {
			System.out.println("rs: " + rs.getName());
		} catch (RecordStoreNotOpenException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("recordID: " + recordID);
	}

	public void recordChanged(RecordStore rs, int recordID) {
		// TODO Auto-generated method stub

	}

	public void recordDeleted(RecordStore rs, int recordID) {
		

	}

}
