#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
using namespace pqxx;

void prepare_find(connection_base &c)
{
  // Prepare a statement called "find" that looks for employees with a given
  // name (parameter 1) whose salary exceeds a given number (parameter 2).
  c.prepare(
        "find",
        "SELECT * FROM relaciones WHERE id = $1");
}

result execute_find(transaction_base &t,int id)
{
  return t.prepared("find")(id).exec();
}

int main(int argc, char* argv[])
{
   //variable de la consulta
   //string * sql;
   //creamos un vector con las 10 palabras
   vector<string> palabras;
   palabras.push_back("God");
   palabras.push_back("pizza");
   palabras.push_back("hamburger");
   palabras.push_back("pen");
   palabras.push_back("cat");
   palabras.push_back("lion");
   palabras.push_back("Buddha");
   palabras.push_back("tiger");
   palabras.push_back("notebook");
   palabras.push_back("Allah");
   //sort(palabras.begin(),palabras.end());

   
   vector<int> id_lemas;

   int current_id;

   try{
      //Conexion a la base de datos
      connection C("dbname=BD2_corpus_final user=postgres password=Hakerlol1 \
      hostaddr=127.0.0.1 port=5432");

      //work W(C);
      //consulta simple de buscar por ID     
      /*
      C.prepare("find", "SELECT * FROM relaciones WHERE id1 = $1");
      result R( W.prepared("find")(21157).exec());
      */

      //consulta para guardar los ID's relacionados a "palabras"
      //C.prepare("get_id","SELECT id FROM lemas WHERE lema = $1");
      for (int i = 0; i < 10; ++i)
      {
         work W(C);
         C.prepare("get_id","SELECT id,lema FROM lemas WHERE lema = $1");
         result R( W.prepared("get_id")(palabras[i]).exec());
         W.commit();
         for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << "id = "   << c[0].as<int>() << endl;
            cout << "lema = " << c[1].as<string>() << endl;
            id_lemas.push_back(c[0].as<int>());
         }
         //current_id = R[0].as<int>();
         //id_lemas.push_back(current_id);
      }


      //Guardamos los lemas en la nueva tabla (lemas20)(solo se hace una vez)
      
      for (int i = 0; i < 10; ++i)
      {
         work W(C);
         C.prepare("push_lema","INSERT INTO lemas20 VALUES ($1,$2)");
         result R( W.prepared("push_lema")(id_lemas[i])(palabras[i]).exec());
         W.commit();
      }
      

      //Copiar solo las relaciones de los 10 lemas a una nueva tabla
      for (int i = 0; i < 10; ++i)
      {
         work W(C);
         C.prepare("copy_to_newtable","INSERT INTO relaciones20 SELECT * FROM relaciones WHERE id1=$1");
         result R( W.prepared("copy_to_newtable")(id_lemas[i]).exec());
         W.commit();
      }

      /* Create SQL statement */
      //string sql = "SELECT * from lemas";

      /* Create a non-transactional object. */
      //nontransaction N(C);
      
      /* Execute SQL query */
      //result R( N.exec( sql ));
      

      /* List down all the records */
      /*
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "id1 = "   << c[0].as<int>() << endl;
         cout << "id2 = "   << c[1].as<int>() << endl;
         cout << "freq = "  << c[2].as<int>() << endl;
      }
      cout << "Operation done successfully" << endl;
      */
      C.disconnect ();

   }

   catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }
}