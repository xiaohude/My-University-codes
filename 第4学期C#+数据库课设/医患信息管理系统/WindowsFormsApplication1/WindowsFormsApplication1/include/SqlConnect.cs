

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;      //连接SQL数据库
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MarketManage
{
    /// <summary>
    /// 封装数据库操作
    /// </summary>
    class SqlConnect
    {
        private string sqlConnString;//数据库连接字符串
        private SqlConnection sqlConn = new SqlConnection(); //SQL数据库连接对象

        private ConnectionState sqlConnPreState = ConnectionState.Closed;//原来数据库的连接状态

        /// <summary>
        /// 数据库连接字符串属性
        /// </summary>
        public string SqlConnectionString
        {
            get { return sqlConnString; }
            set
            {
                sqlConnString = value;
                sqlConn.ConnectionString = sqlConnString;
            }
        }


        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="strSqlCon">数据库连接字符串</param>
        public SqlConnect()
        {
            sqlConn.ConnectionString = "server=XIAOHU-PC;database=yyxx;uid=sa;pwd=sa ";
        }

        /// <summary>
        /// 析构函数
        /// </summary>
        ~SqlConnect()
        {
            try
            { sqlConn.Dispose();
                sqlConn.Close();
               
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        /// <summary>
        /// 打开数据库连接
        /// </summary>
        public void Open()
        {
            try
            {
                if (sqlConn.State == ConnectionState.Closed)
                {
                    sqlConn.Open();
              //    MessageBox.Show("连接成功!");
                    sqlConnPreState = ConnectionState.Open;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        /// <summary>
        /// 关闭数据库连接
        /// </summary>
        public void Close()
        {
            try
            {
                if (sqlConn.State != ConnectionState.Closed)
                {
                    sqlConn.Close();
                    sqlConnPreState = ConnectionState.Closed;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        /// <summary>
        /// 获取查询数据的数据表
        /// </summary>
        /// <param name="strSQL">要查询的SQL语句</param>
        /// <param name="parametes">传入的参数,无参数时使用NULL</param>
        /// <returns></returns>
        public DataTable GetDataTable(string strSQL, params SqlParameter[] parametes)
        {
            DataSet ds = new DataSet();
            DataTable dt = new DataTable();

            try
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State == ConnectionState.Closed)
                //若原来的状态为关闭且当前连接未打开,则打开
                {
                    sqlConn.Open();
                }

                SqlCommand sqlCmd = sqlConn.CreateCommand();
                sqlCmd.CommandText = strSQL;

                if (parametes != null)
                {
                    sqlCmd.Parameters.Clear();
                    sqlCmd.Parameters.AddRange(parametes);
                }


                SqlDataAdapter da = new SqlDataAdapter(sqlCmd);
                da.Fill(ds);
                dt = ds.Tables[0];
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State != ConnectionState.Closed)
                {
                    sqlConn.Close();
                }
            }
            return dt;
        }

        /// <summary>
        /// 返回执行T-SQL语句受影响的行数
        /// </summary>
        /// <param name="strSQL">执行的SQL语句</param>
        /// <param name="parametes">传入的参数,无参数时使用NULL</param>
        /// <returns></returns>
        public int ExecuteNonQuery(string strSQL, params SqlParameter[] parametes)
        {
            int sqlInt = -1;

            try
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State == ConnectionState.Closed)
                {
                    sqlConn.Open();
                }

                SqlCommand sqlCmd = sqlConn.CreateCommand();
                sqlCmd.CommandText = strSQL;

                if (parametes != null)
                {
                    sqlCmd.Parameters.Clear();
                    sqlCmd.Parameters.AddRange(parametes);
                }

                sqlInt = sqlCmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State == ConnectionState.Closed)
                {
                    sqlConn.Close();
                }
            }

            return sqlInt;
        }

/*
        /// <summary>
        /// 获取查询的数据集
        /// </summary>
        /// <param name="strSQL">要查询的SQL语句</param>
        /// <param name="parametes">传入的参数,无参数时使用NULL</param>
        /// <returns></returns>
        public DataSet GetDataSet(string strSQL, params SqlParameter[] parametes)
        {
            DataSet ds = new DataSet();

            try
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State == ConnectionState.Closed)
                {
                    sqlConn.Open();
                }

                SqlCommand sqlCmd = sqlConn.CreateCommand();
                sqlCmd.CommandText = strSQL;

                if (parametes != null)
                {
                    sqlCmd.Parameters.Clear();
                    sqlCmd.Parameters.AddRange(parametes);
                }

                SqlDataAdapter da = new SqlDataAdapter(sqlCmd);
                da.Fill(ds);

                sqlConn.Close();
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State != ConnectionState.Closed)
                {
                    sqlConn.Close();
                }
            }

            return ds;
        }


        /// <summary>
        /// 返回SqlDataReader对象.该函数需要在外部打开和关闭连接操作
        /// </summary>
        /// <param name="strSQL">传入的SQL语句</param>
        /// <param name="parametes">传入的参数,无参数时使用NULL</param>
        /// <returns></returns>
        public SqlDataReader ExecuteReader(string strSQL, params SqlParameter[] parametes)
        {
            SqlDataReader reader;
            try
            {
                SqlCommand sqlCmd = sqlConn.CreateCommand();
                sqlCmd.CommandText = strSQL;

                if (parametes != null)
                {
                    sqlCmd.Parameters.Clear();
                    sqlCmd.Parameters.AddRange(parametes);
                }

                reader = sqlCmd.ExecuteReader();
            }
            catch (Exception ex)
            {
                throw ex;
            }

            return reader;
        }



        /// <summary>
        /// 执行查询并返回第一行第一列的值
        /// </summary>
        /// <param name="strSQL">执行的SQL语句</param>
        /// <param name="parametes">传入的参数,无参数时使用NULL</param>
        /// <returns></returns>
        public object ExecuteScalar(string strSQL, params SqlParameter[] parametes)
        {
            object obj;

            try
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State == ConnectionState.Closed)
                {
                    sqlConn.Open();
                }

                SqlCommand sqlCmd = sqlConn.CreateCommand();
                sqlCmd.CommandText = strSQL;

                if (parametes != null)
                {
                    sqlCmd.Parameters.Clear();
                    sqlCmd.Parameters.AddRange(parametes);
                }

                obj = sqlCmd.ExecuteScalar();
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                if (sqlConnPreState == ConnectionState.Closed && sqlConn.State != ConnectionState.Closed)
                {
                    sqlConn.Close();
                }
            }

            return obj;
        }
*/
    }
}
