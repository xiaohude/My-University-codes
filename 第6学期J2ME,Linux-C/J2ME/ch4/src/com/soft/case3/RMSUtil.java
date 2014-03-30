package com.soft.case3;

import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;
import javax.microedition.rms.RecordStoreFullException;
import javax.microedition.rms.RecordStoreNotFoundException;
import javax.microedition.rms.RecordStoreNotOpenException;

// 封装对RMS的操作
public class RMSUtil {
	// 创建、打开记录库
	/**
	 * @param rsName String类型的数据，代表记录库的名字
	 */
	private RecordStore openRS(String rsName) {
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
	private boolean closeRS(RecordStore rs) {
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

	public int addString(String rsName, String data) {
		RecordStore rs = this.openRS(rsName);
		
		int recordID = this.addString(rs, data);
		
		this.closeRS(rs);
		
		return recordID;
		
	}
}


