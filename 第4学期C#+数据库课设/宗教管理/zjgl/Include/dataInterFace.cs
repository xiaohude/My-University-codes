using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.OleDb;

namespace 学校管理系统.customerClass
{
    class dataInterFace
    {
        OleDbConnection ODConn;
        public dataInterFace() {
            ODConn = new OleDbConnection("provider=Microsoft.jet.oledb.4.0;data source=zj.mdb");
            ODConn.Open();
        }
        public OleDbConnection getODConn() {
            return ODConn;
        }
        public void closeConn() {
            ODConn.Close();
            ODConn.Dispose();
        }
    }
}
