using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.OleDb;

namespace 学校管理系统.customerClass
{
    class readData
    {
        public readData() { 
            
        }
        public bool getString(string sql)
        {
            DataTable dt = getDataString(sql);
            if (dt.Rows.Count == 0)
            {
                return false;
            }
            else {
                return true;
            }
        }
        public DataTable getDataString(string sql) {
            OleDbConnection odc = new dataInterFace().getODConn();
            //OleDbCommand  只执行增删改
            OleDbDataAdapter oda = new OleDbDataAdapter(sql, odc);
            DataTable dt = new DataTable();
            oda.Fill(dt); 
            oda.Dispose();
            odc.Close();
            odc.Dispose();
           
            return dt;
        }
    }
}
