using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.OleDb;

namespace 学校管理系统.customerClass
{
    class insertData
    {
        bool insertState = false;
        public insertData(string sql) {
            OleDbConnection con = new dataInterFace().getODConn();
            OleDbCommand jay = new OleDbCommand(sql,con);
            int str = jay.ExecuteNonQuery();
            if (str > 0) {
                insertState = true;
            }
            jay.Dispose();
            con.Close();
            con.Dispose();
        }
        public bool insertDataState() {
            return insertState;
        }
    }
}
