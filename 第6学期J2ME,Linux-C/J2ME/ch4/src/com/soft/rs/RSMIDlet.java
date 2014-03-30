package com.soft.rs;

import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;
import javax.microedition.rms.InvalidRecordIDException;
import javax.microedition.rms.RecordEnumeration;
import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;
import javax.microedition.rms.RecordStoreFullException;
import javax.microedition.rms.RecordStoreNotFoundException;
import javax.microedition.rms.RecordStoreNotOpenException;

public class RSMIDlet extends MIDlet {

	public RSMIDlet() {
		// TODO Auto-generated constructor stub
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		
		
			// 1. 打开、创建
			String rsName = "J2MEDB";
			
			RSUtil rsUtil = new RSUtil();
			
			RecordStore rs = rsUtil.openRS(rsName);
			
//			// 加载监听器
//			rs.addRecordListener(new MyRecordListener());
			
			
			
			// 3. 添加
//			int recordID = rsUtil.addString(rs, "232222");
//			System.out.println("id: " +  recordID);
			
//			
//			// 4. 获取
//			String dbData = rsUtil.getString(rs, recordID);
//			System.out.println("db data: " + dbData);
			
			
			// 遍历操作
			try {
				RecordEnumeration enumeration = rs.enumerateRecords(null, new MyComparator(), true);
			
			
				while (enumeration.hasNextElement()) {
					byte[] rsData = enumeration.nextRecord();
					
					System.out.println("readed from enumeration: " + new String(rsData));
				}
				
				
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
			
			
			// 2. 关闭
			rsUtil.closeRS(rs);
			
			
			
		
	}

}
