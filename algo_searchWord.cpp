#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
//#include <fixed>

using namespace std;
using namespace pqxx;

//creamos un struct para guardar el id de la palabra y la frecuencia
struct ele_rel{
   int    id2;
   double freq;
};

//struct para guardar las distancias de las palabras
struct dis_cos{
   int id;
   long double dist;
};

bool my_cmp(const dis_cos & a, const dis_cos & b)
{
    // smallest comes first
    return a.dist > b.dist;
}


//funcion para normalizar las frecuencias
vector<ele_rel> normalizar(vector<ele_rel> a)
{
   vector<ele_rel> b;
   double sumv1 = 0;
   int tam1 = a.size();
   for (int i = 0; i < tam1; ++i)
   {sumv1 = sumv1 + pow(a[i].freq,2);}
   sumv1 = sqrt(sumv1);

   for (int i = 0; i < tam1; ++i)
   {
      b.push_back({a[i].id2,a[i].freq/sumv1});
   }
   return b;
}

//funcion para sacar la distancia entre 2 sets de palabras
long double distanciacos(vector<ele_rel> a, vector<ele_rel> b)
{
   int tam1=a.size();
   int tam2=b.size();
   long double suma=0;
   long double sumv1=1;
   long double sumv2=0;
   long double res;
   for (int i = 0; i < tam2; ++i)
   {sumv2 = sumv2 + pow(b[i].freq,2);}
   sumv2 = sqrt(sumv2);
   int i = 0;
   int j = 0;
   while(i<tam1 && j<tam2){
      if(a[i].id2 < b[j].id2)
         i++;
      else if(a[i].id2 > b[j].id2)
         j++;
      else{
         suma = suma + (a[i].freq * b[j].freq); 
         i++;
         j++;
      }
   }
   res = suma/(sumv1*sumv2);
   return isnan(res) ? 0 : res;
}

//print vector
void mostrar_vec(vector<ele_rel> vec)
{
   for(auto i:vec){cout << "id2: " << i.id2 << " freq:" << i.freq << endl;}
}

void mostrar_vecd(vector<dis_cos> vec,vector<string> pal,vector<int> id)
{  
   int pos;
   cout << fixed;
   for(auto i:vec){
      pos = find(id.begin(),id.end(),i.id) - id.begin();
      cout << "id: " << i.id << "\t pal: " << pal[pos] << "\t dist:" << i.dist << endl;
   }
}



int main(int argc, char* argv[])
{
   cout.precision(10);
   //IDs 10 palabras
   vector<int> id_pal = {1685,14529,19430,20294,20551,36880,42365,49120,50491,52480};
   vector<string> palabras = {"God","pizza","hamburger","pen","cat","lion","Buddha","tiger","notebook","Allah"};
   
   vector<ele_rel> vector_rel;
   vector<ele_rel> vector_nor;
   vector<dis_cos> vector_dis;

   try{
      //Conexion a la base de datos
      connection C("dbname=BD2_corpus_final user=postgres password=Hakerlol1 \
      hostaddr=127.0.0.1 port=5432");
      work W(C);
      //Seleccionamos las relaciones de la palabra con id2 = x
      C.prepare("get_id","SELECT id2,freq FROM relaciones20 WHERE id2 = $1");
      result R( W.prepared("get_id")(1685).exec());
      W.commit();
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         vector_rel.push_back({c[0].as<int>(),c[1].as<double>()});   
      }

      cout << "Valores de la palabra con id2:20551" << endl;
      mostrar_vec(vector_rel);

      vector_nor = normalizar(vector_rel);

      cout << "valores normalizados" << endl;
      mostrar_vec(vector_nor);

      vector_rel.clear();
      //Esto sirve para sacar TODOS los valores de la tabla relaciones20
      /*
      work W1(C);
      C.prepare("get_id_freq","SELECT id2,freq FROM relaciones20");
      result S( W1.prepared("get_id_freq").exec());
      W1.commit();
      for (result::const_iterator c = S.begin(); c != S.end(); ++c) {
         vector_rel.push_back({c[0].as<int>(),c[1].as<double>()});   
      }   
      */

      cout << "Todos los valores de la tabla relaciones" << endl;
      //mostrar_vec(vector_rel);
      //hasta aqui funciona
      
      for (int i = 0; i < id_pal.size(); ++i)
      {
         //sacamos las palabras en bloques de acuerdo al vector 'id_pal'
         work W1(C);
         C.prepare("get_id2","SELECT id2,freq FROM relaciones20 WHERE id1 = $1");
         result S( W1.prepared("get_id2")(id_pal[i]).exec());
         W1.commit();
         //Guardamos todos los registros
         for (result::const_iterator c = S.begin(); c != S.end(); ++c) {
            vector_rel.push_back({c[0].as<int>(),c[1].as<double>()}); 
         }
         vector_dis.push_back({id_pal[i],distanciacos(vector_nor,vector_rel)});
         //cout << "Todos los valores de la tabla relaciones" << endl;
         //mostrar_vec(vector_rel);
         vector_rel.clear();       
      }
      sort(vector_dis.begin(),vector_dis.end(),my_cmp);

      cout << "vector distancias" << endl;
      mostrar_vecd(vector_dis,palabras,id_pal);
      
      cout << "Operation done successfully" << endl;
      
      C.disconnect ();
   }

   catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }
}