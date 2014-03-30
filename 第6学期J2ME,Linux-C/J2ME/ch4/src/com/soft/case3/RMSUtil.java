package com.soft.case3;

import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;
import javax.microedition.rms.RecordStoreFullException;
import javax.microedition.rms.RecordStoreNotFoundException;
import javax.microedition.rms.RecordStoreNotOpenException;

// ��װ��RMS�Ĳ���
public class RMSUtil {
	// �������򿪼�¼��
	/**
	 * @param rsName String���͵����ݣ������¼�������
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

	// �رռ�¼��
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

	public int addString(String rsName, String data) {
		RecordStore rs = this.openRS(rsName);
		
		int recordID = this.addString(rs, data);
		
		this.closeRS(rs);
		
		return recordID;
		
	}
}


