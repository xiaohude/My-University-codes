package com.soft.rs;

import javax.microedition.rms.InvalidRecordIDException;
import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;
import javax.microedition.rms.RecordStoreFullException;
import javax.microedition.rms.RecordStoreNotFoundException;
import javax.microedition.rms.RecordStoreNotOpenException;

public class RSUtil {
	// 创建、打开记录库
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
	
	// 关闭记录库
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
	
	// 添加String类型的数据
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
	
	// 获取String类型的数据
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
	
	// 更新String类型的记录
	
	
	// 删除
}
