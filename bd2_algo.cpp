#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   //variable de la consulta
   //string * sql;



   try{
      connection C("dbname=BD2_corpus_final user=postgres password=Hakerlol1 \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } 
      else {
         cout << "Can't open database" << endl;
         return 1;
      }
      /* Create SQL statement */
      string sql = "SELECT * from lemas";

      /* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "id = "   << c[0].as<int>()    << endl;
         cout << "lema = " << c[1].as<string>() << endl;
      }
      cout << "Operation done successfully" << endl;
      C.disconnect ();

   }
   catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }
}