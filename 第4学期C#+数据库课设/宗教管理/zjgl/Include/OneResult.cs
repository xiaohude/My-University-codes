using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.OleDb;
using 学校管理系统.customerClass;

namespace 学校管理系统.Include
{
    class OneResult
    {
        public string OResult="";
        public OneResult(string sql,out string oneResult) 
        {
            OleDbConnection OneConn = new dataInterFace().getODConn();
            OleDbCommand OneComm = new OleDbCommand(sql, OneConn);
            OResult = OneComm.ExecuteScalar().ToString();
            OneComm.Dispose();
            OneConn.Dispose();
            OneConn.Close();

            oneResult = OResult;
        }
        public bool GetOneResultState()
        {
            if (OResult!="")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
