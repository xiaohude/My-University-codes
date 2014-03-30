package com.soft.rs;

import javax.microedition.rms.InvalidRecordIDException;
import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;
import javax.microedition.rms.RecordStoreFullException;
import javax.microedition.rms.RecordStoreNotFoundException;
import javax.microedition.rms.RecordStoreNotOpenException;

public class RSUtil {
	// �������򿪼�¼��
	public  RecordStore openRS(String rsName) {
		try {
			if (rsName.length() < 32) {
				return RecordStore.openRecordStore(rsName, true);
			}
		} catch (RecordStoreFullException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (RecordStoreNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (RecordStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	
	// �رռ�¼��
	public  boolean closeRS(RecordStore rs) {
		try {
			rs.closeRecordStore();
			return true;
		} catch (RecordStoreNotOpenException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (RecordStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}
	
	// ���String���͵�����
	public int addString(RecordStore rs, String data) {
		byte[] temp = data.getBytes();
		
		try {
			return rs.addRecord(temp, 0, temp.length);
		} catch (RecordStoreNotOpenException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (RecordStoreFullException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (RecordStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return 0;
	}
	
	// ��ȡString���͵�����
	public String getString(RecordStore rs, int recordID) {
		try {
			return new String(rs.getRecord(recordID));
		} catch (RecordStoreNotOpenException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvalidRecordIDException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (RecordStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	
	// ����String���͵ļ�¼
	
	
	// ɾ��
}
