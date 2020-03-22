#include <iostream>
#include <pqxx/pqxx> 
#include <string>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   char * sql;
   
   try{
      connection C("dbname=BD2_corpus_final user=postgres password=Hakerlol1 \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      // Tabla de las 20 palabras
      /*
      string sql =   "CREATE TABLE lemas20("  \
      "id   bigserial PRIMARY KEY     NOT NULL," \
      "lema        character varying);";
      */
      
      // Tabla de las relaciones entre palabras y su frec.
      
      string sql =   "CREATE TABLE relaciones20("  \
      "id1   bigint," \
      "id2   bigint," \
      "freq  bigint);";
      

      /* Create a transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Table created successfully" << endl;
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}